#include <algorithm>
#include <iostream>
#include <cassert>
#include <vector>
#include <unordered_set>

// 01 //////////////////////////////

class ArrayInt
{
private:
    int m_length;
    int* m_data;

public:
    ArrayInt(): m_length(0), m_data(nullptr)
    {}

    ArrayInt(int length) : m_length(length)
    {
        assert(length >= 0);
        if (length > 0)
        {
            m_data = new int[length];
        }
        else
        {
            m_data = nullptr;
        }
    }

    ~ArrayInt()
    {
        delete[] m_data;
    }

    void erase()
    {
        delete[] m_data;
        m_data = nullptr;
        m_length = 0;
    }

    int getLength()
    {
        return m_length;
    }

    int& operator[](int index)
    {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

    void resize(int newLength)
    {
        if(newLength == m_length)
        {
            return;
        }
        if(newLength <= 0)
        {
            erase();
            return;
        }
        int *data = new int[newLength];

        if(m_length > 0)
        {
            int elementsToCopy = (newLength > m_length) ? m_length : newLength;

            for(int index=0; index < elementsToCopy ; ++index)
            {
                data[index] = m_data[index];
            }
        }
        delete[] m_data;
        m_data = data;
        m_length = newLength;
    }

    void insertBefore(int value, int index)
    {
        assert(index >= 0 && index <= m_length);
        int* data = new int[m_length+1];

        for(int before=0; before < index; ++before)
        {
            data[before] = m_data[before];
        }
        data [index] = value;

        for(int after=index; after < m_length; ++after)
        {
            data[after+1] = m_data[after];
        }
        delete[] m_data;
        m_data = data;
        ++m_length;
    }

    void push_back(int value)
    {
        insertBefore(value, m_length);
    }

    int pop_back()
    {
        assert(m_length > 0);
        return m_data[--m_length];
    }

    int pop_front()
    {
        assert(m_length > 0);
        int value = m_data[0];

        for(int index = 0; index < (m_length-1); ++index)
        {
            m_data[index] = m_data[index+1];
        }
        --m_length;
        return value;
    }

    void sort()
    {
        std::sort(m_data, (m_data+m_length));
    }

    void print() const
    {
        if(m_length <= 0)
        {
            std::cout  << "Array is empty." << std::endl;
        }

        for(int index = 0; index < m_length; ++index)
        {
            std::cout << m_data[index] << " ";
        }
        std::cout << std::endl;
    }
};



// 02 //////////////////////////////



// 03 //////////////////////////////

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


int main()
{
// 01 //////////////////////////////
    std::cout << "######\n# 01 #\n######\n\nClass ArrayInt:\n\n";

    ArrayInt arrayInt;
    arrayInt.push_back(100);
    arrayInt.push_back(0);
    arrayInt.push_back(1);
    arrayInt.push_back(10);

    arrayInt.print();
    arrayInt.sort();
    arrayInt.print();

    std::cout << std::endl;

    std::cout << arrayInt.pop_back() << " " << arrayInt.pop_front() << std::endl;

    std::cout << std::endl;

    arrayInt.print();

    std::cout << std::endl;

// 02  /////////////////////////////
    std::cout << "######\n# 02 #\n######\n\nVector:\n\n";

    std::vector<int> vec = {1,6,4,3,8,6,4,6,8,4,3,7,8,5,4};

    std::cout << "Unique numbers - " << std::unordered_set<int>(vec.cbegin(), vec.cend()).size() << std::endl;

    std::cout << std::endl;

// 03  /////////////////////////////
    std::cout << "######\n# 03 #\n######\n\nClass Hand:\n\n";

    Hand hand1;
    Card* c1 = new Card(NINE,CLUB,ON);
    Card* c2 = new Card(ACE,CLUB,ON);
    Card* c3 = new Card(FOUR,CLUB,ON);

    hand1.Add(c1);
    hand1.Add(c2);
    std::cout << *c1 << " + " << *c2 << std::endl;
    std::cout << "Value - " << hand1.GetValue() << std::endl;

    hand1.Add(c3);
    std::cout << *c1 << " + " << *c2 << " + " << *c3 << std::endl;
    std::cout << "Value - " << hand1.GetValue() << std::endl;

    hand1.Clear();
    std::cout << "Value - " << hand1.GetValue() << std::endl;

    std::cout << std::endl;


    return 0;
}

