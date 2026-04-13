#pragma once

#include <Eris/macro.h>

#include <algorithm>
#include <functional>
#include <future>
#include <vector>

#ifdef ERSI_TASKING_CPP11THREADS
#include <thread>
#endif

namespace Eris
{

namespace internal{
    // NOTE - This abstraction takes a lambda which should take captured
    //        variables by *value* to ensure no captured references race
    //        with the task itself.
    template<typename Task_T>
    inline void schedule(Task_T&& fcn){
#ifdef ERSI_TASKING_CPP11THREADS
        std::thread thread(fcn);
        thread.detach();
    
#else 
        fcn();
#endif
    
    };
    template <typename TASK_T>
    using operator_return_t=typename std::result_of<TASK_T()>::type;
    
    
    template <typename TASK_T>
    inline auto async(TASK_T && func)->std::future<operator_return_t<TASK_T> >{
        using package_t=std::packaged_task<operator_return_t<TASK_T>()>;
        auto task=new package_t(std::forward<TASK_T>(func));
        auto future=task->get_future();
        schedule([=](){
            (*task)();
            delete task;
        });

        return future;
        
    }



};





};


