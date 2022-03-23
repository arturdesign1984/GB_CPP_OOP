#include <cstdint>
#include <iostream>
#include <cmath>

// 01 //////////////////////////////

class Power
{
private:
    double a;
    double b;
public:
    Power() : a(4.), b(-0.5)
    {}
    void set(double a, double b)
    {
        this->a = a;
        this->b = b;
    }
    void calculate()
    {
        double result;
        result = pow(a,b);
        std::cout << result << std::endl;
    }
    ~Power()
    {}
};

// 02 //////////////////////////////

class RGBA
{
private:
    std::uint8_t m_red, m_green, m_blue, m_alpha;
public:
    RGBA() : m_red(0), m_green(0), m_blue(0), m_alpha(255)
    {}
    RGBA(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha) : m_red(red), m_green(green), m_blue(blue), m_alpha(alpha)
    {}
    void print()
    {
        std::cout << "m_red - " << static_cast<uint16_t> (m_red) << std::endl;
        std::cout << "m_green - " << static_cast<uint16_t> (m_green) << std::endl;
        std::cout << "m_blue - " << static_cast<uint16_t> (m_blue) << std::endl;
        std::cout << "m_alpha - " << static_cast<uint16_t> (m_alpha) << std::endl;
    }
    ~RGBA()
    {}
};

// 03 //////////////////////////////

class Stack
{
private:
    int arr[10];
    int count;
public:
    Stack() : count(0)
    {
        for(int k = 0; k < 10; k++)
        {
            arr[k] = 0;
        }
    }
    void reset()
    {
        for(int k = 0; k < 10; k++)
        {
            arr[k] = 0;
        }
        count = 0;
    }
    bool push(int x)
    {
        if (count < 10)
        {
            arr[count++] = x;
            return true;
        }
        else
        {
            std::cout << "Err: Stack is full!" << std::endl;
            return false;
        }
    }
    int pop()
    {
        int x;
        if (count == 0)
        {
            std::cout << "Err: Stack is empty!" << std::endl;
        }
        else
        {
            x = arr[count--];
            return x;
        }
    }
    void print()
    {
        if (count == 0)
        {
            std::cout << "()" << std::endl;
        }
        else
        {
            std::cout << '(';
            for(int k = 0; k < count; k++)
            {
                std::cout << arr[k];
            }
            std::cout << ')' << std::endl;
        }
    }
};

int main()
{
    // 01 //////////////////////////////
    std::cout << "######\n# 01 #\n######\n\nClass Power:\n\n";

    Power pow;
    pow.calculate();

    std::cout << std::endl;

    // 02  /////////////////////////////
    std::cout << "######\n# 02 #\n######\n\nClass RGBA:\n\n";

    RGBA rgba1;
    rgba1.print();

    std::cout << std::endl;

    RGBA rgba2(5,11,56,128);
    rgba2.print();

    std::cout << std::endl;

    // 03  /////////////////////////////
    std::cout << "######\n# 03 #\n######\n\nClass Stack:\n\n";

    Stack stack;
    stack.reset();
    stack.print();

    stack.push(3);
    stack.push(7);
    stack.push(5);

    stack.print();

    stack.pop();
    stack.print();

    stack.pop();
    stack.pop();
    stack.print();

    return 0;
}

