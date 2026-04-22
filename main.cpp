#include <iostream>
#include <Eris/array1.h>
#include <Eris/parallel.h>

int main(int argc, char **argv)
{

    Eris::Array1<double> test={1.0,2.0,3.0,4.0};
    std::cout<<test[2]<<std::endl;
    std::cout<<"hello fluid\n";

#ifdef ERSI_TASKING_CPP11THREADS
    std::cout<<"define :ERSI_TASKING_CPP11THREADS"<<std::endl;
#endif // DEBUG
    return 0;
}