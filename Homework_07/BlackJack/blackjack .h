#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <windows.h>

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
    Card(cardValue value, cardSuit suit);

    void Flip();

    uint16_t GetValue() const;

    uint8_t GetSuit() const;

    bool GetVisible() const;

};

class Hand
{
protected:
    std::vector<Card*> cardsOnHand;
public:
    Hand();
    virtual ~Hand();

    void Add(Card* card);

    void Clear();

    std::vector<Card*> GetCards() const;

    uint16_t GetValue() const;

};

class GenericPlayer : public Hand
{
private:
    std::string name;
public:
    GenericPlayer(std::string name);
    virtual ~GenericPlayer();

    virtual bool IsHitting() const =0;

    std::string GetName() const;

    bool IsBusted();

    void Bust();
};

class Player : public GenericPlayer
{
public:
    Player(std::string str);

    virtual bool IsHitting() const;

    void Win();

    void Lose();

    void Push();
};

class House : public GenericPlayer
{
public:
    House();

    virtual bool IsHitting() const;

    void FlipFirstCard();
};

class Deck : public Hand
{
public:
    Deck ();
    ~Deck ();

    void Populate();

    void Shuffle();

    void Deal(Hand& hand);

    void AddltionalCards (GenericPlayer& generlcPlayer);
};

class Game
{
private:
    Deck deck;
    House house;
    std::vector<Player> players;
public:
    Game(std::vector<std::string>& names);
    ~Game();

    void printTable();

    void Play();

    void RenewDeck();

};


#endif // BLACKJACK_H
