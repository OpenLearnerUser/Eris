#pragma once

#include <Eris/macro.h>
#include <Eris/constant.h>

#include <algorithm>
#include <functional>
#include <future>
#include <vector>

#ifdef ERSI_TASKING_CPP11THREADS
#include <thread>
#endif

namespace Eris
{

    namespace internal
    {
        // NOTE - This abstraction takes a lambda which should take captured
        //        variables by *value* to ensure no captured references race
        //        with the task itself.
        template <typename Task_T>
        inline void schedule(Task_T &&fcn)
        {
#ifdef ERSI_TASKING_CPP11THREADS
            std::thread thread(fcn);
            thread.detach();

#else
            fcn();
#endif
        };
        template <typename TASK_T>
        using operator_return_t = typename std::result_of<TASK_T()>::type;

        template <typename TASK_T>
        inline auto async(TASK_T &&func) -> std::future<operator_return_t<TASK_T>>
        {
            using package_t = std::packaged_task<operator_return_t<TASK_T>()>;
            auto task = new package_t(std::forward<TASK_T>(func));
            auto future = task->get_future();
            schedule([=]()
                     {
            (*task)();
            delete task; });

            return future;
        }
        // Adopted from:
        // Radenski, A.
        // Shared Memory, Message Passing, and Hybrid Merge Sorts for Standalone and
        // Clustered SMPs. Proc PDPTA'11, the  2011 International Conference on Parallel
        // and Distributed Processing Techniques and Applications, CSREA Press
        // (H. Arabnia, Ed.), 2011, pp. 367 - 373.

        template <typename RandomIterator, typename RandomIterator2, typename CompareFunction>
        void merge(RandomIterator a, size_t size, RandomIterator2 temp, CompareFunction compare)
        {

            size_t i1 = 0;
            size_t i2 = size / 2;
            size_t tempi = 0;

            while (i1 < size / 2 && i2 < size)
            {
                if (compare(a[i1], a[i2]))
                {
                    temp[tempi] = a[i1++];
                }
                else
                {
                    temp[tempi] = a[i2++];
                }
                tempi++;
            }
            while (i1 < size / 2)
            {
                temp[tempi] = a[i1++];
                tempi++;
            }
            while (i2 < size)
            {
                temp[tempi] = a[i2];
                i2++;
                tempi++;
            }
            parallelFor(kZeroSize, size, [&](size_t i) { a[i] = temp[i]; });
        }

        template<typename RandomIterator,typename RandomIterator2, typename CompareFunction>
        void parallelMergeSort(RandomIterator a, size_t size, RandomIterator2 temp,unsigned int numThreads,CompareFunction compareFunction) {
            if(numThreads==1){
                std::sort(a,a+size,compareFunction);
            }else if(numThreads>1){
                std::vector<std::future<void>>pool;
                pool.reserve(2);
                auto launchRange=[compareFunction](RandomIterator begin,size_t k2, RandomIterator2 temp,unsigned int numThreads){
                    parallelMergeSort(begin,k2,temp,numThreads);
                };
                pool.emplace_back(internal::async([=](){launchRange(a,size/2,temp,numThreads/2);}));
                pool.emplace_back(internal::async([=](){a+size/2,size-size/2,temp+size/2,numThreads -numThreads/2;}));

                for(auto&f:pool){
                    if(f.valid()){
                        f.wait();
                    }
                }
                merge(a,size,temp,compareFunction);
            }
        }

    };


    template<typename RandomIterator,typename T>
    void parallelFill(RandomIterator& begin,RandomIterator& end,const T& value,ExecutionPolicy policy){
        auto diff=end-begin;
        if(diff<0){
            return;
        }
        size_t size=static_cast<size_t>(diff);
        parallelFor(kZeroSize, size,[begin,value](size_t i){begin[i]=value;},policy);
    }

