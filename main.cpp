#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>
#include "map.h"



using namespace std;

int main(int argc, char* argv[]){
    srand(time(NULL));
    if(argc != 3) {
        cout << "Command Line Arguments must be <x dimension> <y dimension>" << endl;
        return -1;
    }
    const int max_x = atoi(argv[1]);
    const int max_y = atoi(argv[2]);  
    class Map map(max_x, max_y); // Initialize dimensions of map.
    
    vector<Vampire> vampires;
    vector<Werewolf> werewolves;
    init_map_elements(max_x, max_y);
    ifstream my_map; // This will be used to read the map from the txt file.
    my_map.open("map.txt", ios::in); // Open the file
    char game_map[max_x][max_y];
    char c; // This will be used to read the map from the txt file.
        if(my_map.is_open()){
            for(int i = 0; i <= max_x; i++){
               for(int j = 0; j <= max_y; j++){
                    c = my_map.get();
                    game_map[i][j] = c;

                }
            }
                

        }else cout << "Could not open file" << endl;
        
    
    cout << "The Map has been created! Take a look!" << endl;
    for(int i = 0; i< max_x; i++){
        for(int j = 0; j < max_y; j++){
            cout << game_map[i][j]<< " ";
        }
        cout << endl;
    }
    
    // Creating variable player of type class Avatar and calling the constructor using as the arguments the initial random coordinates.
    int avatar_x =  (int)rand() % map.x;
    int avatar_y =  (int)rand() % map.y;
    int pots = 1;
    // Check so as the avatar will spawn in earth and not in a tree and fall or in water and drown
    while(game_map[avatar_x][avatar_y] == '.'){

        avatar_x =  (int)rand() % map.x;
        avatar_y = (int)rand() % map.y; 
    }
    Avatar player(avatar_x, avatar_y, MAX_HEALTH, pots);

    game_map[player.curr_x][player.curr_y] = (char)player.team_chosen;
    
    int potion_x =  (int)rand() % map.x;
    int potion_y = (int)rand() % map.y;
    while(game_map[potion_x][potion_y] != '.'){
        potion_x =  (int)rand() % map.x;
        potion_y = (int)rand() % map.y;
    }
    
    Potion pot(potion_x, potion_y);
    
    game_map[pot.x][pot.y] = (char)pot.potion;
    
        for(int i = 0; i< max_x; i++){
        for(int j = 0; j < max_y; j++){
            cout << game_map[i][j]<< " ";
        }
        cout << endl;
    }

    int dim = map.x * map.y;
    int min_number_of_entities = 0.5 * dim / 15; 
    int max_number_of_entities = dim / 15;
    int number_of_entities = 1 + (int)rand()%(max_number_of_entities - min_number_of_entities) + min_number_of_entities;

    for(int i = 0; i < number_of_entities; i++){
        int medicine = (int)rand() % 3;
        int attack = 1 + (int)rand() % 3; // Number between 1-3
        int defense = 1 + (int)rand() % 2; // Number between 1-2
        int x = 1 + (int)rand() % map.x;
        int y = 1 + (int)rand() % map.y;
        while(game_map[x][y] != '.'){
            x = 1 + (int)rand() % map.x;
            y = 1 + (int)rand() % map.y;
        }
        Werewolf* wolf = new Werewolf(x,y,MAX_HEALTH, attack, defense, medicine);
        werewolves.push_back(*wolf); // Push back the werewolf to the vector of werewolves
        game_map[wolf->curr_x][wolf->curr_y] = (char)wolf->type;
    }

    
    for(int i = 0; i < number_of_entities; i++){
        int medicine = (int)rand()% 3; //Number between 0-2
        int attack = 1 + (int)rand() % 3; // Number between 1-3
        int defense = 1 + (int)rand() % 2; // Number between 1-2
        int  x = 1 + (int)rand() % map.x;
        int  y = 1 + (int)rand() % map.x;
        while(game_map[x][y] != '.'){
            x = 1 + (int)rand() % map.x;
            y = 1 + (int)rand() % map.y;
        }
        Vampire* bloodsucka = new Vampire(x, y, MAX_HEALTH, attack, defense, medicine);
        vampires.push_back(* bloodsucka); // Push back the vampire to the vector of vampires
        game_map[bloodsucka->curr_x][bloodsucka->curr_y] = (char)bloodsucka->type;
    }

        //game starts here
        cout << endl <<  "Make a move !" << endl;
        int control = 1;
        char ch;
        

    // If time is from 12 - 40 its day. From 40 to 12 its night.
    int time = 0;
    while(ch != 'q' || control != 0) {   // While the user does not press q, the game will continue


    if(werewolves.size() == 0 || vampires.size() == 0){
        if(werewolves.size() == 0){
            cout << "The Vampires Won"<< endl;
        }else 
            cout << "The Werewolves Won!" << endl;
        control = 0;
        
    }
    if(time == 48){
        time = 0;
        time++;
    }


        game_map[player.curr_x][player.curr_y] = '.';
        ch = getchar();
        switch (ch) {
            case 'w':
                if ((game_map[player.curr_x - 1][player.curr_y] == '.' && (player.curr_x - 1) >= 0) || game_map[player.curr_x - 1][player.curr_y] == 'P') {
                    
                    if(game_map[player.curr_x - 1][player.curr_y] == 'P'){
                        player.pots++;
                    }
                    player.curr_x--;
                } // key up
                break;

            case 's':
                if ((game_map[player.curr_x + 1][player.curr_y] == '.' && (player.curr_x + 1) < map.x) || game_map[player.curr_x + 1][player.curr_y] == 'P') {
                    if(game_map[player.curr_x + 1][player.curr_y] == 'P')
                        player.pots++;
                    player.curr_x++;
                }   // key down
                break;
            case 'a':
                if ((game_map[player.curr_x][player.curr_y - 1] == '.' && (player.curr_y - 1) >= 0) || game_map[player.curr_x][player.curr_y - 1] == 'P') {
                    
                    if(game_map[player.curr_x][player.curr_y - 1] == 'P')
                        player.pots++;
                    player.curr_y--; // key left
                }
                break;

            case 'd' :
                if ((game_map[player.curr_x][player.curr_y + 1] == '.' && (player.curr_y + 1) < map.y) || game_map[player.curr_x][player.curr_y + 1] == 'P'){
                    if(game_map[player.curr_x][player.curr_y + 1] == 'P')
                        player.pots++;
                    player.curr_y++; // key right

                }
                break;
            case 'h':
                if(player.pots > 0){
                    if (player.team_chosen == 'W' && (time >= 40 && time <= 12)) {
                        // Change the health of all Vampire objects
                        for (int i = 0; i < werewolves.size(); i++) {
                            werewolves[i].curr_health = MAX_HEALTH;
                            
                        }
                        player.pots--;
                    }
                    else{
                        // Change the health of all Werewolf objects
                        for (int i = 0; i < vampires.size(); i++) {
                            vampires[i].curr_health = MAX_HEALTH;
                        }
                        player.pots--;
                    }
                
                }
                break;
            case 'p': 
                cout << "Number of of active vampires : " << vampires.size() << endl;
                cout << "Number of active werewolves : " <<  werewolves.size() << endl;
                cout << "You have " << player.pots << " potions left." << endl;
                break;
            default:
                break;
                
        }
        //move all vampires a next step in the game map randomly
        for (int i = 0; i < vampires.size(); i++) {
            int x = vampires[i].curr_x;
            int y = vampires[i].curr_y;
            game_map[x][y] = '.';
            int move = (int) rand() % 9;
            switch (move) {
                case 0:
                    if (game_map[x - 1][y] == '.' && (x - 1) >= 0) {
                        vampires[i].curr_x--;
                    }
                    break;
                case 1:
                    if (game_map[x + 1][y] == '.' && (x + 1) < map.x) {
                        vampires[i].curr_x++;
                    }
                    break;
                case 2:
                    if (game_map[x][y - 1] == '.' && (y - 1) >= 0) {
                        vampires[i].curr_y--;
                    }
                    break;
                case 3:
                    if (game_map[x][y + 1] == '.' && (y + 1) < map.y) {
                        // vampires[i].curr_y++;
                    }
                    break;
                    //make a diagonal move if the vampire is not on the edge of the map
                case 4:
                    if (game_map[x - 1][y - 1] == '.' && (x - 1) >= 0 && (y - 1) >= 0) {
                        vampires[i].curr_x--;
                        vampires[i].curr_y--;
                    }
                    break;
                case 5:
                    if (game_map[x - 1][y + 1] == '.' && (x - 1) >= 0 && (y + 1) < map.y) {
                        vampires[i].curr_x--;
                        vampires[i].curr_y++;
                    }
                    break;
                case 6:
                    if (game_map[x + 1][y - 1] == '.' && (x + 1) < map.x && (y - 1) >= 0) {
                        vampires[i].curr_x++;
                        vampires[i].curr_y--;
                    }
                    break;
                case 7:
                    if (game_map[x + 1][y + 1] == '.' && (x + 1) < map.x && (y + 1) < map.y) {
                        vampires[i].curr_x++;
                        vampires[i].curr_y++;
                    }
                    break;
                    //case no  move
                case 8:
                    game_map[x][y] = 'V';
                    break;
                default:
                    break;
                    
            }
            game_map[vampires[i].curr_x][vampires[i].curr_y] = (char)vampires[i].type;
        }


        //move all werewolves a next step in the game map randomly

        for (int i = 0; i < werewolves.size(); i++) { 

            int x = werewolves[i].curr_x;
            int y = werewolves[i].curr_y;
            game_map[x][y] = '.';
            int move2 = (int) rand() % 5;
            switch (move2) {
                case 0:
                    if (game_map[x - 1][y] == '.' && (x - 1) >= 0) {
                        werewolves[i].curr_x--;
                    }
                    break;
                case 1:
                    if (game_map[x + 1][y] == '.' && (x + 1) < map.x) {
                        werewolves[i].curr_x++;
                    }
                    break;
                case 2:
                    if (game_map[x][y - 1] == '.' && (y - 1) >= 0) {
                        werewolves[i].curr_y--;
                    }
                    break;
                case 3:
                    if (game_map[x][y + 1] == '.' && (y + 1) < map.y) {
                        werewolves[i].curr_y++;
                    }
                    break;
                    //case no  move 
                case 4:
                    game_map[x][y] = 'w';
                    break;
                default:
                    break;
                    
            }

            game_map[werewolves[i].curr_x][werewolves[i].curr_y] = (char) werewolves[i].type;


        }
        game_map[player.curr_x][player.curr_y] = (char)player.team_chosen;
        
        
        //fight between werewolves and vampires at the adjacent cells and decrease the health of the loser

        int fight = (int) rand() % 2; //randomly choose WHO FIGHTS FIRST
        for (int i = 0; i < vampires.size(); i++) {
            for (int j = 0; j < werewolves.size(); j++) {
                switch (fight) {

                    case 0:

                        if (vampires[i].curr_x == werewolves[j].curr_x &&
                            abs((vampires[i].curr_y - werewolves[j].curr_y)) == 1
                            || vampires[i].curr_y == werewolves[j].curr_y &&
                               abs((vampires[i].curr_x - werewolves[j].curr_x)) == 1) {
                            //if the vampire is stronger than the werewolf it will attack.
                            if (vampires[i].attack >= werewolves[j].attack) {
                                werewolves[j].curr_health =
                                        werewolves[j].curr_health - abs(vampires[i].attack - werewolves[j].defense);
                                 }
                             else { // The vampire will try to move away from the dog
                                int move3 = (int) rand() % 8;
                                int x = vampires[i].curr_x;
                                int y = vampires[i].curr_y;
                                game_map[x][y] = '.';
                                switch (move3) {
                                    case 0:
                                        if (game_map[x - 1][y] == '.' && (x - 1) >= 0) {
                                            vampires[i].curr_x--;
                                        }
                                        break;
                                    case 1:
                                        if (game_map[x + 1][y] == '.' && (x + 1) < map.x) {
                                            vampires[i].curr_x++;
                                        }
                                        break;
                                    case 2:
                                        if (game_map[x][y - 1] == '.' && (y - 1) >= 0) {
                                            vampires[i].curr_y--;
                                        }
                                        break;
                                    case 3:
                                        if (game_map[x][y + 1] == '.' && (y + 1) < map.y) {
                                            // vampires[i].curr_y++;
                                        }
                                        break;
                                        //make a diagonal move if the vampire is not on the edge of the map
                                    case 4:
                                        if (game_map[x - 1][y - 1] == '.' && (x - 1) >= 0 && (y - 1) >= 0) {
                                            vampires[i].curr_x--;
                                            vampires[i].curr_y--;
                                        }
                                        break;
                                    case 5:
                                        if (game_map[x - 1][y + 1] == '.' && (x - 1) >= 0 && (y + 1) < map.y) {
                                            vampires[i].curr_x--;
                                            vampires[i].curr_y++;
                                        }
                                        break;
                                    case 6:
                                        if (game_map[x + 1][y - 1] == '.' && (x + 1) < map.x && (y - 1) >= 0) {
                                            vampires[i].curr_x++;
                                            vampires[i].curr_y--;
                                        }
                                        break;
                                    case 7:
                                        if (game_map[x + 1][y + 1] == '.' && (x + 1) < map.x && (y + 1) < map.y) {
                                            vampires[i].curr_x++;
                                            vampires[i].curr_y++;
                                        }
                                        break;
                                }
                             }
                                game_map[vampires[i].curr_x][vampires[i].curr_y] = (char) vampires[i].type;

                            }
                            break;
                            case 1:
                                if (vampires[i].curr_x == werewolves[j].curr_x && abs((vampires[i].curr_y - werewolves[j].curr_y)) == 1
                                    || vampires[i].curr_y == werewolves[j].curr_y && abs((vampires[i].curr_x - werewolves[j].curr_x)) == 1) {
                                    // If the dog is stronger than the leach he will attack it

                            if (werewolves[j].attack >= vampires[i].attack) {
                                vampires[i].curr_health = vampires[i].curr_health - abs(werewolves[j].attack - vampires[i].defense);
                            }
                             else { // The dog will (try) run away
                                int x = werewolves[j].curr_x;
                                int y = werewolves[j].curr_y;
                                game_map[x][y] = '.';
                                int move = (int) rand() % 4;
                                switch (move) {
                                    case 0:
                                        if (game_map[x - 1][y] == '.' && (x - 1) >= 0) {
                                            werewolves[j].curr_x--;
                                        }
                                        break;
                                    case 1:
                                        if (game_map[x + 1][y] == '.' && (x + 1) < map.x) {
                                            werewolves[j].curr_x++;
                                        }
                                        break;
                                    case 2:
                                        if (game_map[x][y - 1] == '.' && (y - 1) >= 0) {
                                            werewolves[j].curr_y--;
                                        }
                                        break;
                                    case 3:
                                        if (game_map[x][y + 1] == '.' && (y + 1) < map.y) {
                                            werewolves[j].curr_y++;
                                        }
                                        break;
                                } 
                             }
                                game_map[werewolves[j].curr_x][werewolves[j].curr_y] = (char) werewolves[i].type;


                            }
                            break;
                        }
                }
            }

            for(int i = 0; i < vampires.size(); i++){
                 int will_you_medicine_me = (int) rand() % 2;
                if (vampires[i].curr_x == vampires[i + 1].curr_x && abs((vampires[i].curr_y - vampires[i+1].curr_y)) == 1
                || vampires[i].curr_y == vampires[i+1].curr_y && abs((vampires[i].curr_x - vampires[i+1].curr_x)) == 1){
                    }
                    if(will_you_medicine_me == 1 && vampires[i].medicine > 0 && vampires[i + 1].curr_health < MAX_HEALTH){
                        vampires[i + 1].curr_health++;
                        vampires[i].medicine--;
                    }

            }

            for(int i = 0; i < werewolves.size(); i++){
                 int will_you_medicine_me = (int) rand() % 2;
                if (werewolves[i].curr_x == werewolves[i + 1].curr_x && abs((werewolves[i].curr_y - werewolves[i+1].curr_y)) == 1
                || werewolves[i].curr_y == werewolves[i+1].curr_y && abs((werewolves[i].curr_x - werewolves[i+1].curr_x)) == 1){
                    }
                    if(will_you_medicine_me == 1 && werewolves[i].medicine > 0 && werewolves[i+1].curr_health < MAX_HEALTH){
                        werewolves[i + 1].curr_health++;
                        werewolves[i].medicine--;
                    }

            }

            // if the health of the vampire or werewolf is less than or equal to 0, delete it from the vector and from the map
            for (int i = 0; i < vampires.size(); i++) {
                if (vampires[i].curr_health <= 0) {

                    game_map[vampires[i].curr_x][vampires[i].curr_y] = '.';
                    vampires.erase(vampires.begin() + i);
                    //put on map '.'
                    
                }
            }
            for (int j = 0; j < werewolves.size(); j++) {
                if (werewolves[j].curr_health <= 0) {
                    game_map[werewolves[j].curr_x][werewolves[j].curr_y] = '.';
                    werewolves.erase(werewolves.begin() + j);
                    //put on map '.'

                }
            }


            cout << endl;
            for (int i = 0; i < max_x; i++) {
                for (int j = 0; j < max_y; j++) {
                    cout << game_map[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;
    

            cout << endl << "Make a move !" << endl;

        }

        return 0;
    
}




