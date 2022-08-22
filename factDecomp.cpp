#include <iostream>
#include <cmath>
#include <map>

bool isPrime(int32_t p)
{
    bool isPrime = true;
    if (p == 2 || p == 3)
        isPrime = true;

    if (p <= 1 || p % 2 == 0 || p % 3 == 0)
        isPrime = false;

    for (int32_t i = 5; i * i <= p; i += 6)
    {
        if (p % i == 0 || p % (i + 2) == 0)
            isPrime = false;
    }

    return isPrime;
}

int32_t nextPrime(int32_t p)
{

}

int64_t factorial(int32_t n)
{
    int32_t n_fact = 1;
    for(int64_t i = 2; i <= n; i++)
    {
        n_fact = n_fact*i;
    }

    std::map<int32_t, int32_t> divisors;


    return n_fact;
}

std::string decomp(int32_t n)
{
    std::string result;
    int64_t n_fact = factorial(n);


    return result;
}

int main()
{
    int32_t n = 1;
    std::cout << "enter factorial" << std::endl;
    std::cin >> n;

    std::cout << factorial(n) << std::endl;
}