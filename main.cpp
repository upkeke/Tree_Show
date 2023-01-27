
#include "some_func.h"
#include <MyTree.h>
#include <iostream>
int main(int argc, char *argv[])
{
    auto arr = get_vector_norepeat(10);
    std::cout<<arr.size()<<"\n";
    for(auto i:arr)
    {
        std::cout<<i<<'\t';
    }
    return 0;
}