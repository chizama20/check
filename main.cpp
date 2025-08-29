
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>


std::vector<std::string> shuffleCards(std::vector<std::string> cards){
    std::random_device rd;
    std::mt19937 g(rd()); 
    
    std::shuffle(cards.begin(), cards.end(), g);
    
    return cards;
}

void dishCards(std::vector<std::string> deck, std::vector<std::vector<std::string>>& players, int& deckIndex, std::string& top){
    int cardsRecieved{ 5 };

    for(auto& player:players){
        for(int i{0}; i<cardsRecieved; i++){
            player.push_back(deck[deckIndex++]);                   
        }
        
        top = deck[deckIndex];
        
        for(const auto& card:player){
            std::cout<<card<<" ";
        }
        std::cout<<"\n";
    }
    std::cout<< "start: "<< top << "\n";

}
void drawdeck(std::vector<std::string>& deck, int& deckIndex, std::vector<std::vector<std::string>>& players, int& playerIndex){    
    players[playerIndex].push_back(deck[deckIndex]);
    std::cout<<"\nPlayer drew";
}

void checkValidCard(std::string& newcard, std::string& top, std::vector<std::string>& deck, int deckIndex, std::vector<std::vector<std::string>>& players, int& playerIndex){
    if (newcard[0] == top[0] || newcard[1] == top[1]) {
        std::cout<<"\nPlayer played";
        top = newcard;
        //return true;
    } else {
        std::cout<<"Not valid card.";
        drawdeck(deck, deckIndex, players, playerIndex);  
        //return false;
}

}

std::string playTurn(std::vector<std::vector<std::string>>& players, int& playerIndex, std::string& top, std::vector<std::string>& deck, int& deckIndex){
    if (playerIndex >= players.size()) return "";

    std::string newcard;
    while (!players[playerIndex].empty())
    {
    
        std::cout<<"\nPlayer " << playerIndex+1 << " hand: ";
        for(const auto& card:players[playerIndex]){
        std::cout<<card<<" ";
        }
    
        std::cout<<"\nEnter card: ";
        std::cin>> newcard;
    
        auto it = (std::find(players[playerIndex].begin(), players[playerIndex].end(), newcard)); 
        if ( it == players[playerIndex].end()){
            std::cout<<"\nInvalid card or Card not in hand";
        }else{
            checkValidCard(newcard, top, deck, deckIndex, players, playerIndex);
            players[playerIndex].erase(it);            
            return newcard;
    
        }

    }
    std::cout<< "\nPlayer " << playerIndex+1 << " has no cards left!\n";
    return "";
}


int main()
{
    std::vector<std::string> cards = {"hK", "dK", "sK", "cK", 
                                        "hQ", "dQ", "sQ", "cQ", 
                                        "hP", "dP", "sP", "cP", 
                                        "hA", "dA", "sA", "cA", 
                                        "h2", "d2", "s2", "c2", 
                                        "h3", "d3", "s3", "c3", 
                                        "h4", "d4", "s4", "c4", 
                                        "h5", "d5", "s5", "c5", 
                                        "h6", "d6", "s6", "c6", 
                                        "h7", "d7", "s7", "c7", 
                                        "h8", "d8", "s8", "c8", 
                                        "h9", "d9", "s9", "c9", 
                                        "h10", "d10", "s10", "c10", 
                                        "rJ", "bJ"};
    std::vector<std::vector<std::string>> players;
    int playerIndex{ 0 };
    int numPlayers;                                    
    int deckIndex{0};
    std::string top;

    std::cout<<"Enter number of players: ";
    
    std::cin>>numPlayers;
    players.resize(numPlayers);

    std::vector<std::string> deck = shuffleCards(cards); 
    dishCards(deck, players, deckIndex, top);

    while(true){
        
        
        if (players[playerIndex].empty()) {
                std::cout << "Player " << playerIndex + 1 << " wins!\n";
                break;
        }
        else{
            playTurn(players, playerIndex, top, deck, deckIndex);
            std::cout << "\nTop of the deck: " << top << "\n";
            playerIndex = (playerIndex + 1) % players.size();
        }
        
        
    }

    return 0;
}

