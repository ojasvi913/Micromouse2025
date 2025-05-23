#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "data_structures.c"

char path_taken[16 * 16];
int path_index = 0;
char path[256];

 bool wall_data[16][16][4];

bool dup_arr[16][16][4]={

    {{1,1,0,0},{0,1,0,1},{0,1,0,1},{0,1,1,0},{1,1,0,0},{0,1,0,0},{0,1,1,0},{1,1,0,0},{0,1,0,1},{0,1,0,1},{0,1,0,0},{0,1,0,1},{0,1,0,1},{0,1,0,1},{0,1,0,1},{0,1,1,0}},
    {{1,0,0,0},{0,1,1,1},{1,1,0,0},{0,0,1,1},{1,0,1,0},{1,0,1,0},{1,0,1,0},{1,0,0,0},{0,1,0,1},{0,1,1,0},{1,0,1,1},{1,1,1,0},{1,1,0,0},{0,1,0,1},{0,1,1,0},{1,0,1,0}},
    {{1,0,0,1},{0,1,1,0},{1,0,0,1},{0,1,1,0},{1,0,1,0},{1,0,0,0},{0,0,1,0},{1,0,1,1},{1,1,0,0},{0,0,1,1},{1,1,0,0},{0,0,0,1},{0,0,1,1},{1,1,0,0},{0,0,0,1},{0,0,1,0}},
    {{1,1,0,0},{0,0,1,1},{1,1,0,1},{0,0,1,0},{1,0,1,0},{1,0,1,0},{1,0,1,0},{1,1,0,0},{0,0,1,1},{1,1,0,0},{0,0,1,1},{1,1,0,0},{0,1,0,1},{0,0,1,1},{1,1,0,0},{0,0,1,1}},
    {{1,0,1,0},{1,1,0,0},{0,1,0,1},{0,0,1,1},{1,0,1,0},{1,0,1,0},{1,0,0,0},{0,0,1,1},{1,1,0,0},{0,0,1,1},{1,1,1,0},{1,0,1,0},{1,1,0,0},{0,1,0,1},{0,0,1,1},{1,1,1,0}},
    {{1,0,1,0},{1,0,0,1},{0,1,0,1},{0,1,1,0},{1,0,1,0},{1,0,0,1},{0,0,1,0},{1,1,1,0},{1,0,0,0},{0,1,0,1},{0,0,1,0},{1,0,1,0},{1,0,1,0},{1,1,1,0},{1,1,1,0},{1,0,1,0}},
    {{1,0,1,0},{1,1,0,0},{0,1,1,1},{1,0,1,0},{1,0,0,0},{0,1,1,0},{1,0,1,1},{1,0,0,1},{0,0,1,1},{1,1,1,0},{1,0,1,0},{1,0,0,1},{0,0,0,0},{0,0,0,1},{0,0,0,1},{0,0,1,1}},
    {{1,0,0,0},{0,0,1,0},{1,1,0,0},{0,0,1,1},{1,0,1,0},{1,0,0,1},{0,1,1,0},{1,1,0,0},{0,1,0,0},{0,0,0,1},{0,0,0,1},{0,1,1,1},{1,0,0,1},{0,1,0,0},{0,1,0,1},{0,1,1,0}},
    {{1,0,1,1},{1,0,1,0},{1,0,0,1},{0,1,1,0},{1,0,0,0},{0,1,0,1},{0,0,1,1},{1,0,0,1},{0,0,1,1},{1,1,1,0},{1,1,0,0},{0,1,0,1},{0,1,1,0},{1,0,0,1},{0,1,0,0},{0,0,1,1}},
    {{1,1,0,0},{0,0,0,1},{0,1,1,1},{1,0,0,1},{0,0,1,1},{1,1,0,0},{0,1,1,1},{1,1,0,0},{0,1,0,0},{0,0,0,1},{0,0,1,0},{1,1,1,0},{1,0,0,1},{0,1,1,0},{1,0,0,1},{0,1,1,0}},
    {{1,0,0,0},{0,1,0,1},{0,1,0,1},{0,1,0,0},{0,1,0,1},{0,0,0,0},{0,1,1,1},{1,0,1,1},{1,0,0,1},{0,1,1,0},{1,0,1,0},{1,0,0,0},{0,1,1,1},{1,0,0,1},{0,1,0,1},{0,0,1,0}},
    {{1,0,1,0},{1,1,0,0},{0,1,1,0},{1,0,0,1},{0,1,1,0},{1,0,0,1},{0,1,1,0},{1,1,0,0},{0,1,1,0},{1,0,0,0},{0,1,1,0},{1,0,0,1},{0,1,0,1},{0,1,0,1},{0,1,0,1},{0,0,1,1}},
    {{1,0,0,0},{0,0,1,1},{1,0,0,1},{0,1,1,0},{1,0,0,1},{0,1,1,0},{1,0,1,0},{1,0,1,0},{1,0,1,0},{1,0,1,1},{1,0,0,1},{0,1,0,1},{0,1,0,1},{0,1,0,1},{0,1,1,1},{0,1,1,0}},
    {{1,0,1,0},{1,1,0,0},{0,1,1,0},{1,0,0,1},{0,1,1,0},{1,0,0,1},{0,0,1,0},{1,0,1,0},{1,0,1,0},{1,1,0,1},{0,1,0,0},{0,1,0,1},{0,1,0,1},{0,1,0,1},{0,1,0,1},{0,0,1,1}},
    {{1,0,1,0},{1,0,1,0},{1,0,0,1},{0,1,1,0},{1,0,0,1},{0,1,1,0},{1,0,1,0},{1,0,1,0},{1,0,1,0},{1,1,0,1},{0,0,0,1},{0,1,0,1},{0,1,0,1},{0,1,0,1},{0,1,0,1},{0,1,1,0}},
    {{1,0,1,1},{1,0,0,1},{0,1,0,1},{0,0,0,1},{0,1,0,1},{0,0,0,1},{0,0,0,1},{0,0,1,1},{1,0,0,1},{0,1,0,1},{0,1,0,1},{0,1,0,1},{0,1,0,1},{0,1,0,1},{0,1,0,1},{0,0,1,1}},
 };

 void print_maze(int bot_x, int bot_y) {
    for(int y = 3; y >= 0; y--) {
        // Print top walls
        for(int x = 0; x < 4; x++) {
            printf("+");
            if(wall_data[x][y][0]) // NORTH
                printf("---");
            else
                printf("   ");
        }
        printf("+\n");

        // Print side walls and bot
        for(int x = 0; x < 4; x++) {
            if(wall_data[x][y][3]) // WEST
                printf("|");
            else
                printf(" ");

            if(x == bot_x && y == bot_y)
                printf(" B ");
            else
                printf("   ");
        }

        if(wall_data[3][y][1]) // EAST wall of last cell
            printf("|");
        else
            printf(" ");

        printf("\n");
    }

    // Print bottom walls
    for(int x = 0; x < 4; x++) {
        printf("+");
        if(wall_data[x][0][2]) // SOUTH
            printf("---");
        else
            printf("   ");
    }
    printf("+\n");
}


