
#include<iostream>
struct x{};
struct x1:x{};
int main(int argc, char *argv[])
{
    x1* a1 = new x1();
    x* a2 = a1;
    std::cout<<(a1 == a2);
    return 0;
}