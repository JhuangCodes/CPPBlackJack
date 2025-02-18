#include<iostream>
#include<ctime>
#include<cstdlib>
#include<vector>
using namespace std;
class Card {
    public:
    int face; // 1 = Ace, 2 = 2, 3 = 3, 4 = 4, 5 = 5, 6 = 6, 7 = 7, 8 = 8, 9 = 9, 10 = 10, 11 = Jack, 12 = Queen, 13 = King
    int suit; // 0 = Hearts, 1 = Diamonds, 2 = Clubs, 3 = Spades
    Card(int f, int s) {
        face = f;
        suit = s;
    }
};