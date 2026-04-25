#include <Eris/parallel.h>


#include <memory>
#include <thread>

#if defined(ERIS_TASKING_TBB)
# include <tbb/task_arena.h>
# include <tbb/task_scheduler_init.h>
#elif defined(ERIS_TASKING_OPENMP)
# include <omp.h>
#endif

static unsigned int sMaxNumberOfThreads=std::thread::hardware_concurrency();

namespace Eris{

   void setMaxNumberOfThreads(unsigned int numThreads){
        sMaxNumberOfThreads = std::max(numThreads, 1u);
   }

    unsigned int maxNumberOfThreads() { return sMaxNumberOfThreads; }


}