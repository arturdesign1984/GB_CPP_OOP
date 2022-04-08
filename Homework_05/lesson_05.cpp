#include <iostream>
#include <vector>

// 01 //////////////////////////////

template<typename T>
class Pair1
{
private:
    T firstItem, secondItem;
public:
    Pair1(T firstItem, T secondItem) : firstItem(firstItem), secondItem(secondItem)
    {}
    T first() const
    {
        return firstItem;
    }
    T second() const
    {
        return secondItem;
    }
};

// 02 //////////////////////////////

template<typename T1, typename T2>
class Pair
{
private:
    T1 firstItem;
    T2 secondItem;
public:
    Pair(T1 firstItem, T2 secondItem) : firstItem(firstItem), secondItem(secondItem)
    {}
    T1 first() const
    {
        return firstItem;
    }
    T2 second() const
    {
        return secondItem;
    }
};

// 03  /////////////////////////////

template<typename T>
class StringValuePair : public Pair<std::string, T>
{
public:
    StringValuePair(std::string firstItem, T secondItem) :  Pair<std::string, T>(firstItem, secondItem)
    {}
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

enum cardVisibility
{
    OFF=0,
    ON=1
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
            case ACE: return os << '(' << 'A' << c.GetSuit() << ')'; break;
            case JACK: return os << '(' << 'J' << c.GetSuit() << ')'; break;
            case QUEEN: return os << '(' << 'Q' << c.GetSuit() << ')'; break;
            case KING: return os << '(' << 'K' << c.GetSuit() << ')'; break;
            default : return os << '(' << c.GetValue() << c.GetSuit() << ')';
        }

    }
    return os << "Card is: " << "(**)";
}

class Hand
{
private:
    std::vector<Card*> cardsOnHand;
public:
    void Add(Card* card)
    {
        cardsOnHand.push_back(card);
    }
    void Clear()
    {
        cardsOnHand.clear();
    }
    uint16_t GetValue()
    {
        uint16_t result = 0;
        bool aceOnHand = false;
        for(size_t k = 0; k < cardsOnHand.size(); ++k)
        {
            if(cardsOnHand[k]->GetValue() == ACE)
            {
                aceOnHand = true;
            }

            if(cardsOnHand[k]->GetValue() == JACK || cardsOnHand[k]->GetValue() == QUEEN || cardsOnHand[k]->GetValue() == KING)
            {
                result += 10;
            }
            else
            {
                result += cardsOnHand[k]->GetValue();
            }
        }
        if(aceOnHand && result <= 11)
        {
            result += 10;
        }
        return result;
    }
};

class GenericPlayer : public Hand
{
private:
    std::string name;
public:
    GenericPlayer(std::string name) : name(name)
    {}
    virtual bool IsHitting() const =0;

    bool IsBoosted()
    {
        if(this->GetValue() > 21)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void Bust()
    {
        std::cout << "Player " << name << " busted";
    }
};

int main()
{
// 01 //////////////////////////////
    std::cout << "######\n# 01 #\n######\n\nClass Pair1:\n\n";

    Pair1<int> p1(6, 9);
    std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

    const Pair1<double> p2(3.4, 7.8);
    std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

    std::cout << std::endl;

// 02  /////////////////////////////
    std::cout << "######\n# 02 #\n######\n\nClass Pair:\n\n";

    Pair<int, double> p01(6, 7.8);
    std::cout << "Pair: " << p01.first() << ' ' << p01.second() << '\n';

    const Pair<double, int> p02(3.4, 5);
    std::cout << "Pair: " << p02.first() << ' ' << p02.second() << '\n';

    std::cout << std::endl;

// 03  /////////////////////////////
    std::cout << "######\n# 03 #\n######\n\nClass StringValuePair:\n\n";

    StringValuePair<int> svp("Amazing", 7);
    std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';

    std::cout << std::endl;

// 04  /////////////////////////////
    std::cout << "######\n# 04 #\n######\n\nClass GenericPlayer:\n\n";

    std::cout << "Description above the function MAIN" << std::endl;

    std::cout << std::endl;


    return 0;
}