void print_path_taken() {
    printf("\nPath taken by bot: ");
    for (int i = 0; i < path_index; i++) {
        printf("%c ", path_taken[i]);
    }
    printf("\n");
}

void swap(int *x, int *y){
    //Swaps values of two  numbers x and y.
    //Function is complete
    int temp = *x;
    *x = *y;
    *y = temp;
}

int* minimum_cost(short int arena_map[16][16], short int bot_pos[2], int *sortedArray){
    /*
        returns array with [0,1,2,3] as [l,s,r,b] in ascending order of their weights
        Function verified
    */

   //Getting values of neighbors
   int top, left, bottom, right;

   //if condition is to check for array out of bound condition
    if (bot_pos[0] == 0){ //if bot is at top row
        top = 1000;
    }
    else{
        top = arena_map[bot_pos[0] - 1][bot_pos[1]];
    }

    if (bot_pos[0] == 15){ //if bot is at bottom row
        bottom = 1000;
    }
    else{
        bottom = arena_map[bot_pos[0] + 1][bot_pos[1]];
    }

    if (bot_pos[1] == 0){ //if bot is at leftmost column
        left = 1000;
    }
    else{
        left = arena_map[bot_pos[0]][bot_pos[1] - 1];
    }

    if (bot_pos[1] == 15){ //if bot is at rightmost column
        right = 1000;
    }
    else{
        right = arena_map[bot_pos[0]][bot_pos[1] + 1];
    }

    int *return_value = (int *)calloc (4, sizeof(int)); //array to be returned
    int temp_arr[4] = {left, top, right, bottom}; //array to be sorted
    int smallest =0;

    for (int i = 0; i<4; i++){
        return_value[i] =i; //initializing return array to [0,1,2,3]
    }

    //Sorting array (selection sort)
    for (int i  =0 ; i<4; i++){
        smallest = i;
        for (int j = i +1;j<4; j++){
            if (temp_arr[smallest]>temp_arr[j]){
                smallest = j;
            }
        }

        swap(&temp_arr[i], &temp_arr[smallest]);
        swap(&return_value[i], &return_value[smallest]);
    }

    for (int i =0 ; i<4; i++){ //copying sorted array to sortedArray
        sortedArray[i] = temp_arr[i];
    }



    return return_value;
}


