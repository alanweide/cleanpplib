#include <stdlib.h>
#include <iostream>
#include <queue>
#include <string>
#include <ctime>

using namespace std;

class Card {

    int cardNum;

public:

    Card(){
        cardNum = 0;
    }

    Card(int card) : cardNum(card){}
    
    void operator = (const Card &C ){
        cardNum = C.cardNum;
    }

    friend std::ostream& operator<<(std::ostream& out, Card& C){
        std::string result;
        
        if(C.cardNum <= 10){
            result = std::to_string(C.cardNum);
        } else if(C.cardNum == 11){
            result = "Jack";
        } else if(C.cardNum == 12){
            result = "Queen";
        } else if(C.cardNum == 13){
            result = "King";
        } else {
            result = "Ace";
        }
        return out << result;
    }

    int getCardNum(){
        return cardNum;
    }

};


void populateDeck(queue<Card>& deck){

    for(int i = 0; i<13; i++)
    {
      for(int j = 0; j < 4; j++)
      {
        deck.push( Card(i + 2) );
      }
    }

}

//Define shuffle function
void shuffle(queue<Card>& deck, queue<Card>& p1, queue<Card>& p2){
    
    populateDeck(deck);

    //shuffle p1 deck
    for(int i = 0; i<26; i++) {
        srand((unsigned int) time(NULL));
        int posInMainDeck = rand() % 100;

        for(int i = 0; i < posInMainDeck; i++){
            deck.push(deck.front());
            deck.pop();
        }
        
        p1.push(deck.front());
        deck.pop(); 

        }

       //shuffle p2 deck
       for(int i = 0; i<26; i++){
            
            int posInMainDeck = rand() % 100;
            
            for(int i = 0; i < posInMainDeck; i++){
                deck.push(deck.front());
                deck.pop();
            }
            
            p2.push(deck.front());
            deck.pop();
                
        }
        
}

void war(queue<Card> p1, queue<Card> p2){

    while(p1.size() != 0 && p2.size() != 0){
        int input;
        std::cout<<"Press enter to draw a card"<<endl;
        getchar();

        Card p1Card, p2Card;

        p1Card = p1.front();
        p1.pop();
        p2Card = p2.front();
        p2.pop();
        

        std::cout<<"player one has played a "<<p1Card<<endl;
        std::cout<<"player two has played a "<<p2Card<<endl;

        if(p1Card.getCardNum() > p2Card.getCardNum()){
            
            std::cout<<"player one has won this round"<<endl;
            p1.push(p1Card);
            p1.push(p2Card);

        } else if(p2Card.getCardNum() > p1Card.getCardNum()){

            std::cout<<"player two has won this round"<<endl;
            p2.push(p2Card);
            p2.push(p1Card);

        } else{

            std::cout<<"tie. play three cards each, the third of which will determine who wins this round"<<endl;
            std::cout<<"Press enter to draw three cards"<<endl;
            getchar();

            queue<Card> p1TieCards, p2TieCards;
            Card p1TieBreaker, p2TieBreaker;

            int i = 0;

            while(p1.size() > 0 && i < 3){
                p1TieCards.push(p1.front());
                p1TieBreaker = p1.front();
                p1.pop();
                i++;
            }

            int j = 0;

            while(p2.size() > 0 && j < 3){
                p2TieBreaker = p2.front();
                p2TieCards.push(p2.front());
                p2.pop();
                j++;
            }

            if( p1.size() != 0 && p2.size() != 0 ){

                if(p1TieBreaker.getCardNum() > p2TieBreaker.getCardNum()){
                    std::cout<<"player 1 wins tiebreaker"<<endl;
                    p1.push(p1Card);
                    p1.push(p2Card);
                    
                    while(!p1TieCards.empty()){
                        p1.push(p1TieCards.front());
                        p1TieCards.pop();
                    }

                    while(!p2TieCards.empty()){
                        p1.push(p2TieCards.front());
                        p2TieCards.pop();
                    }
  
                } else if(p2TieBreaker.getCardNum() > p1TieBreaker.getCardNum()){
                    std::cout<<"player 2 wins tiebreaker"<<endl;
                    p2.push(p1Card);
                    p2.push(p2Card);
                    
                    while(!p2TieCards.empty()){
                        p2.push(p2TieCards.front());
                        p2TieCards.pop();
                    }

                    while(!p1TieCards.empty()){
                        p2.push(p1TieCards.front());
                        p1TieCards.pop();
                    }

                } else{
                    std::cout<<"tie again. split the cards evenly"<<endl;
                    p1.push(p1Card);

                    p2.push(p2Card);


                    while(!p1TieCards.empty()){
                        p1.push(p1TieCards.front());
                        p1TieCards.pop();
                    }

                    while(!p2TieCards.empty()){
                        p2.push(p2TieCards.front());
                        p2TieCards.pop();
                    }
                }
            } 
        }
    }

    std::cout<<endl;
    if(p1.size() > 0){
        std::cout<<"player one has won the game";
    } else if(p2.size() > 0){
        std::cout<<"player two has won the game";
    } else{
        std::cout<<"it's a draw";
    }
    std::cout<<endl;
}

int main(){

    queue<Card> deck, p1, p2;
    shuffle(deck, p1, p2);
    war(p1, p2);

}