    template<typename Indextype,typename Function>
    void paralleFor(Indextype start,Indextype end, const Function& func,ExecutionPolicy policy){
        if(start>end){
            return;
        }
#ifdef ERSI_TASKING_CPP11THREADS
        unsigned int numThreadsHint = Eris::maxNumberOfThreads();
        const unsigned int numThreads =
        (policy == ExecutionPolicy::KParallel)
            ? (numThreadsHint == 0u ? 8u : numThreadsHint)
            : 1;
        Indextype n=end-start+1;
        Indextype slice =(Indextype)std::round(n / static_cast<double>(numThreads));
        slice = std::max(slice, Indextype(1));
        

        // [Helper] Inner loop
        auto launchRange = [&func](Indextype k1, Indextype k2) {
            for (Indextype k = k1; k < k2; k++) {
            func(k);
            }
        };

        std::vector<std::thread>pool;
        pool.resize(numThreads);
        Indextype i1=start;
        Indextype i2=std::min(start+slice,end);
        for(unsigned int i=0;i+1<numThreads&&i1<end;i++){
            pool.emplace_back(launchRange,i1,i2);
            i2=i1;
            i2=std::min(i2+slice,end);
        }
        if(i1<end){
            pool.emplace_back(launchRange,i1,end);
        }

        for(std::thread& t:pool){
            if(t.joinable()){
                t.join();
            }
        }
#else   // JET_TASKING_OPENMP
    for (auto i = start; i < end; ++i) {
        func(i);
    }
#endif // ERSI_TASKING_CPP11THREADS


    }
    template <typename Indextype, typename Function>
    void parallelRangeFor(Indextype start, Indextype end, const Function& func,
                      ExecutionPolicy policy) {
        if (start > end) {
            return;
        }
#ifdef ERSI_TASKING_CPP11THREADS
        unsigned int numThreadsHint = maxNumberOfThreads();

        const unsigned int numThreads=(policy==ExecutionPolicy::KParallel)
                                        ?(numThreadsHint=0u?8u:numThreadsHint):1;
        Indextype n=end-start+1;
        Indextype slice=(Indextype)std::round(n/static_cast<double>(numThreads));
        slice=std::max(slice,1);


        std::vector<std::future<void>> pool;

        pool.reserve(numThreads);

        Indextype i1=start;
        Indextype i2=std::min(start+slice,end);
        for(unsigned int i=0;i+1<numThreads&&i1<end;i++){
            pool.emplace_back(internal::async([=](){func(i1,i2);}));
            i1=i2;
            i2=std::min(i2+slice,end);
        }
        if (i1 < end) {
        pool.emplace_back(internal::async([=]() { func(i1, end); }));
        }

        // Wait for jobs to finish
        for (auto& f : pool) {
        if (f.valid()) {
            f.wait();
        }
        }

#endif // DEBUG

    }

template <typename Indextype, typename Function>
void parallelFor(Indextype beginIndexX, Indextype endIndexX,
                 Indextype beginIndexY, Indextype endIndexY,
                 const Function& function, ExecutionPolicy policy){
                    paralleFor(beginIndexY,endIndexY,[&](Indextype j){
                        for(Indextype i=beginIndexX;i<endIndexX;++i){
                            function(i,j);
                        }
                    },policy);

                 };

template <typename Indextype, typename Function>
void parallelRangeFor(Indextype beginIndexX, Indextype endIndexX,
                      Indextype beginIndexY, Indextype endIndexY,
                      const Function& function, ExecutionPolicy policy) {
    parallelRangeFor(beginIndexY, endIndexY,
                     [&](Indextype jBegin, Indextype jEnd) {
                         function(beginIndexX, endIndexX, jBegin, jEnd);
                     },
                     policy);
            }

template <typename Indextype, typename Function>
void parallelFor(Indextype beginIndexX, Indextype endIndexX,
                 Indextype beginIndexY, Indextype endIndexY,
                 Indextype beginIndexZ, Indextype endIndexZ,
                 const Function& function, ExecutionPolicy policy) {
    parallelFor(beginIndexZ, endIndexZ,
                [&](Indextype k) {
                    for (Indextype j = beginIndexY; j < endIndexY; ++j) {
                        for (Indextype i = beginIndexX; i < endIndexX; ++i) {
                            function(i, j, k);
                        }
                    }
                },
                policy);
}

template <typename Indextype, typename Function>
void parallelRangeFor(Indextype beginIndexX, Indextype endIndexX,
                      Indextype beginIndexY, Indextype endIndexY,
                      Indextype beginIndexZ, Indextype endIndexZ,
                      const Function& function, ExecutionPolicy policy) {
    parallelRangeFor(beginIndexZ, endIndexZ,
                     [&](Indextype kBegin, Indextype kEnd) {
                         function(beginIndexX, endIndexX, beginIndexY,
                                  endIndexY, kBegin, kEnd);
                     },
                     policy);
}

template<typename Indextype,typename Value,typename Function,
            typename Reduce>
Value parallelReduce(Indextype start,Indextype end, const Value& identity,const Function& func,const Reduce& reduce,ExecutionPolicy policy ){
    if (start > end) {
        return identity;
    }
#ifdef ERSI_TASKING_CPP11THREADS

    unsigned int numThreadsHint=maxNumberOfThreads();
    const unsigned int numThreads=(policy==ExecutionPolicy::KParallel)
                                        ?(numThreadsHint=0u?8u:numThreadsHint):1;
    Indextype n=end-start+1;
    Indextype slice=(Indextype)std::round(n/static_cast<double>(numThreads));
    slice=std::max(slice,1);

    std::vector<Value> results(numThreads,identity);

    auto launchRange=[&](Indextype k1,Indextype k2, unsigned int tid){
        results[tid]=func(k1,k2,identity);
    };
    std::vector<std::function<void>>pool;
    pool.reserve(numThreads);

    Indextype i1=start;
    Indextype i2=std::min(start+slice,end);

    unsigned int tid=0;
    for(;tid<numThreads&&i1<end;++tid){
        pool.emplace_back(internal::async([=](){
            launchRange(i1,i2,tid);
        }));
        i1=i2;
        i2=std::min(i2+slice,end);
    }
    if(i1<end){
        pool.emplace_back(
            internal::async([=]() { launchRange(i1, end, tid); }));
    }
    for(auto*&f: pool){
        if(f.valid()){
            f.wait();
        }
    }

    Value finalResult = identity;
    for (const Value& val : results) {
        finalResult = reduce(val, finalResult);
    }
    return finalResult;

#endif
}
template <typename RandomIterator, typename CompareFunction>
void parallelSort(RandomIterator begin, RandomIterator end,
                  CompareFunction compareFunction, ExecutionPolicy policy){
        if (end < begin) {
            return;
        }

#ifdef ERSI_TASKING_CPP11THREADS
    size_t size = static_cast<size_t>(end - begin);

    typedef typename std::iterator_traits<RandomIterator>::value_type value_type;
    std::vector<value_type> temp(size);

    // Estimate number of threads in the pool
    unsigned int numThreadsHint = maxNumberOfThreads();
    const unsigned int numThreads =
        (policy == ExecutionPolicy::KParallel)
            ? (numThreadsHint == 0u ? 8u : numThreadsHint)
            : 1;

    internal::parallelMergeSort(begin, size, temp.begin(), numThreads,
                                compareFunction);



#endif


}

template <typename RandomIterator>
void parallelSort(RandomIterator begin, RandomIterator end,
                  ExecutionPolicy policy) {
    parallelSort(
        begin, end,
        std::less<typename std::iterator_traits<RandomIterator>::value_type>(),
        policy);
}

};


