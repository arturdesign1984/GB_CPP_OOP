#include <cstdint>
#include <iostream>
#include <cmath>

// 01 //////////////////////////////

class Figure
{
protected:
    static constexpr double pi = 3.1415;
public:
    virtual double area() const = 0;
};

class Circle : public Figure
{
private:
    double radius;
public:
    Circle (double rad) : radius(rad)
    {}
    double  area() const
    {
        return (pi*radius*radius);
    }
};

class Parallelogram : public Figure
{
private:
    double sideA, sideB, alpha;
public:
    Parallelogram()
    {}
    Parallelogram (double sA, double sB, double alp) : sideA(sA), sideB(sB), alpha(alp)
    {}
    virtual double area() const
    {
        return (sideA*sideB*(std::abs((sin(alpha*pi/180)))));
    }
};

class Rectangle : public Parallelogram
{
private:
    double sideA, sideB;
public:
    Rectangle (double sideA, double sideB) : sideA(sideA), sideB(sideB)
    {}
    double area() const
    {
        return (sideA*sideB);
    }
};

class Square : public Parallelogram
{
private:
    double side;
public:
    Square (double side) : side(side)
    {}
    double area() const
    {
        return (sqrt(side));
    }
};

class Rhombus : public Parallelogram
{
private:
    double side, alpha;
public:
    Rhombus (double side, double alpha) : side(side), alpha(alpha)
    {}
    double area() const
    {
        return (side*side*std::abs((sin(alpha*pi/180))));
    }
};

// 02 //////////////////////////////

class Car
{
protected:
    std::string company, model;
public:
    Car() : company("CarC"), model("CarM")
    {
        std::cout << "classCar - ";
        std::cout << " Company - " << company;
        std::cout << " Model - " << model << std::endl;
    }
    ~Car()
    {
        std::cout << "~classCar" << std::endl;
    }
};

class PassengerCar : virtual public Car
{
public:
    PassengerCar()
    {
        company = "PassengerCarC";
        model = "PassengerCarM";
        std::cout << "classPassengerCar - ";
        std::cout << " Company - " << company;
        std::cout << " Model - " << model << std::endl;
    }
    ~PassengerCar()
    {
        std::cout << "~classPassengerCar" << std::endl;
    }
};

class Bus : virtual public Car
{
public:
    Bus()
    {
        company = "BusC";
        model = "BusM";
        std::cout << "classBus - " ;
        std::cout << " Company - " << company;
        std::cout << " Model - " << model << std::endl;
    }
    ~Bus()
    {
        std::cout << "~classBus" << std::endl;
    }
};

class Minivan : public PassengerCar, public Bus
{
public:
    Minivan()
    {
        company = "MinivanC";
        model = "MinivanM";
        std::cout << "classMinivan - ";
        std::cout << " Company - " << company;
        std::cout << " Model - " << model << std::endl;
    }
    ~Minivan()
    {
        std::cout << "~classMinivan" << std::endl;
    }
};

// 03 //////////////////////////////

class Fraction
{
private:
    int32_t divisible, divider;
public:
    Fraction () : divisible(0), divider(1)
    {}
    Fraction (int32_t divisible, int32_t divider)
    {
        this->divisible = divisible;
        if(divider == 0)
        {
            std::cout << "ERROR! Division by (0)" << std::endl;
        }
        else
        {
            this->divider = divider;
        }
        if(this->divisible < 0 && this->divider < 0)    // Если числитель и знаменатель отрицательные делаем положительную дробь
        {
            this->divisible = -this->divisible;
            this->divider = -this->divider;
        }
        else if(this->divider < 0)                      // Если только знаменатель отрицательный делаем отрицательным числитель, а знаменатель положительным для простоты расчетов
        {
            this->divisible = -this->divisible;
            this->divider = -this->divider;
        }
    }

