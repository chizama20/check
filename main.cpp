
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

struct Card
{
private:
    char suit;
    std::string rank;
    
public:
    Card(char s, std::string rank) : suit(s), rank(rank){}
    
    std::string toString() const{
        return std::string(1, suit) + rank;
    } // combine suit and rank in one string
    
    static Card fromString(std::string& s){
        char suit = s[0];
        std::string rank = s.substr(1);
        return Card(suit, rank);
    } // turns the string into a card object (struct)
    
    bool match(const Card& other) const{
        return (suit == other.suit || rank == other.rank);
    }

    bool isSpecial() const{
        return (rank == "7" || rank == "A" || rank == "J" || rank == "P" );
    }
};


class Deck{
private:
    std::vector<Card> deck;
    

public:
    Deck(){
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
            
            for(const auto& card:cards){
                deck.push_back(Card::fromString(card));
            }
    }
    
    void shuffleCards(){
        std::random_device rd;
        std::mt19937 g(rd()); 
        
        std::shuffle(deck.begin(), deck.end(), g);
    }

    Card draw(){
        Card c = deck.back();
        deck.pop_back();
        return c;
    }

    bool empty(){
        return deck.empty();
    }

    int size(){
        return deck.size();
    }




};

class Player{

private:
    int id;
    std::vector<Card> hand;

public:
    Player(int id) : id(id){}
    
    void drawFromDeck(Deck& deck, int n = 1){
        for(int i=0; i<n; i++){
            if(deck.empty()) break;

            hand.push_back(deck.draw());
        }
    }     // draws n cards into hand
    
    bool hasCard(const Card& c) const{
        return 
    }
    bool removeCard(const Card& c);               // returns true if removed
    void printHand() const;
    
};


class Game {
private:
    std::vector<Card> deck;      
    int deckIndex{0};    
    std::vector<Card> discardPile;   
    std::vector<Player> players;     
    int currentPlayerIndex{0};  
    Card top;        

public:
    Game(int numPlayers);

    void start(){

        int cardsRecieved{ 5 };
        for(auto& player:players){
            for(int i{0}; i<cardsRecieved; i++){
                player.push_back(deck[deckIndex++]);                   
            }
            
            top = deck[deckIndex];

            /* for(const auto& card:player){
                std::cout<<card<<" ";
            }*/
            std::cout<<"\n";
        }
        std::cout<< "start: "<< top << "\n";
        }    // deal cards, set up first card

    void play(){

        std::string makeMove;
        while (!players[currentPlayerIndex].empty())
        {
        
            std::cout<<"\nPlayer " << currentPlayerIndex+1 << " hand: ";
            for(const auto& card:players[currentPlayerIndex]){
                std::cout<<card<<" ";
            }
            
            std::cin>> makeMove;  // making move & checking valid card
            auto it = (std::find(players[currentPlayerIndex].begin(), players[currentPlayerIndex].end(), makeMove)); 
            if ( it == players[currentPlayerIndex].end()){
                std::cout<<"\nInvalid card or Card not in hand";
                return "";
            }else{
                if(checkValidCard(makeMove, top, discardPile)){
                    players[playerIndex].erase(it);            
                    return makeMove;
                }else{
                    std::cout<<"Drawing due to invalid move....";
                    drawdeck(deck, deckIndex, players, playerIndex);
                    return "";
                }    
            }

        }
        std::cout<< "\nPlayer " << playerIndex+1 << " has no cards left!\n";
        return "";
    
    }     // main game loop
    void nextTurn(); // go to next player
};



std::vector<std::string> shuffleCards(std::vector<std::string> cards){
    std::random_device rd;
    std::mt19937 g(rd()); 
    
    std::shuffle(cards.begin(), cards.end(), g);
    
    return cards;
}

void dishCards(std::vector<std::string>& deck, std::vector<std::vector<std::string>>& players, int& deckIndex, std::string& top){
    int cardsRecieved{ 5 };

    for(auto& player:players){
        for(int i{0}; i<cardsRecieved; i++){
            player.push_back(deck[deckIndex++]);                   
        }
        
        top = deck[deckIndex];
        
        /* for(const auto& card:player){
            std::cout<<card<<" ";
        }*/
        std::cout<<"\n";
    }
    std::cout<< "start: "<< top << "\n";

}
void drawdeck(std::vector<std::string>& deck, int& deckIndex, std::vector<std::vector<std::string>>& players, int& playerIndex){    
    
    if(deckIndex>=deck.size()){    
        std::cout<<"\nDeck is empty!";
        return;    
    } 
    players[playerIndex].push_back(deck[deckIndex]);
    std::cout<<"\nPlayer drew";
    ++deckIndex;
}

std::string cardPlayed(std::string& makeMove, std::vector<std::vector<std::string>>& players, int& playerIndex, std::vector<std::string>& deck, int& deckIndex){
    char rank = makeMove.back();

    if(rank == '7'){
        for(auto& card:deck[deckIndex]{
        })
        return "DRAW2";
    }else if(rank == 'A'){
        ++playerIndex;
        return "SKIP";
    }else if(rank == 'J'){
        return "DRAW4";
    }

    return "";
}

bool checkValidCard(std::string& makeMove, std::string& top, std::vector<std::string>& discardPile){
    if (makeMove[0] == top[0] || makeMove[1] == top[1]) {
    /*    std::cout<<"\nPlayer played";
        discardPile.push_back(top);
        top = makeMove;  */  
        return true;   
    } else {
        return false;
}

}

std::string playTurn(std::vector<std::vector<std::string>>& players, int& playerIndex, std::string& top, std::vector<std::string>& deck, int& deckIndex, std::vector<std::string>& discardPile){
    if (playerIndex >= players.size()) return "";

    std::string makeMove;
    while (!players[playerIndex].empty())
    {
    
        std::cout<<"\nPlayer " << playerIndex+1 << " hand: ";
        for(const auto& card:players[playerIndex]){
            std::cout<<card<<" ";
        }
    
        std::cout<<"\nEnter Card \nDraw Deck '+' \nCall Check '!'\n\n--> ";
        std::cin>> makeMove;
        
        if(makeMove == "+"){
            drawdeck(deck, deckIndex, players, playerIndex);
            return "";    
        }else if(makeMove == "!"){
            std::cout<<"\nCHECK!!\n";
            return "";    
        }else if (makeMove == checkSpecial(makeMove)){
            std::cout<<"Special used";
        }
        
        auto it = (std::find(players[playerIndex].begin(), players[playerIndex].end(), makeMove)); 
        if ( it == players[playerIndex].end()){
            std::cout<<"\nInvalid card or Card not in hand";
            drawdeck(deck, deckIndex, players, playerIndex);
            return "";
        }else{
            if(checkValidCard(makeMove, top, discardPile)){
                players[playerIndex].erase(it);            
                return makeMove;
            }else{
                std::cout<<"Drawing due to invalid move....";
                drawdeck(deck, deckIndex, players, playerIndex);
                return "";
            }    
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
    std::vector<std::string> discardPile;

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
            playTurn(players, playerIndex, top, deck, deckIndex, discardPile);
            std::cout << "\nTop of the deck: " << top << "\n";
            playerIndex = (playerIndex + 1) % players.size();
            if(deckIndex>= deck.size()){
                std::cout << "\nHol up ma niggas lemme reshuffle... \n";
                std::string keepTop = discardPile.back();
                discardPile.pop_back();
                
                deck = discardPile;
                shuffleCards(deck);  
                deckIndex = 0;

                discardPile.clear();
                discardPile.push_back(keepTop);
                top = keepTop;
            }
        }
        
        
    }

    return 0;
}

//