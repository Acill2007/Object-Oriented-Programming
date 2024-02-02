#include <cstdlib> // needed for the rand() function.
#include <time.h>
#include <iostream>
#include "classes.h"

using namespace std;

class Map{
    //Size of the 2-d map. Will get their values as an argument of main.
    public: 
    int x;
    int y;
    Map(){}
    Map(int x_max, int y_max){
        x = x_max;
        y = y_max;
    }


}map;

// This function initializes the map. The map will consist of 3 elements, earth, water and trees. Each element will be generated in a random coordinate.
void init_map_elements(int max_x,int max_y){
    int dim = max_x * max_y;
    int min_number_of_earth = 0.7 * dim;

     /* We will use a double array in which each pair of indexes will represent a pair of coordinates.
    The array will be type of int, and we will initialize it to 0, which 0 means the current index is empty,
    1 will mean that earth is there, 2 water and lastly 3  a tree.
    */
    char Elements[max_x][max_y];

    for(int i = 0; i < max_x; i ++){
        for(int j=0; j < max_y; j++){
        Elements[i][j] = 'E';
        }
    }
    srand((int)time(NULL));
    int num_of_earth_elements = (int)rand()%(dim - min_number_of_earth) + min_number_of_earth; // generating a random amount of earth elements between 0.7 * dimensions to dimensions.
    int num_of_water_elements = ((int)rand() % (dim - num_of_earth_elements));
    int num_of_tree_elements = dim - num_of_earth_elements - num_of_water_elements;

    cout << "There will be " << num_of_earth_elements << " earth elements," << num_of_water_elements << " water " << num_of_tree_elements << " tree." << endl;
    
    int i = 0;
    int j = 0;
    int k = 0;
    //Now we need to generate random coordinates for every element. We need to check the array for the terain of the random coordinate
    while(i < num_of_earth_elements){ 

       int x = ((int) rand() % max_x);
       int y = ((int) rand() % max_y);

       if(Elements[x][y] != 'E'){
            int x = ((int) rand() % max_x);
            int y = ((int) rand() % max_y);

       }else{
        Elements[x][y] = '.'; // earth
        i++;
       }
        
    }

    while(j < num_of_water_elements){ 

       int x = ((int) rand() % max_x);
       int y = ((int) rand() % max_y);

       if(Elements[x][y] != 'E'){
            int x = ((int) rand() % max_x);
            int y = ((int) rand() % max_y);

       }else{
        Elements[x][y] = '@'; // water
        j++;
       }
        
    }

    while(k < num_of_tree_elements){ 

       int x = ((int) rand() % max_x);
       int y = ((int) rand() % max_y);

       if(Elements[x][y] != 'E'){
            int x = ((int) rand() % max_x);
            int y = ((int) rand() % max_y);

       }else{
        Elements[x][y] = '#'; // tree
        k++;
       }
        
    }
    // Now we need to write the map to a txt file
    fstream map;
    map.open("map.txt", ios::out);
    for(int i = 0; i < max_x; i++){
        for(int j = 0; j < max_y; j++){
            map << Elements[i][j];
        }
        map << endl;
    }



}