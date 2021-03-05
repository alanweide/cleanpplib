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
        } else if(C.cardNum == 14){
            result = "Ace";
        } else{
            result = std::to_string(C.cardNum);
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
        } else if(cardNum == 14){
            result = "Ace";
        } else{
            result = "more than 14";
        }
        return result;
    }

    int getCardNum(){
        return cardNum;
    }

};

int main(){

    flex_queue<int> deck(linked_queue<int>{}), p1, p2;
    for(int i = 1; i < 30; i++){
            deck.enqueue(std::move(i));
    }

    // for(int j = 0; j < 44; j++){


        std::cout<<"Right before enqueueing, deck is: "<<std::endl;
        flex_queue<int> tempDeck;
        while(!deck.is_empty()){
            int temp = deck.dequeue();
            std::cout<<temp<<std::endl;

            tempDeck.enqueue(std::move(temp));
        }
        deck = std::move(tempDeck);



    //     Card deckCard = deck.dequeue();
    //     p1.enqueue( std::move(deckCard)) ;

    //     flex_queue<Card> temp;

    //     std::cout<<"p1 deck on iteration "<<j<<std::endl;

    //     while(!p1.is_empty()){

    //         Card temp1 = p1.dequeue();
    //         std::cout<<temp1<<std::endl;
    //         temp.enqueue(std::move(temp1));

    //     }
    //     p1 = std::move(temp);
    // }

    
}