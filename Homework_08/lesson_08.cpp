#include <iostream>
#include <vector>

// 01 //////////////////////////////

template <typename T>
T div(T a, T b)
{
    a = static_cast<double>(a);
    if(!b)
    {
        throw "DivisionByZero";
    }
    return (a/b);
}

// 02 //////////////////////////////

class Ex
{
private:
    double x;
public:
    Ex (double x) : x(x)
    {}
    double get()
    {
        return x;
    }
};

class Bar
{
private:
    double y;
public:
    Bar() : y(0)
    {}
    ~Bar()
    {}
    void set(double a)
    {
        if(y+a > 100)
        {
            Ex ex(a*y);
            throw  ex;
        }
        else
        {
            y = a;
        }
    }
};

// 03  /////////////////////////////

class IllegalCommand
{
private:
    int x,y,m;
public:
    IllegalCommand(int x, int y, int m) : x(x), y(y), m(m)
    {}
    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }
    int getM()
    {
        return m;
    }
};

class OffTheField
{
private:
    int x,y,m;
public:
    OffTheField(int x, int y, int m) : x(x), y(y), m(m)
    {}
    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }
    int getM()
    {
        return m;
    }
};

class Robot
{
private:
    int x,y;
public:
    Robot() : x(0), y(0)
    {}
    void move(int& m)
    {
        if(m < 1 || m > 4)
        {
            IllegalCommand ic(x, y, m);
            throw ic;
        }
        switch (m)
        {
        case 1:
            --x;
            if(x < 0)
            {
                ++x;
                OffTheField otf(x, y, m);
                throw otf;
            }
            break;
        case 2:
            ++y;
            if(y > 9)
            {
                --y;
                OffTheField otf(x, y, m);
                throw otf;
            }
            break;
        case 3:
            ++x;
            if(x > 9)
            {
                --x;
                OffTheField otf(x, y, m);
                throw otf;
            }
            break;
        case 4:
            --y;
            if(y < 0)
            {
                ++x;
                OffTheField otf(x, y, m);
                throw otf;
            }
            break;
        }
    }
    void getPosition()
    {
        std::cout << "Position is - (" << x << ',' << y << ')' <<std::endl;
    }
};


int main()
{
// 01 //////////////////////////////
    std::cout << "######\n# 01 #\n######\n\nDiv:\n\n";

    int a, b;
    std::cout << "Enter divisible: \n";
    std::cin >> a;
    std::cout << "Enter divider: \n";
    std::cin >> b;

    try
    {
        double c = div<double>(a,b);
        std::cout << "Result is " << c;
    }
    catch (const char* exeption)
    {
        std::cerr << "Error: " << exeption << std::endl;
    }

    std::cout << std::endl;

// 02  /////////////////////////////
    std::cout << "######\n# 02 #\n######\n\nEx:\n\n";

    Bar bar;
    double nom = 0;

    while(nom >= 0)
    {
        std::cout << "Enter nomber: ";
        std::cin >> nom;
        try
        {
            bar.set(nom);
        }
        catch(Ex& ex)
        {
            std::cerr << "Error! - " << ex.get() << std::endl;
            break;
        }
    }

    std::cout << std::endl;

// 03  /////////////////////////////
    std::cout << "######\n# 03 #\n######\n\nRobot:\n\n";

    Robot bot;

    std::cout << "Enter direction\n(1 - left | 2 - up | 3 - right | 4 - down | Any letter to quit): ";
    std::string str = "0";
    int direction;
    std::cin >> str;

    while(std::isdigit(str[0]))
    {

        direction = std::atoi(str.c_str());
        try
        {
            bot.move(direction);
        }
        catch(OffTheField& otf)
        {
            std::cerr << "Error - Off the field! Coord (" << otf.getX() << ',' << otf.getY() << "), Direction (" << otf.getM() << ')' << std::endl;
        }
        catch(IllegalCommand& ic)
        {
            std::cerr << "Error - Illegal command! Coord (" << ic.getX() << ',' << ic.getY() << "), Direction (" << ic.getM() << ')' << std::endl;
        }

        std::cout << "Enter direction\n(1 - left | 2 - up | 3 - right | 4 - down | Any letter to quit): ";
        std::cin >> str;
    }

    std::cout << std::endl;


    return 0;
}


