#include "blackjack.h"


Card::Card(cardValue value, cardSuit suit) : value(value), suit(suit), visible(ON)
{}
void Card::Flip()
{
    visible = !visible;
}
uint16_t Card::GetValue() const
{
    return this->value;
}
uint8_t Card::GetSuit() const
{
    return this->suit;
}
bool Card::GetVisible() const
{
    return this->visible;
}



Hand::Hand()
{}
Hand::~Hand()
{}
void Hand::Add(Card* card)
{
    cardsOnHand.push_back(card);
}
void Hand::Clear()
{
    cardsOnHand.clear();
    cardsOnHand.shrink_to_fit();
}
std::vector<Card*> Hand::GetCards() const
{
    return cardsOnHand;
}
uint16_t Hand::GetValue() const
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



GenericPlayer::GenericPlayer(std::string name) : name(name)
{}
GenericPlayer::~GenericPlayer()
{}
//bool GenericPlayer::IsHitting() const =0;

std::string GenericPlayer::GetName() const
{
    return name;
}

bool GenericPlayer::IsBusted()
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
void GenericPlayer::Bust()
{
    std::cout << " bust";
}



Player::Player(std::string str) : GenericPlayer(str)
{}
bool Player::IsHitting() const
{
    bool result;
    std::cout << '\n' << this->GetName() << ". Another card? (y/n): ";
    bool notCorrectAnswer = true;
    std::string answer;
    while(notCorrectAnswer)
    {
        std::cin >> answer;
        switch (answer.at(0))
        {
        case 'y':
            result = true;
            notCorrectAnswer = false;
            break;
        case 'n':
            result = false;
            notCorrectAnswer = false;
            break;
        default:
            std::cout << " (y/n): ";
            break;
        }
    }
    return result;
}
void Player::Win()
{
    std::cout << "Player " << this->GetName() << " WIN\n";
}
void Player::Lose()
{
    std::cout << "Player " << this->GetName() << " LOSE\n";
}
void Player::Push()
{
    std::cout << "Player " << this->GetName() << " PUSH\n";
}



House::House() : GenericPlayer("Dealer")
{}
bool House::IsHitting() const
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
void House::FlipFirstCard()
{
    this->cardsOnHand[0]->Flip();
}


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

    return os;
}


Deck::Deck ()
{
    cardsOnHand.reserve(52);
    Populate();
}
Deck::~Deck ()
{
    cardsOnHand.clear();
    cardsOnHand.shrink_to_fit();
}
void Deck::Populate()
{
    Clear();
    for(int s = CLUB; s <= SPADE; ++s)
    {
        for(int v = ACE; v <= KING; ++v)
        {
            Add(new Card(static_cast<cardValue> (v), static_cast<cardSuit> (s)));
        }
    }
}
void Deck::Shuffle()
{
    std::random_shuffle(cardsOnHand.begin(), cardsOnHand.end());
}
void Deck::Deal(Hand& hand)
{
    if(!cardsOnHand.empty())
    {
        hand.Add(cardsOnHand.back());
        cardsOnHand.pop_back();
    }
    else
    {
        std::cout <<"Out of cards. Unable to deal.";
    }
}
void Deck::AddltionalCards (GenericPlayer& generlcPlayer)
{
    while(generlcPlayer.IsHitting())
    {
        Deal(generlcPlayer);
        std::cout << generlcPlayer << " - " << generlcPlayer.GetValue();
    }
}


Game::Game(std::vector<std::string>& names)
{
    for(size_t k = 0; k < names.size(); ++k)
    {
        players.push_back(names.at(k));
    }
    deck.Shuffle();
}
Game::~Game()
{
    players.clear();
    players.shrink_to_fit();
}
void Game::printTable()
{
    system("cls");
    std::cout << house << " - ";
    if(house.GetCards().at(0)->GetVisible())
    {
        if(house.IsBusted())
        {
            house.Bust();
        }
        else
        {
            std::cout << house.GetValue();
        }
    }
    std::cout<< "\n\n\n|| ";
    for(size_t k = 0; k < players.size(); ++k)
    {
        std::cout << players.at(k) << " - ";
        if(players.at(k).GetCards().at(0)->GetVisible())
        {
            if(players.at(k).IsBusted())
            {
                players.at(k).Bust();
            }
            else
            {
                std::cout << players.at(k).GetValue();
            }
        }
        std::cout << "  ||  ";
    }
    std::cout << std::endl;
}
void Game::Play()
{
    for(size_t k = 0; k < players.size(); ++k)
    {
        deck.Deal(players.at(k));
        deck.Deal(players.at(k));
    }
    deck.Deal(house);
    deck.Deal(house);
    house.FlipFirstCard();

    printTable();

    for(size_t k = 0; k < players.size(); ++k)
    {
        deck.AddltionalCards(players.at(k));
        printTable();

    }
    house.FlipFirstCard();
    printTable();
    deck.AddltionalCards(house);
    printTable();

    for(size_t k = 0; k < players.size(); ++k)
    {
        if(((house.GetValue() > 21) || (house.GetValue() < players.at(k).GetValue())) && (players.at(k).GetValue() < 22) )
        {
            std::cout << std::endl;
            players.at(k).Win();
        }
        else if((house.GetValue() == players.at(k).GetValue()) && (players.at(k).GetValue() < 22))
        {
            std::cout << std::endl;
            players.at(k).Push();
        }
        else
        {
            std::cout << std::endl;
            players.at(k).Lose();
        }
    }
    house.Clear();
    for(size_t k = 0; k < players.size(); ++k)
    {
        players.at(k).Clear();
    }
}
void Game::RenewDeck()
{
    deck.Populate();
    deck.Shuffle();
}