int minimum_value_accessible_neighbors(short int arena_map[16][16], short int pos[2], int *smallest_accessible_regardless,bool wall_data[][16][4]){
    /*returns 0 for left, 1 for forward, 2 for right, 3 for back, -1 if no minimum accessible neighbors
    Function verified
    */

    int sortedArray[4];
    int *min_cost = minimum_cost(arena_map, pos, sortedArray);



    for (int i =0; i< 4; i++){


        if (arena_map[pos[0]][pos[1]]>sortedArray[i]){ //Checking if current node is greater than minimum accessible neighbors.
            if (wall_data[pos[0]][pos[1]][min_cost[i]] == 0){ //Checking if node is accessible
                return min_cost[i];
            }
            else{
                continue;
            }
        }

        else{
            if (wall_data[pos[0]][pos[1]][min_cost[i]] == 0){ //Checking if node is accessible
                switch(min_cost[i]){ //assigning smallest_accessible_regardless to the smallest non-accessible neighbor
                    case 0:
                        *smallest_accessible_regardless = arena_map[pos[0]][pos[1] - 1];
                        break;
                    case 1:
                        *smallest_accessible_regardless = arena_map[pos[0] - 1][pos[1]];
                        break;
                    case 2:
                        *smallest_accessible_regardless = arena_map[pos[0]][pos[1] + 1];
                        break;
                    case 3:
                        *smallest_accessible_regardless = arena_map[pos[0] + 1][pos[1]];
                        break;
                    default:
                        break;
                }
                return -1;
            }
        }
    }
}

void rearrange_map(short int arena_map[16][16], short int base_pos[2],bool wall_data[][16][4]){
    //Changes value of map node cost in case the current node has a strictly lower cost than all of its accessible neighbors. Function verified

    queue_push(base_pos[0], base_pos[1]); //pushing base node to queue
    short int *poped;
    int min_access;
    int small;

    while (!queue_empty()){
        poped = queue_pop();
        min_access = minimum_value_accessible_neighbors(arena_map, poped, &small, wall_data); //returns index of minimum value accessible neighbor
        if (poped[0]<0 || poped[0]>15 || poped[1]<0 || poped[1]>15){
            continue;
        }
        if (min_access == -1){ //if all accessible neighbors have higher cost than current node

            arena_map[poped[0]][poped[1]] = small + 1;

            for (int i = 0; i<4; i++){ //pushing accessible neighbors to queue
                if (wall_data[poped[0]][poped[1]][i] == 0){
                    switch (i){
                        case (0):
                            queue_push(poped[0], poped[1] - 1);
                            break;

                        case (1):
                            queue_push(poped[0] - 1, poped[1]);
                            break;

                        case (2):
                            queue_push(poped[0], poped[1] + 1);
                            break;

                        case (3):
                            queue_push(poped[0] + 1, poped[1]);
                            break;

                        default:
                            break;
                    }
                }
            }
        }
    }
}

int direction_wrt_compass(short int arena_map[16][16], short int bot_pos[2], bool wall_data[][16][4]){
    // Checks which direction to move in wrt to a compass. i.e 0=>East, 1=>North, 2=>West, 3=>South. Function unverified

    int *smallest_value;
    int small;
    int min_access;

    do{
        min_access = minimum_value_accessible_neighbors(arena_map, bot_pos, &small, wall_data);

    // Serial.print("Direction: ");
    // Serial.println(min_access);

        switch (min_access){  //lsrb if nodes are equal
            case 0://move east
                path_taken[path_index++] = 'E';
                return 0;
                break;
            case 1: //move north
                path_taken[path_index++] = 'N';
                return 1;
                break;
            case 2: //move west
                path_taken[path_index++] = 'W';
                return 2;
                break;
            case 3: // move south
                path_taken[path_index++] = 'S';
                return 3;
                break;
            case -1:
                rearrange_map(arena_map, bot_pos, wall_data);
        }

    }while (min_access == -1);
}


