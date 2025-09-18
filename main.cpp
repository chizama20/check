
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
    Card(char s, const std::string& rank) : suit(s), rank(rank){}
    
    std::string toString() const{
        return std::string(1, suit) + rank;
    } // combine suit and rank in one string
    
    static Card fromString(const std::string& s){
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
        return c; // draw card function, we also have to add it  to the discard pile, probably in the game class
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
        for(const auto& card : hand){
            if(card.toString() == c.toString()){
                return true;
            }
        }
        return false;
    }

    bool removeCard(const Card& c){
        for(auto it = hand.begin(); it != hand.end(); it++){
            if(it->toString() == c.toString()){
                hand.erase(it);
                return true;
            }
        }
        return false;
    }               // returns true if removed
   
    void printHand() const{
        std::cout<< "Player " << id << " hand: ";
        for(const auto& card : hand){
            std::cout<< card.toString() << " ";
        }
        std::cout<<"\n";
    }

    bool empty(){
        return hand.empty();
    }

};

class Game {
private:
    Deck deck;
    std::vector<Card> discardPile;      
    std::vector<Player> players;     
    int currentPlayerIndex{0};  
    Card top = Card('x', "o"); // top card placeholder
    char currentSuit;

public:
    Game(int numPlayers) {
        for (int i = 0; i < numPlayers; i++) {
            players.emplace_back(i + 1);
        }
        deck.shuffleCards();
    }

    void start() {
        int cardsRecieved{5};
        for (auto& player : players) {   
            player.drawFromDeck(deck, cardsRecieved);                   
        }
        top = deck.draw();
        discardPile.push_back(top);
        currentSuit = top.toString()[0];

        std::cout << "\nStarting card: " << top.toString() << "\n";
    }

    void play() {
        while (true) {
            Player& player = players[currentPlayerIndex];
            player.printHand();

            std::string input;
            std::cout << "Enter Card or + to draw: ";
            std::cin >> input;

            if (input == "+") {
                player.drawFromDeck(deck, 1);
                nextTurn();
                std::cout << "\nTOP: " << top.toString() << "\n";
            } else {
                Card move = Card::fromString(input);

                if (!(move.toString()[0] == currentSuit || 
                      move.toString().substr(1) == top.toString().substr(1) || 
                      move.isSpecial())) {
                    std::cout << "Invalid Card. Try again\n";
                } else {
                    // Remove card + update discard pile
                    player.removeCard(move);
                    discardPile.push_back(move);
                    top = move;
                    currentSuit = top.toString()[0];

                    if (move.isSpecial()) {
                        std::string rank = move.toString().substr(1);

                        if (rank == "7") {
                            std::cout << "Next player draws 2!\n";
                            nextTurn();
                            players[currentPlayerIndex].drawFromDeck(deck, 2);

                        } else if (rank == "A") {
                            std::cout << "Skip!\n";
                            nextTurn(); // skip once
                            nextTurn(); // skip again

                        } else if (rank == "P") {
                            std::cout << "J COMMAND!!! Command a suit (h, d, s, c): ";
                            char chosenSuit;
                            std::cin >> chosenSuit;

                            while (chosenSuit != 'h' && chosenSuit != 'd' &&
                                   chosenSuit != 's' && chosenSuit != 'c') {
                                std::cout << "Invalid suit! Choose h, d, s, or c: ";
                                std::cin >> chosenSuit;
                            }

                            currentSuit = chosenSuit;  
                            std::cout << "Next player must play a card of suit " 
                                      << currentSuit << "\n";
                            nextTurn();

                        } else if (rank == "J") {
                            std::cout << "Next player draws 4!\n";
                            nextTurn();
                            players[currentPlayerIndex].drawFromDeck(deck, 4);
                        }
                    } else {
                        std::cout << "Player played " << move.toString() << ".\n";
                        nextTurn();
                    }

                    if (player.empty()) {
                        std::cout << "Player " << currentPlayerIndex + 1 << " wins!\n";
                        break;
                    }
                }

                std::cout << "\nTOP: " << top.toString() << "\n";
            }
        }
    }

    void nextTurn() {
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    }
};



int main()
{

    int numplayers;
    std::cout<<"Enter number of players: ";
    std::cin>>numplayers;
    Game game(numplayers);

    game.start();
    game.play();
    

    return 0;
}


