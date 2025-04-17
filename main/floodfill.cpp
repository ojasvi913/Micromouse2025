#include <floodfill.h>
#include "data_structures.h"

char path_taken[6 * 6];
int path_index = 0;
char path[256];
Queue queue;
bool wall_data[6][6][4];

bool dup_arr[6][6][4] ={
 {{1,1,1,0},{1,1,0,0},{0,1,0,1},{0,1,1,0},{1,1,1,0},{1,1,1,0}},
 {{1,0,0,1},{0,0,1,0},{1,1,0,1},{0,0,0,1},{0,0,1,0},{1,0,1,0}},
 {{1,1,1,0},{1,0,1,0},{1,1,0,0},{0,1,0,0},{0,0,1,0},{1,0,1,0}},
 {{1,0,0,0},{0,0,1,1},{1,0,0,1},{0,0,1,1},{1,0,0,0},{0,0,1,1}},
 {{1,0,0,0},{0,1,1,0},{1,1,0,0},{0,1,0,1},{0,0,0,1},{0,1,1,1}},
 {{1,0,1,1},{1,0,0,1},{0,0,0,1},{0,1,0,1},{0,1,0,1},{0,1,1,1}}
 };

void print_maze(int bot_x, int bot_y) {
    for (int y = 3; y >= 0; y--) {
        // Print top walls
        for (int x = 0; x < 4; x++) {
            Serial.print("+");
            if (wall_data[x][y][0]) // NORTH
                Serial.print("---");
            else
                Serial.print("   ");
        }
        Serial.println("+");

        // Print side walls and bot
        for (int x = 0; x < 4; x++) {
            if (wall_data[x][y][3]) // WEST
                Serial.print("|");
            else
                Serial.print(" ");

            if (x == bot_x && y == bot_y)
                Serial.print(" B ");
            else
                Serial.print("   ");
        }

        if (wall_data[3][y][1]) // EAST wall of last cell
            Serial.print("|");
        else
            Serial.print(" ");

        Serial.println();
    }

    // Print bottom walls
    for (int x = 0; x < 4; x++) {
        Serial.print("+");
        if (wall_data[x][0][2]) // SOUTH
            Serial.print("---");
        else
            Serial.print("   ");
    }
    Serial.println("+");
}

void print_path_taken() {
    Serial.print("\nPath taken by bot: ");
    for (int i = 0; i < path_index; i++) {
        Serial.print(path_taken[i]);
        Serial.print(" ");
    }
    Serial.println();
}

void swap(int* x, int* y) {
    // Swaps values of two numbers x and y.
    int temp = *x;
    *x = *y;
    *y = temp;
}

