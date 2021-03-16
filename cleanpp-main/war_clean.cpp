#include <memory>
#include <iostream>
#include "template_integer.hpp"
#include "flexible_integer.hpp"
#include "nn_integer.hpp"
#include "bounded_nn.hpp"
#include "vector_integer.hpp"
#include "template_queue.hpp"
#include "flexible_queue.hpp"
#include "linked_queue.hpp"
#include "array_queue.hpp"
#include "array_stack.hpp"
#include "template_list.hpp"
#include "flexible_list.hpp"
#include "stack_based_list.hpp"
#include "natural_number.hpp"
#include <queue>
#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace cleanpp;

class Card {

    int cardNum;

public:

    Card(){
        cardNum = 0;
    }

    Card(int card) : cardNum(card){}
    
    Card(Card const &C ) = delete;

    Card(Card&& C){
        cardNum = std::move(C.cardNum);
    }

    void operator = (const Card& C) = delete;

    void operator = (Card&& C ){
        cardNum = std::move(C.cardNum);
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


    std::string getCard(){
        
        std::string result;

        if(cardNum <= 10){
            result = std::to_string(cardNum);
        } else if(cardNum == 11){
            result = "Jack";
        } else if(cardNum == 12){
            result = "Queen";
        } else if(cardNum == 13){
            result = "King";
        } else {
            result = "Ace";
        }
        return result;
    }

    int getCardNum(){
        return cardNum;
    }

};


flex_queue<Card> populateDeck(flex_queue<Card> deck){

    for(int i = 0; i<13; i++)
    {
      for(int j = 0; j < 4; j++)
      {
        deck.enqueue( Card(i + 2) );
      }
    }

    return deck;
}

//Define shuffle function
std::tuple<flex_queue<Card>, flex_queue<Card>, flex_queue<Card>> shuffle(flex_queue<Card> deck, flex_queue<Card> p1, flex_queue<Card> p2)
{

    srand((unsigned int) time(NULL));
    deck = populateDeck(std::move(deck));

        //shuffle p1 deck
       for(int i = 0; i<26; i++) {
    
            int posInMainDeck = rand() % 100;

            for(int i = 0; i < posInMainDeck; i++){
                deck.enqueue(deck.dequeue());
            }
            
            p1.enqueue(deck.dequeue());


        }//end for

       //shuffle p2 deck
       for(int i = 0; i<26; i++){
            
            int posInMainDeck = rand() % 29;
            
            for(int i = 0; i < posInMainDeck; i++){
                deck.enqueue(deck.dequeue());
            }
            
            p2.enqueue(deck.dequeue());
                
        }
        
    return std::make_tuple(std::move(deck), std::move(p1), std::move(p2));

}

void war(flex_queue<Card> p1, flex_queue<Card> p2){
        
    while(!p1.is_empty() && !p2.is_empty()){
        int input;
        std::cout<<"Press enter to draw a card"<<std::endl;
        getchar();

        Card p1Card, p2Card;

        p1Card = p1.dequeue();
        
        p2Card = p2.dequeue();

        

        std::cout<<"player one has played a "<<p1Card<<std::endl;
        std::cout<<"player two has played a "<<p2Card<<std::endl;

        

        if(p1Card.getCardNum() > p2Card.getCardNum()){
            
            std::cout<<"player one has won this round"<<std::endl;
            p1.enqueue(std::move(p1Card));
            p1.enqueue(std::move(p2Card));

        } else if(p2Card.getCardNum() > p1Card.getCardNum()){

            std::cout<<"player two has won this round"<<std::endl;
            p2.enqueue(std::move(p2Card));
            p2.enqueue(std::move(p1Card));

        } else{



            std::cout<<"tie. play three cards each, the third of which will determine who wins this round"<<std::endl;
            std::cout<<"Press enter to draw three cards"<<std::endl;
            getchar();

            flex_queue<Card> p1TieCards, p2TieCards;
            int p1TieBreaker, p2TieBreaker;

            int i = 0;

            while(!p1.is_empty() && i < 3){
                Card front = p1.dequeue();
                p1TieBreaker = front.getCardNum();
                p1TieCards.enqueue(std::move(front));
                i++;
            }

            int j = 0;

            while(!p2.is_empty() && j < 3){
                Card front = p2.dequeue();
                p2TieBreaker = front.getCardNum();
                p2TieCards.enqueue(std::move(front));
                j++;
            }

            if( !p1.is_empty() && !p2.is_empty() ){

                   if(p1TieBreaker > p2TieBreaker){
                    std::cout<<"player 1 wins tiebreaker"<<std::endl;
                    p1.enqueue(std::move(p1Card));
                    p1.enqueue(std::move(p2Card));
                    
                    while(!p1TieCards.is_empty()){
                        p1.enqueue(p1TieCards.dequeue());
                    }


                    while(!p2TieCards.is_empty()){
                        p1.enqueue(p2TieCards.dequeue());
                    }

                    
                } else if(p2TieBreaker > p1TieBreaker){
                    std::cout<<"player 2 wins tiebreaker"<<std::endl;
                    p2.enqueue(std::move(p1Card));
                    p2.enqueue(std::move(p2Card));
                    
                    while(!p2TieCards.is_empty()){
                        p2.enqueue(p2TieCards.dequeue());
                    }

                    while(!p1TieCards.is_empty()){
                        p2.enqueue(p1TieCards.dequeue());
                    }


                } else{
                    std::cout<<"tie again. split the cards evenly"<<std::endl;
                    p1.enqueue(std::move(p1Card));

                    p2.enqueue(std::move(p2Card));


                    while(!p1TieCards.is_empty()){
                        p1.enqueue(p1TieCards.dequeue());
                    }

                    while(!p2TieCards.is_empty()){
                        p2.enqueue(p2TieCards.dequeue());
                    }
                }

            }

        }
    }
    
    std::cout<<std::endl;
    if(!p1.is_empty()){
        std::cout<<"player one has won the game";
    } else if( !p2.is_empty() ){
        std::cout<<"player two has won the game";
    } else{
        std::cout<<"it's a draw";
    }
    std::cout<<std::endl;
}

int main(){

    flex_queue<Card> deck, p1, p2;
    std::tie(deck, p1, p2) = shuffle(std::move(deck), std::move(p1), std::move(p2));
    war(std::move(p1), std::move(p2));

}
