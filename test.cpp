#include <iostream>
#include <bigint.hpp>

int main() {
    {
        bigint a(90024);

        std::cout << a << "== 90024" << std::endl;
    }
    
    {
        bigint a("789937586938093858935");

        std::cout << a << "== 789937586938093858935" << std::endl;
    }

    {
        bigint a(5);
        bigint b(5);
        bigint c = a + b;

        std::cout << a << "== 10" << std::endl;
    }
}