#include "blackjack.h"

// BLACK JACK //////////////////////////////

int main()
{

    std::cout << "######\n# 03 #\n######\n\nBlackjack:\n\n";

    std::vector<std::string> names;
    size_t nomberOfPlayers;
    std::string name;
    std::string answer;

    std::cout << "Enter nomber of players (1-4):" << std::endl;

    std::cin >> nomberOfPlayers;

    for(size_t k = 1; k <= nomberOfPlayers; ++k)
    {
        std::cout << "Enter #" << k << " player name:" << std::endl;
        std::cin >> name;
        names.push_back(name);
    }
    name.clear();
    name.shrink_to_fit();

    std::shared_ptr<Game> game(new Game(names));
    do
    {
        game->Play();

        std::cout << std::endl;

        std::cout << "Play again? (y/n)";

        std::cin >> answer;

        game->RenewDeck();
    }
    while(answer.at(0) != 'n');

    names.clear();
    names.shrink_to_fit();
    answer.clear();
    answer.shrink_to_fit();

    return 0;
}

