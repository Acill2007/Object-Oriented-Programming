#include <cstdlib> // needed for the rand() function.
#include <time.h>
#include <iostream>
#define MAX_HEALTH 10

using namespace std;


//class being is the predeccesor of classes vampire, werewolf and avatar.
class Being{

    public:
    //Coordinates of the being.
    int curr_x;
    int curr_y;
    int curr_health;
}being;

class Avatar: public Being{

        public:
        char team_chosen;
        int health;
        int pots;
        Avatar(){}
        Avatar(int x, int y, int health, int num_of_pots){

            curr_x = x;
            curr_y = y;
            pots = num_of_pots;
            curr_health = health;
            cout << "Your avatar has been created and placed in a random spot on the map! Now choose your side! W for werewolves and V for Vampires! (UPPERCASE LETTERS ONLY!!)" << endl;
            cout << "Avatar is now in the position (" << curr_x << "," << curr_y << ")" << " with health = " << curr_health  << endl;
            cin >> team_chosen;

        }




}avatar;

class Werewolf: public Being {
    public:
    char type;
    int health;
    int defense;
    int attack;
    int medicine;
    Werewolf(){}
    Werewolf(int x, int y, int health, int att, int def, int num_of_medicine){
        type = 'w';
        curr_x = x;
        curr_y = y;
        curr_health = health;
        attack = att;
        defense = def;
        medicine = num_of_medicine;
        cout << "A Werewolf has been spawned in the position (" << curr_x << "," << curr_y <<")" << " with health = " << curr_health  << endl;

    }
};

class Vampire: public Being {
    public: 
    char type;
    int health;
    int defense;
    int attack;
    int medicine;
    Vampire(){}
    Vampire(int x, int y, int health, int att, int def, int num_of_medicine){
        type = 'v';
        curr_x = x;
        curr_y = y;
        curr_health = health;
        attack = att;
        defense = def;
        medicine = num_of_medicine;
        cout <<"A Vampire has been spawned in the position (" << curr_x << "," << curr_y <<")" << " with health = " << curr_health  << endl;
    }
};


class Potion{

    public:
    int x;
    int y;
    char potion;

    Potion(){}
    Potion(int x_potion, int y_potion){
        x = x_potion;
        y = y_potion;
        potion = 'P';

    }

}potion;