#include <iostream>
#include <vector>

// 01 //////////////////////////////

bool isNomber(std::string str)
{
    size_t strlen = str.size();
    if(strlen == 0 || strlen > 11)
    {
        return 0;
    }
    for(size_t k = 0; k < strlen; ++k)
    {
        if((str[k] < '0' || str[k] > '9') && str[k] != '-')
        {
            return 0;
        }
    }
//    int number = atoi(str.c_str());                       // При необходимости ограничить диапазон
//    if(number < -1000 || number > 1000)                   // вводимых чисел разкомментировать
//    {
//        return 0;
//    }
    return 1;
}

int enterIntNumber()
{
    int result;
    std::string str;
    while(true)
    {
        std::cout << "Enter number:\n";
        std::cin.unsetf(std::ios::skipws);
        std::cin >> str;

        if(std::cin.good() && isNomber(str))
        {
            std::cin.ignore(11, '\n');
            result = atoi(str.c_str());
            break;
        }
        std::cin.clear();
        std::cin.ignore(11, '\n');
        std::cout << "Wrong input. Try again.\n";
    }
    return result;
}

// 02 //////////////////////////////

std::ostream& endll(std::ostream& os)
{
    os << "\n\n";
    return os;
}

// ////////////////////////////////

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
        cardsOnHand.shrink_to_fit();
    }
    std::vector<Card*> GetCards() const
    {
        return cardsOnHand;
    }
    uint16_t GetValue() const
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

    std::string GetName() const
    {
        return name;
    }

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

// 03  /////////////////////////////

class Player : public GenericPlayer
{
public:
    Player(std::string str) : GenericPlayer(str)
    {}
    virtual bool IsHitting() const
    {
        bool result;
        std::cout << "Another card? (y/n) ";
        bool notCorrectAnswer = true;
        while(notCorrectAnswer)
        {
            switch (std::cin.get())
            {
            case 'y':
                result = true;
                notCorrectAnswer = false;
                break;
            case 'n':
                result = false;
                notCorrectAnswer = false;
                break;
            default: std::cout << "Enter 'y' or 'n': ";
            }
        }
        return result;
    }
    void Win()
    {
        std::cout << this->GetName() << " WIN\n";
    }
    void Lose()
    {
        std::cout << this->GetName() << " LOSE\n";
    }
    void Push()
    {
        std::cout << this->GetName() << " PUSH\n";
    }
};

// 04 //////////////////////////////

class House : public GenericPlayer
{
public:
    House(std::string str) : GenericPlayer(str)
    {}
    virtual bool IsHitting() const
    {
        if(this->GetValue() <= 16)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void FlipFirstCard()
    {
        this->GetCards()[0]->Flip();
    }
};

// 05 //////////////////////////////

std::ostream& operator<<(std::ostream& os, const Card& c)
{
    if(c.GetVisible())
    {
        switch (c.GetValue())
        {
            case ACE: return os << 'A' << c.GetSuit(); break;
            case JACK: return os << 'J' << c.GetSuit(); break;
            case QUEEN: return os << 'Q' << c.GetSuit(); break;
            case KING: return os << 'K' << c.GetSuit(); break;
            default : return os << c.GetValue() << c.GetSuit();
        }

    }
    return os << "XX";
}

std::ostream& operator<<(std::ostream& os, const GenericPlayer& gp)
    {
        os << gp.GetName() << " - " ;
        for(size_t k = 0; k < gp.GetCards().size(); ++k)
        {
            os << *gp.GetCards()[k];
        }
        os << " - " << gp.GetValue();

        return os;
    }

int main()
{
// 01 //////////////////////////////
    std::cout << "######\n# 01 #\n######\n\nInt number:\n\n";

    int num = enterIntNumber();
    std::cout << "Your nomber is: " << num << std::endl;

    std::cout << std::endl;

// 02  /////////////////////////////
    std::cout << "######\n# 02 #\n######\n\nendll:\n\n";

    std::cout << "Begin" << endll << "End" << std::endl;

    std::cout << std::endl;

// 03-04  /////////////////////////////
    std::cout << "######\n# 03 #\n######\n\nClass Player & House:\n\n";

    Card c1(EIGHT, CLUB, ON);
    Card c2(KING, CLUB, ON);
    Card c3(EIGHT, CLUB, OFF);
    Card c4(KING, CLUB, OFF);

    Player pl1("Andrey");
    House h1("Computer");

    pl1.Add(&c1);
    pl1.Add(&c2);

    std::cout << pl1 << std::endl;

    h1.Add(&c3);
    h1.Add(&c4);

    std::cout << h1 << std::endl;

    h1.FlipFirstCard();

    std::cout << h1 << std::endl << "IsHitting - " << h1.IsHitting() << std::endl;


    std::cout << std::endl;

// 02  /////////////////////////////
    std::cout << "######\n# 05 #\n######\n\nOperator << overload:\n\n";

    std::cout << "Description above the function MAIN" << std::endl;

    std::cout << std::endl;


    return 0;
}