int direction_wrt_bot(short int arena_map[16][16], short int bot_pos[2], int facing, bool wall_data[][16][4]){
    //Decide which direction the both should move in from its perspective
    int direction1 = direction_wrt_compass(arena_map, bot_pos, wall_data);

    if (facing == direction1){
        //move forward

        return 1;
    }

    else if (((facing+1)%4 == direction1)){
        //turn right

        return 2;
    }

    else if (facing == (direction1+1)%4){
        //turn left

        return 0;
    }

    return 3;
}



int main(){

    short int arena_map[16][16] = {
    {14, 13, 12, 11, 10, 9, 8, 7, 7, 8, 9, 10, 11, 12, 13, 14},
    {13, 12, 11, 10,  9, 8, 7, 6, 6, 7, 8,  9, 10, 11, 12, 13},
    {12, 11, 10,  9,  8, 7, 6, 5, 5, 6, 7,  8,  9, 10, 11, 12},
    {11, 10,  9,  8,  7, 6, 5, 4, 4, 5, 6,  7,  8,  9, 10, 11},
    {10,  9,  8,  7,  6, 5, 4, 3, 3, 4, 5,  6,  7,  8,  9, 10},
    { 9,  8,  7,  6,  5, 4, 3, 2, 2, 3, 4,  5,  6,  7,  8, 9 },
    { 8,  7,  6,  5,  4, 3, 2, 1, 1, 2, 3,  4,  5,  6,  7, 8 },
    { 7,  6,  5,  4,  3, 2, 1, 0, 0, 1, 2,  3,  4,  5,  6, 7 },
    { 7,  6,  5,  4,  3, 2, 1, 0, 0, 1, 2,  3,  4,  5,  6, 7 },
    { 8,  7,  6,  5,  4, 3, 2, 1, 1, 2, 3,  4,  5,  6,  7, 8 },
    { 9,  8,  7,  6,  5, 4, 3, 2, 2, 3, 4,  5,  6,  7,  8, 9 },
    {10,  9,  8,  7,  6, 5, 4, 3, 3, 4, 5,  6,  7,  8,  9, 10},
    {11, 10,  9,  8,  7, 6, 5, 4, 4, 5, 6,  7,  8,  9, 10, 11},
    {12, 11, 10,  9,  8, 7, 6, 5, 5, 6, 7,  8,  9, 10, 11, 12},
    {13, 12, 11, 10,  9, 8, 7, 6, 6, 7, 8,  9, 10, 11, 12, 13},
    {14, 13, 12, 11, 10, 9, 8, 7, 7, 8, 9, 10, 11, 12, 13, 14},
    };
    short int position[2] = {15,0};
    initialize_queue();
    int facing = 1;

    while (true){

        printf("Wall data for current node: \n");
        for (int i =0 ; i<4; i++){
            int temp;
            wall_data[position[0]][position[1]][i] = dup_arr[position[0]][position[1]][i];
            printf("%d ", wall_data[position[0]][position[1]][i]);
        }
        printf("\n");

        if (arena_map[position[0]][position[1]] == 0){
            printf("Reached center!\n");
            print_path_taken();
            return 0;
            break;
        }

        int turn_direction = direction_wrt_bot(arena_map, position, facing, wall_data); //Decide direction to turn to so as to face the correct node
        // printf("Turn direction: %d\n", turn_direction);

        switch (turn_direction)
            {
                case 0:
                    // printf("Turn left\n");
                    facing = facing - 1;
                    if (facing == -1){
                        facing = 3;
                    }
                    break;

                case 1:
                    // printf("Move forward\n");
                    break; //Facing the correct node

                case 2:
                    facing = (facing + 1)%4;
                    // printf("Turn right\n");
                    break;

                case 3:
                    facing = (facing + 2)%4;
                    // printf("Turn back\n");
                    break;

                default:
                    // Serial.println("Not possible");
                    break;
            }

            switch(facing){ //Update current position
                case 0:
                    position[1] -= 1;

                    break;

                case 1:
                    position[0] -= 1;

                    break;

                case 2:
                    position[1] += 1;

                    break;

                case 3:
                    position[0] += 1;


                    break;
            }

            printf("Current position: %d %d\n", position[0], position[1]);
            printf("Current facing: %d\n", facing);

    }

    print_path_taken();

    return 0;
}