    Fraction operator- ()
    {
        int32_t de = -this->divisible;
        return Fraction(de, divider);
    }
    Fraction operator- (const Fraction &fr)
    {
        int32_t de = divisible*fr.divider - fr.divisible*divider;
        int32_t dr = divider*fr.divider;
        return Fraction(de, dr);
    }
    Fraction operator+ (const Fraction &fr)
    {
        int32_t de = divisible*fr.divider + fr.divisible*divider;
        int32_t dr = divider*fr.divider;
        return Fraction(de, dr);
    }
    Fraction operator* (const Fraction &fr)
    {
        int32_t de = divisible*fr.divisible;
        int32_t dr = divider*fr.divider;
        return Fraction(de, dr);
    }
    Fraction operator/ (const Fraction &fr)
    {
        int32_t de = divisible*fr.divider;
        int32_t dr = divider*fr.divisible;
        return Fraction(de, dr);
    }
    bool operator== (const Fraction &fr)
    {
        if(divisible*fr.divider == fr.divisible*divider)
        {
            return true;
        }
        return false;
    }
    bool operator!= (const Fraction &fr)
    {
        if(*this==fr)
        {
            return false;
        }
        return true;
    }
    bool operator< (const Fraction &fr)
    {
        if(divisible*fr.divider < fr.divisible*divider)
        {
            return true;
        }
        return false;
    }
    bool operator>= (const Fraction &fr)
    {
        if(*this<fr)
        {
            return false;
        }
        return true;
    }
    bool operator> (const Fraction &fr)
    {
        if(divisible*fr.divider > fr.divisible*divider)
        {
            return true;
        }
        return false;
    }
    bool operator<= (const Fraction &fr)
    {
        if(*this>fr)
        {
            return false;
        }
        return true;
    }
    friend std::ostream& operator<<(std::ostream& os, const Fraction& fr)
    {
        return os << fr.divisible << '/' << fr.divider;
    }
};

// 04 //////////////////////////////

enum cardValue
{
    ACE=1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
};
enum cardSuit
{
    HEART=3,
    DIAMOND,
    CLUB,
    SPADE
};

class Card
{
private:
    cardValue value;
    cardSuit suit;
    bool visible;
public:
    Card(cardValue value, cardSuit suit, bool visible) : value(value), suit(suit), visible(visible)
    {}
    void Flip()
    {
        visible = !visible;
    }
    uint16_t GetValue() const
    {
        return this->value;
    }
    uint8_t GetSuit() const
    {
        return this->suit;
    }
    bool GetVisible() const
    {
        return this->visible;
    }
};
std::ostream& operator<<(std::ostream& os, const Card& c)
{
    if(c.GetVisible())
    {
        switch (c.GetValue())
        {
            case ACE: return os << "Card is: " << '(' << 'A' << c.GetSuit() << ')'; break;
            case JACK: return os << "Card is: " << '(' << 'J' << c.GetSuit() << ')'; break;
            case QUEEN: return os << "Card is: " << '(' << 'Q' << c.GetSuit() << ')'; break;
            case KING: return os << "Card is: " << '(' << 'K' << c.GetSuit() << ')'; break;
            default : return os << "Card is: " << '(' << c.GetValue() << c.GetSuit() << ')';
        }

    }
    return os << "Card is: " << "(**)";
}

int main()
{
    // 01 //////////////////////////////
    std::cout << "######\n# 01 #\n######\n\nClass Figure:\n\n";

    Circle ci(3);
    std::cout << "Circle area: " << ci.area() << std::endl;

    Parallelogram pa(3,5,90);
    std::cout << "Parallelogram area: " << pa.area() << std::endl;

    Rectangle re(2,6);
    std::cout << "Rectangle area: " << re.area() << std::endl;

    Square sq(8);
    std::cout << "Square area: " << sq.area() << std::endl;

    Rhombus rh(2,10);
    std::cout << "Rhombus Square: " << rh.area() << std::endl;

    std::cout << std::endl;

    // 02  /////////////////////////////
    std::cout << "######\n# 02 #\n######\n\nClass Car:\n\n";

    if(1)
    {
    Car ca;
    PassengerCar pc;
    Bus bu;
    Minivan mi;
    }

    std::cout << std::endl;

    // 03  /////////////////////////////
    std::cout << "######\n# 03 #\n######\n\nClass Fraction:\n\n";

    Fraction fr1(3,7);
    Fraction fr2(9,2);
    Fraction fr3;
    fr3 = -fr1;
    std::cout << fr3 << std::endl;
    fr3 = fr1 - fr2;
    std::cout << fr3 << std::endl;
    fr3 = fr1 + fr2;
    std::cout << fr3 << std::endl;
    fr3 = fr1 * fr2;
    std::cout << fr3 << std::endl;
    fr3 = fr1 / fr2;
    std::cout << fr3 << std::endl;
    std::cout << (fr1 == fr2) << std::endl;
    std::cout << (fr1 != fr2) << std::endl;
    std::cout << (fr1 < fr2) << std::endl;
    std::cout << (fr1 > fr2) << std::endl;
    std::cout << (fr1 <= fr2) << std::endl;
    std::cout << (fr1 >= fr2) << std::endl;

    std::cout << std::endl;

    // 04  /////////////////////////////
    std::cout << "######\n# 04 #\n######\n\nClass Card:\n\n";

    Card c1(ACE, HEART,0);
    std::cout << c1 << std::endl;
    c1.Flip();
    std::cout << c1 << std::endl;

    std::cout << std::endl;

    return 0;
}

