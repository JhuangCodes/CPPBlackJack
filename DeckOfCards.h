#include<iostream>
#include<ctime>
#include<cstdlib>
#include<vector>
#include "Card.h"
using namespace std;
class DeckOfCards {
    public:
    vector<Card> deck; // Vector of cards

     void CreateDeckOfCards() { //creates an order pair of cards as number values and suits
    // 0 = Hearts, 1 = Diamonds, 2 = Clubs, 3 = Spades
    // 1 = Ace, 2 = 2, 3 = 3, 4 = 4, 5 = 5, 6 = 6, 7 = 7, 8 = 8, 9 = 9, 10 = 10, 11 = Jack, 12 = Queen, 13 = King
        for (int i = 1; i <= 13; i++) {
            for (int j = 0; j < 4; j++) {
                deck.push_back(Card(i, j));
            }
        
        }

    }

    void ShuffleDeckOfCards() { //shuffled the deck of cards using the random function
        //THIS METHOD ONLY WORKS IF YOU HAVE DECLARED A DECK OF CARDS
        srand(time(0));
        for (int i = 0; i < deck.size(); i++) {
            int j = rand() % deck.size();
            swap(deck[i], deck[j]);
        }
    }
    void DisplayStartUp() { // displays the welcome message and begins the st
        cout << "Welcome to BlackJack!" << endl;
        cout << "Get as close to 21 or better than the dealer without going over 21!" << endl;
        cout << "Good luck!" << endl;
    }

    string DisplayCard(Card c) { //displays the card in a readable format
    // The format will ALWAYS be "Face of Suit"
        string face;
        string suit;
        if (c.face == 1) {
            face = "Ace";
        } else if (c.face == 11) {
            face = "Jack";
        } else if (c.face == 12) {
            face = "Queen";
        } else if (c.face == 13) {
            face = "King";
        }
        else if (c.face == 14)
        {
            face = "Ace";
        }
        else {
            face = to_string(c.face);
        }
        if (c.suit == 0) {
            suit = "Hearts";
        } else if (c.suit == 1) {
            suit = "Diamonds";
        } else if (c.suit == 2) {
            suit = "Clubs";
        } else {
            suit = "Spades";
        }
        return face + " of " + suit;
    }

    int getCardValue(Card c) { //gets the value of the card
    // 1= Ace, 2 = 2, 3 = 3, 4 = 4, 5 = 5, 6 = 6, 7 = 7, 8 = 8, 9 = 9, 10 = 10, 11 = Jack, 12 = Queen, 13 = King 14 = "11 Ace"
        if(c.face>=10 && c.face<=14){ //Face Cards are always going to be the value of 10
            return 10;
        }
        else if (c.face == 14){
            return 11;
        }
        else{
            return c.face;
        }
    }

    int addCardValues(vector<Card> hand) { //adds the values of the cards in the hand
        int sum = 0;
        for (int i = 0; i < hand.size(); i++) {
            sum += getCardValue(hand[i]);
        }
        return sum;
    }

    void DealCards(vector<Card>& playerHand, vector<Card>& dealerHand, vector<Card>& deck) { //deals the cards to the player and dealer
        playerHand.push_back(deck[0]); //adds the first card to the player's hand
        deck.erase(deck.begin()); //removes the first card from the deck
        playerHand.push_back(deck[0]); //adds the second card to the player's hand
        deck.erase(deck.begin()); //removes the second card from the deck
        dealerHand.push_back(deck[0]); //adds the first card to the dealer's hand
        deck.erase(deck.begin()); //removes the first card from the deck
        dealerHand.push_back(deck[0]); //adds the second card to the dealer's hand
        deck.erase(deck.begin()); //removes the second card from the deck
    }
    void displayDealerHand(vector<Card>& dealerHand) { //displays the dealer's hand
        cout << "Dealer's hand: ";
        string DealerHand = "";
        for (int i = 0; i < dealerHand.size()-1; i++) {
           DealerHand += DisplayCard(dealerHand[i]) + " | ";
        }
        cout << DealerHand << "Hidden Card" << endl;
    }
    void displayPlayerHand(vector<Card>& playerHand) { //displays the player's hand
        cout << "Your hand: ";
        string PlayerHand = "";
        for (int i = 0; i < playerHand.size(); i++) {
            PlayerHand += DisplayCard(playerHand[i]) + " | ";
        }
        cout << PlayerHand << endl;
    }

