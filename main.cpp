
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

void dishCards(std::vector<std::string> deck, std::vector<std::vector<std::string>> players, int deckIndex, std::vector<std::string> top){
    int cardsRecieved{ 7 };

    for(auto& player:players){
        for(int i{0}; i<cardsRecieved; i++){
            player.push_back(deck[deckIndex++]);                   
        }
        
        top.push_back(deck[deckIndex]);
        
        for(const auto& card:player){
            std::cout<<card<<" ";
        }
        std::cout<<"\n";
    }
    std::cout<<top.at(1);

}



void playCard(std::vector<std::vector<std::string>> players, int numPlayers){

    bool gameOn;

    while(gameOn){
        for(auto& player:players){

        }



    }
}

int main()
{
    std::vector<std::vector<std::string>> players;
    std::vector<std::string> cards = {"hK", "dK", "sK", "cK", 
                                        "hQ", "dQ", "sQ", "cQ", 
                                        "hP", "dP", "sP", "cP", 
                                        "hA", "dA", "sA", "cA", 
                                        "h1", "d1", "s1", "c1", 
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
                                        
    std::cout<<"Enter number of players: ";
    int numPlayers;
    std::cin>>numPlayers;
    players.resize(numPlayers);
    int deckIndex{0};
    std::vector<std::string> top;




    std::vector<std::string> deck = shuffleCards(cards); 
    dishCards(deck, players, deckIndex, top);

    return 0;
}