int* minimum_cost(short arena_map[6][6], short bot_pos[2], int *sortedArray) {
    /*
        returns array with [0,1,2,3] as [l,s,r,b] in ascending order of their weights
        Function verified
    */

    // Getting values of neighbors
    int top, left, bottom, right;

    // If condition is to check for array out of bound condition
    if (bot_pos[0] == 0) { // if bot is at top row
        top = 1000;
    } else {
        top = arena_map[bot_pos[0] - 1][bot_pos[1]];
    }

    if (bot_pos[0] == 15) { // if bot is at bottom row
        bottom = 1000;
    } else {
        bottom = arena_map[bot_pos[0] + 1][bot_pos[1]];
    }

    if (bot_pos[1] == 0) { // if bot is at leftmost column
        left = 1000;
    } else {
        left = arena_map[bot_pos[0]][bot_pos[1] - 1];
    }

    if (bot_pos[1] == 15) { // if bot is at rightmost column
        right = 1000;
    } else {
        right = arena_map[bot_pos[0]][bot_pos[1] + 1];
    }

    int* return_value = new int[4]; // array to be returned
    int temp_arr[4] = {left, top, right, bottom}; // array to be sorted
    int smallest = 0;

    for (int i = 0; i < 4; i++) {
        return_value[i] = i; // initializing return array to [0,1,2,3]
    }

    // Sorting array (selection sort)
    for (int i = 0; i < 4; i++) {
        smallest = i;
        for (int j = i + 1; j < 4; j++) {
            if (temp_arr[smallest] > temp_arr[j]) {
                smallest = j;
            }
        }

        // Swap values
        int temp = temp_arr[i];
        temp_arr[i] = temp_arr[smallest];
        temp_arr[smallest] = temp;

        temp = return_value[i];
        return_value[i] = return_value[smallest];
        return_value[smallest] = temp;
    }

    // Copying sorted array to sortedArray
    for (int i = 0; i < 4; i++) {
        sortedArray[i] = temp_arr[i];
    }

    return return_value;
}
int minimum_value_accessible_neighbors(short arena_map[6][6], short pos[2], int *smallest_accessible_regardless, bool wall_data[6][6][4]) {
    /*returns 0 for left, 1 for forward, 2 for right, 3 for back, -1 if no minimum accessible neighbors
    Function verified
    */

    int sortedArray[4];
    int *min_cost = minimum_cost(arena_map, pos, sortedArray);

    for (int i = 0; i < 4; i++) {

        if (arena_map[pos[0]][pos[1]] > sortedArray[i]) { //Checking if current node is greater than minimum accessible neighbors.
            if (wall_data[pos[0]][pos[1]][min_cost[i]] == 0) { //Checking if node is accessible
                return min_cost[i];
            } else {
                continue;
            }
        } else {
            if (wall_data[pos[0]][pos[1]][min_cost[i]] == 0) { //Checking if node is accessible
                switch (min_cost[i]) { //assigning smallest_accessible_regardless to the smallest non-accessible neighbor
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

void rearrange_map(short arena_map[6][6], short base_pos[2], bool wall_data[6][6][4]) {
    // Changes value of map node cost in case the current node has a strictly lower cost than all of its accessible neighbors.
    // Function verified
    queue.push(base_pos[0], base_pos[1]);  // using Queue method
    short* poped;
    int min_access;
    int small;

    while (!queue.empty()) {  // using Queue method
        poped = queue.pop();  // using Queue method
        min_access = minimum_value_accessible_neighbors(arena_map, poped, &small, wall_data);  // returns index of minimum value accessible neighbor

        if (poped[0] < 0 || poped[0] > 15 || poped[1] < 0 || poped[1] > 15) {
            continue;
        }

        if (min_access == -1) {  // if all accessible neighbors have higher cost than current node
            arena_map[poped[0]][poped[1]] = small + 1;

            for (int i = 0; i < 4; i++) {  // pushing accessible neighbors to queue
                if (wall_data[poped[0]][poped[1]][i] == 0) {
                    switch (i) {
                        case 0: queue.push(poped[0], poped[1] - 1); break;  // west
                        case 1: queue.push(poped[0] - 1, poped[1]); break;  // north
                        case 2: queue.push(poped[0], poped[1] + 1); break;  // east
                        case 3: queue.push(poped[0] + 1, poped[1]); break;  // south
                        default: break;
                    }
                }
            }
        }
    }
}

int direction_wrt_compass(short arena_map[6][6], short bot_pos[2], bool wall_data[6][6][4]) {
    // Checks which direction to move in with respect to a compass. i.e 0 => East, 1 => North, 2 => West, 3 => South. Function unverified

    int smallest_value;
    int small;
    int min_access;

    do {
        min_access = minimum_value_accessible_neighbors(arena_map, bot_pos, &small, wall_data);

        switch (min_access) {  // LSRB if nodes are equal
            case 0:
                path_taken[path_index++] = 'E';
                return 0;
            case 1:
                path_taken[path_index++] = 'N';
                return 1;
            case 2:
                path_taken[path_index++] = 'W';
                return 2;
            case 3:
                path_taken[path_index++] = 'S';
                return 3;
            case -1:
                rearrange_map(arena_map, bot_pos, wall_data);
                break;
        }

    } while (min_access == -1);

    return -1;  // to avoid fall-through if invalid min_access
}

int direction_wrt_bot(short arena_map[6][6], short bot_pos[2], int facing, bool wall_data[6][6][4]) {
    // Decide which direction the bot should move from its perspective
    int direction1 = direction_wrt_compass(arena_map, bot_pos, wall_data);

    if (facing == direction1) {
        // moveForward(25);
        return 1;
        Serial.print("Forward");
    } else if (((facing + 1) % 4 == direction1)) {
        Serial.print("Right");
        // TurnRight();
        return 2;

    } else if (facing == (direction1 + 1) % 4) {
        // TurnLeft();
        Serial.print("Left");
        return 0;
    }
Serial.print("Back");
    return 3;  // turn back if no other condition matches
}

#include "data_structures.h"  // Make sure to include your custom structures

int floodfill() {
    short arena_map[6][6] = {

        { 4, 3, 2, 2, 3, 4 },
        { 3, 2, 1, 1, 2, 3 },
        { 2, 1, 0, 0, 1, 2 },
        { 2, 1, 0, 0, 1, 2 },
        { 3, 2, 1, 1, 2, 3 },
        { 4, 3, 2, 2, 3, 4 },

    };

    short position[2] = {15, 0};
    int facing = 1;

    while (true) {
        printf("Wall data for current node: \n");
        for (int i = 0; i < 4; i++) {
            int temp;
            wall_data[position[0]][position[1]][i] = dup_arr[position[0]][position[1]][i];
            printf("%d ", wall_data[position[0]][position[1]][i]);
        }
        printf("\n");

        if (arena_map[position[0]][position[1]] == 0) {
            printf("Reached center!\n");
            print_path_taken();
            return 0;
        }

        int turn_direction = direction_wrt_bot(arena_map, position, facing, wall_data);

        switch (turn_direction) {
            case 0:
                facing = facing - 1;
                if (facing == -1) facing = 3;
                break;
            case 1:
                break;
            case 2:
                facing = (facing + 1) % 4;
                break;
            case 3:
                facing = (facing + 2) % 4;
                break;
        }

        // Save previous position before updating
        short prev_x = position[0];
        short prev_y = position[1];

        switch (facing) {
            case 0: position[1] -= 1; break;
            case 1: position[0] -= 1; break;
            case 2: position[1] += 1; break;
            case 3: position[0] += 1; break;
        }

        // Push previous position to queue for path tracking
        queue.push(prev_x, prev_y);

        printf("Current position: %d %d\n", position[0], position[1]);
        printf("Current facing: %d\n", facing);
    }

    print_path_taken();
    return 0;
}
