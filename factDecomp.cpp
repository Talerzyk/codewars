#include <iostream>
#include <cmath>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
//#include <windows.h>


class Int512_t
{
public:

    Int512_t()
    {
        number.pop_back();
        number.reserve(512);
    }

    Int512_t(const std::string &n)
    {
        if(n.size() <= 512 && isValid(n))
        {
            number.pop_back();
            number.reserve(512);
            for(uint64_t i = 0; i < n.size(); i++)
            {
                int a = (int)n[i] - 48;
                number.push_back(a);
            }
        }
    }

    Int512_t(const std::vector<int> &v)
    {
        if(v.size() > 512)
            return;

        number.reserve(512);
        number = v;
    }

    ~Int512_t(){}

    bool isValid(std::string n)
    {
        auto isNum = [](char &c){return c <= 57 && c >= 48;};
        bool isV = true;
        for(uint64_t i = 0; i < n.size(); i++)
        {
            if(!isNum(n[i]))
            {
                isV = false;
                break;
            }
        }
        return isV;
    }

    int setNumber(const std::vector<int> &v)
    {
        int success = 0;
        if(v.size() > 512)
            success = 1;
        else
            number = v;

        return success;
    }

    std::vector<int> getNumber()
    {
        return number;
    }

    int print()
    {
        for (int it : number)
        {
            std::cout << it;
        }
        std::cout << std::endl;

        return 0;
    }

private:
        std::vector<int> number {0};
};

//resize vectors for further operations
std::vector<std::vector<int>> resizeVec(std::vector<int>& a, std::vector<int>& b)
{
    std::vector<std::vector<int>> ab;
    int i = a.size(); int j = b.size();

    std::vector<int> c;
    for (int k = abs(i - j); k >= 0; k--)
        c.push_back(0);

    if (i > j)
    {
        b.insert(b.begin(), c.begin(), c.end());
        a.insert(a.begin(), 0);
    }
    else if (i < j)
    {
        a.insert(a.begin(), c.begin(), c.end());
        b.insert(b.begin(), 0);
    }
    else
    {
        a.insert(a.begin(), 0);
        b.insert(b.begin(), 0);
    }
    

    ab.push_back(a); ab.push_back(b);

    return ab;
}

Int512_t operator+ (Int512_t& __lhs, Int512_t& __rhs)
{
    std::vector<int> a = __lhs.getNumber();
    std::vector<int> b = __rhs.getNumber();
    std::vector<std::vector<int>> ab = resizeVec(a, b);
    a = ab[0]; b = ab[1];
    
    
    for(int i = a.size(); i > 0; i--)
    {
        a[i] = a[i] + b[i];
        if(a[i] > 9)
        {
            a[i] = a[i] - 10;
            a[i - 1]++;
        }
    }

    __lhs.setNumber(a);

    return __lhs;
}

Int512_t operator- (Int512_t __lhs, Int512_t __rhs)
{
    std::vector<int> a = __lhs.getNumber();
    std::vector<int> b = __rhs.getNumber();
    std::vector<std::vector<int>> ab = resizeVec(a, b);
    a = ab[0]; b = ab[1];

    for(int i = a.size(); i > 0; i--)
    {
        a[i] = a[i] - b[i];
        if(a[i] < 0)
        {
            a[i] = a[i] + 10;
            a[i - 1]--;
        }
    }
    
    __lhs.setNumber(a);

    return __lhs;
}

bool isPrime(int32_t p)
{
    bool isPrime = true;
    if (p == 2 || p == 3)
        isPrime = true;

    else if (p <= 1 || p % 2 == 0 || p % 3 == 0)
        isPrime = false;

    else
    {
        for (int32_t i = 5; i * i <= p; i += 6)
        {
            if (p % i == 0 || p % (i + 2) == 0)
                isPrime = false;
        }
    }

    return isPrime;
}

int64_t factorial(int32_t n)
{
    int32_t nFact = 1;
    for(int64_t i = 2; i <= n; i++)
    {
        nFact = nFact*i;
    }

    return nFact;
}

std::string decomp(int32_t n)
{
    std::string result;
    int64_t nFact = factorial(n);

    std::map<int32_t, int32_t> divisors;

    for(int64_t i = 2; i < sqrt(nFact); i++)
    {
        if(isPrime(i))
        {
            divisors[i] = 0;
        }
    }

    std::cout << "nFact=" << nFact << std::endl;
    auto i = divisors.begin();
    while(i != divisors.end())
    {
        if((nFact % i->first) == 0)
        {
            i->second++;
            nFact = nFact/i->first;
            std::cout << "nFact=" << nFact << "  k=" << i->first << "  v=" << i->second << std::endl;
            i = divisors.begin(); //we need to always check from 2 just in case
        }
        else
        {
            i++;
        }
    }

    for(auto i = divisors.begin(); i != divisors.end(); i++)
    {
        if(i->second)
        {
            if(i != divisors.begin())
            {
                result = result + " * ";
            }

            if(i->second > 1)
            {
                result = result + std::to_string(i->first) + "^" + std::to_string(i->second);
            }
            else
            {
                result = result + std::to_string(i->first);
            }
        }
    }
    return result;
}


int main()
{
    std::string a {"1000"}, b {"1"};
    Int512_t num1(a), num2(b);
    Int512_t num3(num1 - num2);
    num3.print();

    return 0;
}
