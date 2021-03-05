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
void shuffle(queue<Card>& deck, queue<Card>& p1, queue<Card>& p2)
{
    
    populateDeck(deck);

//shuffle p1 deck

   //this is the required for loop specified in the APP C38-1 write-up.
       for(int i = 0; i<26; i++) {
        srand((unsigned int) time(NULL));
        int posInMainDeck = (rand() % deck.size());

        for(int i = 0; i < posInMainDeck; i++){
            deck.push(deck.front());
            
            deck.pop();
        }
        
        p1.push(deck.front());
        deck.pop(); 

        

        }//end for

       //shuffle p2 deck
       for(int i = 0; i<26; i++){
            srand((unsigned int) time(NULL));
            int posInMainDeck = (rand() % deck.size());
            
            for(int i = 0; i < posInMainDeck; i++){
                deck.push(deck.front());
                deck.pop();
            }
            
            p2.push(deck.front());
            deck.pop();
                
        }
        

//end shuffling
}

void war(queue<Card> p1, queue<Card> p2){

    while(p1.size() != 0 && p2.size() != 0){
        int input;
        cout<<"Press enter to draw a card"<<endl;
        getchar();

        Card p1Card, p2Card;

        p1Card = p1.front();
        p1.pop();
        p2Card = p2.front();
        p2.pop();
        

        cout<<"player one has played a "<<p1Card<<endl;
        cout<<"player two has played a "<<p2Card<<endl;

        if(p1Card.getCardNum() > p2Card.getCardNum()){
            
            cout<<"player one has won this round"<<endl;
            p1.push(p1Card);
            p1.push(p2Card);

        } else if(p2Card.getCardNum() > p1Card.getCardNum()){

            cout<<"player two has won this round"<<endl;
            p2.push(p2Card);
            p2.push(p1Card);

        } else{

            cout<<"tie. play three cards each, the third of which will determine who wins this round"<<endl;
            cout<<"Press enter to draw three cards"<<endl;
            getchar();
            
            if( p1.size() >= 3 && p2.size() >= 3 ){
                Card tieCards[4];
                for(int i = 0; i < 4; i += 2){
                    tieCards[i] = p1.front();
                    p1.pop();
                    tieCards[i + 1] = p2.front();
                    p2.pop();
                }

                cout<<"p1 has played a "<<tieCards[0]<<", "<<tieCards[2]<<", and "<<p1.front()<<endl;
                cout<<"p2 has played a "<<tieCards[1]<<", "<<tieCards[3]<<", and "<<p2.front()<<endl;

                if(p1.front().getCardNum() > p2.front().getCardNum()){
                    cout<<"p1 wins tiebreaker"<<endl;
                    p1.push(p1Card);
                    p1.push(p2Card);
                    p1.push(p1.front());
                    p1.pop();
                    p1.push(p2.front());
                    p2.pop();
                    for(int i = 0; i < 4; i++){
                        p1.push(tieCards[i]);
                    }
                    
                } else if(p2.front().getCardNum() > p1.front().getCardNum()){
                    cout<<"p2 wins tiebreaker"<<endl;
                    p2.push(p1Card);
                    p2.push(p2Card);
                    p2.push(p2.front());
                    p2.pop();
                    p2.push(p1.front());
                    p1.pop();
                    for(int i = 0; i < 4; i++){
                        p2.push(tieCards[i]);
                    }
                } else{
                    cout<<"tie again. split the cards evenly"<<endl;
                    p1.push(p1Card);
                    p1.push(p1.front());
                    p1.pop();
                    p2.push(p2Card);
                    p2.push(p2.front());
                    p2.pop();

                    for(int i = 0; i < 4; i+=2){
                        p1.push(tieCards[i]);
                        p2.push(tieCards[i +  1]);
                    }
                }
            } else{

                
                if(p1.size() < 3){
                    cout<<"p1 does not have enough cards to complete the war";
                    while(p1.size() != 0){
                        p1.pop();
                    }
                }
                
                if(p2.size() < 3){
                    cout<<"p2 does not have enough cards to complete the war";
                    while(p2.size() != 0){
                        p2.pop();
                    }

                }

            }
            
            
        }
    }

    cout<<endl;

    if(p1.size() > 0){
        cout<<"player one has won the game";
    } else if(p2.size() > 0){
        cout<<"player two has won the game";
    } else{
        cout<<"it's a draw";
    }
    cout<<endl;
}

int main(){

    queue<Card> deck, p1, p2;
    shuffle(deck, p1, p2);
    war(p1, p2);

}