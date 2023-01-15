#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "grid.h"
#include "player.h"

void init_level(const char* file_path, struct Grid *lGrid){
	// ouverture du fichier en mode lecture
	FILE* file = fopen(file_path, "r");
	if(!file){
		fprintf(stderr, "Error %s not found", file_path);
		exit(-1);
	}
	char line[100] = {0};
	int number_column = 0; // nombre de colonne
	int number_row = 0; /// nombre de ligne
	int number_goals = 0;
	// on lit la première ligne du fichier
	fgets(line, 100, file);
	sscanf(line, "%d %d %d", &number_column, &number_row, &number_goals);
	int current_row = 0;
	//int current_goal = 0;
	// On lit le fichier ligne par ligne jusqu'à la fin du fichier
	lGrid -> column_number = number_column;
	lGrid -> row_number= number_row;
	lGrid -> goals_nmr = number_goals;
	lGrid -> goals_nmr_d = 0;
	//remplisage de tableau game_grid
	
	lGrid -> game_grid = malloc(lGrid->row_number * sizeof(enum CaseType*));
	for(int index_allouer = 0; index_allouer < lGrid->row_number; index_allouer++)
    {
        lGrid -> game_grid[index_allouer] = malloc(lGrid->column_number * sizeof(enum CaseType));
    }
    
	while(fgets(line, 100, file) != NULL){
		char* buf = line;
		int current_column = 0;
		while(*buf && *buf != '\n'){
			lGrid -> game_grid[current_row][current_column] = *buf;
			if(*buf == '@'){
				lGrid -> position.x = current_column;
				lGrid -> position.y = current_row;
			}
			current_column += 1;
			buf += 1;
		}		
		current_row += 1;
	}
	fclose(file); // close file
}
void display(struct Grid *lGrid){
    int line_returned=1;
	printf("Done: %d/%d",lGrid->goals_nmr_d,lGrid->goals_nmr);
	printf("\n\r");
	for(int i = 0; i < lGrid -> row_number; i++){
		for(int j = 0; j < lGrid -> column_number; j++)
		{	
			printf("%c",lGrid -> game_grid[i][j]);
			if(line_returned == lGrid -> column_number) printf("\n\r");
			line_returned++;
		}
		line_returned = 1;
	}
	
}

void freegrid(struct Grid *lGrid){
    for(int i = 0; i < lGrid->row_number; i++){
        free(lGrid->game_grid[i]);
    }
    free(lGrid->game_grid);
}

void move_player(struct Grid *lGrid, struct Grid *mGrid,enum Direction mp, struct Player new_position){
    
	if(mp){
        switch(mp)
        {
            case Top :
            {
                new_position.x = lGrid->position.x;
                new_position.y = lGrid->position.y - 1;
            } break;
            case Left :
            {
                new_position.x = lGrid->position.x - 1;
                new_position.y = lGrid->position.y;
            } break;
            case Right :
            {
                new_position.x = lGrid->position.x + 1;
                new_position.y = lGrid->position.y;
            } break;
            case Bottom :
            {
                new_position.x = lGrid->position.x;
                new_position.y = lGrid->position.y + 1;
            } break;
            default: {
				new_position.x = lGrid->position.x;
                new_position.y = lGrid->position.y;
			} break;
        }        
    }
	bool isMove = false;
	enum CaseType *currentGrid = &lGrid -> game_grid[lGrid->position.y][lGrid->position.x];
    enum CaseType *nextMoveGrid = &lGrid->game_grid[new_position.y][new_position.x];
    if (*nextMoveGrid == BOX || *nextMoveGrid == BOX_LOADED){
		struct Player new_box_position = new_position;
		switch(mp){
            case Top :
            {
                new_box_position.x = new_position.x;
                new_box_position.y = new_position.y - 1;
            } break;
            case Left :
            {
                new_box_position.x = new_position.x - 1;
                new_box_position.y = new_position.y;
            } break;
            case Right :
            {
                new_box_position.x = new_position.x + 1;
                new_box_position.y = new_position.y;
            } break;
            case Bottom :
            {
                new_box_position.x = new_position.x;
                new_box_position.y = new_position.y + 1;
            } break;

            default: break;
        } 

		enum CaseType *nextBoxMoveGrid = &lGrid->game_grid[new_box_position.y][new_box_position.x];

		if(*nextBoxMoveGrid == NONE){ 
			*nextBoxMoveGrid = (mGrid->game_grid[new_box_position.y][new_box_position.x] == GOAL ? BOX_LOADED : BOX); 
			*nextMoveGrid = (mGrid->game_grid[new_position.y][new_position.x] != BOX ? mGrid->game_grid[new_position.y][new_position.x] : NONE);
			if (*nextBoxMoveGrid == BOX && mGrid->game_grid[new_position.y][new_position.x] == GOAL)  lGrid->goals_nmr_d--;
		}
		else if (*nextBoxMoveGrid == GOAL){
            *nextBoxMoveGrid = BOX_LOADED; 
			*nextMoveGrid = (mGrid->game_grid[new_position.y][new_position.x] != BOX ? mGrid->game_grid[new_position.y][new_position.x] : NONE);
			lGrid->goals_nmr_d++;
		}
	}

	if(*nextMoveGrid == NONE){ 
		*nextMoveGrid = PLAYER; 
		isMove = true;
	}
	else if(*nextMoveGrid == GOAL){ 
		*nextMoveGrid = PLAYER; 
		isMove = true;
	}

	if (isMove){
		if (mGrid -> game_grid[lGrid->position.y][lGrid->position.x] == GOAL)
		  *currentGrid = GOAL;
		else *currentGrid = NONE;
		lGrid -> position = new_position;
    }
}