#ifndef FLOODFILL_H
#define FLOODFILL_H

#include "config.h"
#include "movement.h"
#include "data_structures.h" // Include the header with the Queue class

// Global Variables (Declared as extern in the header, defined in the .c file)
extern char path_taken[16 * 16];
extern int path_index;
extern char path[256];
extern bool wall_data[16][16][4];
extern bool dup_arr[16][16][4];

// Function Prototypes
void print_maze(int bot_x, int bot_y);
void print_path_taken();
void swap(int* x, int* y);
int* minimum_cost(short int arena_map[16][16], short int bot_pos[2], int* sortedArray);
int minimum_value_accessible_neighbors(short int arena_map[16][16], short int pos[2], int* smallest_accessible_regardless, bool wall_data[][16][4]);
void rearrange_map(short int arena_map[16][16], short int base_pos[2], bool wall_data[][16][4]);
int direction_wrt_compass(short int arena_map[16][16], short int bot_pos[2], bool wall_data[][16][4]);
int direction_wrt_bot(short int arena_map[16][16], short int bot_pos[2], int facing, bool wall_data[][16][4]);
int floodfill();

#endif /* FLOODFILL_H_ */