    void Hit(vector<Card>& playerHand, vector<Card>& deck, int& PlayerHandTotalValue) { //adds a card to the player's hand
            playerHand.push_back(deck[0]); //adds a card to the player's hand
            cout << "You drew a " << DisplayCard(playerHand[playerHand.size()-1]) << endl; //displays the card that the player drew
            deck.erase(deck.begin()); //removes the card from the deck
            cout << "Your hand: ";
            for(int i = 0; i < playerHand.size(); i++){
                if(playerHand[i].face == 1){

                    string AceChoice;
                    cout << "Would you like your Ace to be a 1 or 11? 1 = 1 || 11 = 11" << endl;
                    cin >> AceChoice;

                    if (AceChoice == "1"){
                        playerHand[i].face = 1;
                            
                    }
                    else if (AceChoice == "11"){
                           playerHand[i].face = 14;    
                    }
                }
                    
                    PlayerHandTotalValue = addCardValues(playerHand); //gets the total value of the player's hand
                    cout << DisplayCard(playerHand[i]) << " | ";


            }
    }
    void HitStand(int PlayerHandTotalValue, int DealerHandTotalValue, vector<Card>& playerHand, vector<Card>& dealerHand) { //asks the player if they want to hit or stay
        string OfferChoice = "Would you like to hit or stay? H = Hit || S = Stay"; //asks the player if they want to hit or stay
        cout << endl << OfferChoice << endl; //asks the player if they want to hit or stay
        char choice;
        cin >> choice;
        while (choice == 'H' || choice == 'h') { //if the player chooses to hit
            Hit(playerHand, deck, PlayerHandTotalValue); //adds a card to the player's hand
            if (PlayerHandTotalValue > 22) { //if the player's hand is over 21
                cout << "You busted! You lose!" << endl; //displays that the player busted
                return; //ends the game
            }
            cout << endl << OfferChoice << endl; //asks the player if they want to hit or stay
            cin >> choice; //gets the player's choice
        }
        if (choice == 'S' || choice == 's') { //if the player chooses to stay
        
            for(int i = 0; i < playerHand.size(); i++){
                if(playerHand[i].face == 1){

                    string AceChoice;
                    cout << "Would you like your Ace to be a 1 or 11? 1 = 1 || 11 = 11" << endl;
                    cin >> AceChoice;

                    if (AceChoice == "1"){
                        playerHand[i].face = 1;
                            
                    }
                    else if (AceChoice == "11"){
                           playerHand[i].face = 14;    
                    }
                    }
                }
            
            cout << "Your hand: ";
        
            for (int i = 0; i < playerHand.size(); i++) {
                cout << DisplayCard(playerHand[i]) << " | "; //displays the player's hand
            }
            cout << endl;
            cout << "Dealer's hand: ";
            for (int i = 0; i < dealerHand.size(); i++) {
                cout << DisplayCard(dealerHand[i]) << " | "; //displays the dealer's hand
            }
            cout << endl;
            while (DealerHandTotalValue < 17) { //if the dealer's hand is less than 17
                dealerHand.push_back(deck[0]); //adds a card to the dealer's hand
                cout << "Dealer drew a " << DisplayCard(dealerHand[dealerHand.size()-1]) << endl; //displays the card that the dealer drew
                deck.erase(deck.begin()); //removes the card from the deck
                DealerHandTotalValue = addCardValues(dealerHand); //gets the total value of the dealer's hand
            }
            cout << "Dealer's hand: ";
            for (int i = 0; i < dealerHand.size(); i++) {
                cout << DisplayCard(dealerHand[i]) << " | "; //displays the dealer's hand
            }
            cout << endl;
            if (DealerHandTotalValue > 21) { //if the dealer's hand is over 21

                cout << "Dealer busted! You win!" << endl; //displays that the dealer busted
            } else if (PlayerHandTotalValue > DealerHandTotalValue) { //if the player's hand is greater than the dealer's hand
                cout << "You win!" << endl; //displays that the player wins
            } else if (PlayerHandTotalValue < DealerHandTotalValue) { //if the player's hand is less than the dealer's hand
                cout << "You lose!" << endl; //displays that the player loses
            } else { //if the player's hand is equal to the dealer's hand
                cout << "It's a tie!" << endl; //displays that it's a tie
            }
        }
    }
    void playGame() { //playst the game
        CreateDeckOfCards(); //creates the ordered deck of cards for the game
        ShuffleDeckOfCards(); // shuffles that deck of cards
        vector<Card> playerHand; //vector of cards for the player
        vector<Card> dealerHand; //vector of cards for the dealer
        DealCards(playerHand, dealerHand, deck); //deals the cards to the player and dealer
        DisplayStartUp(); //displays the welcome message
        displayPlayerHand(playerHand); //displays the player's hand
        displayDealerHand(dealerHand); //displays the dealer's hand
        HitStand(addCardValues(playerHand), addCardValues(dealerHand), playerHand, dealerHand); //asks the player if they want to hit or stay
    }
};
