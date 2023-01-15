
#include <SDL2/SDL.h>
#include "sdl2.h"

#include <stdio.h>
#include <ncurses.h>
#include <stdbool.h>
#include <string.h>

#include <unistd.h>

#include "grid.h"
#include "player.h"

/** \file SOKOBAN */
/**
 * @author Hasanli Ayhan
 * @version 2
 * @date 01/04/2022
*/

/**
 * \brief Main function manages the execution of the sokoban game
 * 
 * \fn main(int argc , char *argv[])
 * \post Main function manages the execution of sokaban game, 
 * first it will allocate the \struct Grid where the game board will be saved, 
 * after it will fill this \struct with a txt file which contains the game level,
 * the function also contains two while loops one for game move execution: 
 * with the getchar function, the user is prompted to enter a direction
 * (using the 'h','j','k','l' keys) to move the character in an allowed direction 
 * inside the game board and then display on the console the board with 
 * the new position of the character. we added the letter 'q' to exit the game loop, 
 * also we keep the while loop of the subject that asks 
 * for the letter 'q' as input to complete the execution of the program. 
 * 
 * \return int
*/
int main(int argc , char *argv[]){
	struct Grid lGrid,mGrid; /** declaration lGrid, mGrid \memberof \struct Grid for saving saving game board*/
	struct Player position;
	init_level("level1.txt", &lGrid); //read .txt file with play level and board allocation
	init_level("level1.txt", &mGrid);
	display(&lGrid);
	
	initscr(); //init window
	noecho();
    
    Event (*handle_event)(void);
	void (*handle_display)(struct Grid * grid);

	int graph = 1,cons = 1;
	if(argc>1){
		cons = strcmp(argv[1],"--console");
		graph = strcmp(argv[1],"--sdl2");
	}	

	if( argc==1 || cons==0 ){
		handle_event=event;
		handle_display=display;
	}

	if(graph==0){
		handle_event= event_sdl2;
		handle_display= display_sdl2;
		sdl_init();
	}

	clear();
	refresh();
	handle_display(&lGrid);
    
	
	bool run = true; 
	while(run){ //loop for starting the game
		if(lGrid.goals_nmr != lGrid.goals_nmr_d){
			Event action = handle_event();
			if (action!=None){
				switch (action){
					case Quit: {
						run = false;
						break;
					}
					case U: {
						move_player(&lGrid,&mGrid, 104, position);
						break;
					}
					case D: {
						move_player(&lGrid,&mGrid, 106, position);
						break;
					}
					case L: {
						move_player(&lGrid,&mGrid, 108, position);
						break;
					}
					case R: {
						move_player(&lGrid,&mGrid, 107, position);
						break;
					}
					default:{
					break;
					}
				}
			}
			clear();
			refresh();
			handle_display(&lGrid);
		}
		else
			run = false;				
	}
	endwin();
	sdl_quit();

	if(lGrid.goals_nmr == lGrid.goals_nmr_d) printf("\nVICTORY\n");
	else printf("\nDEFEAT\n");
	
	freegrid(&lGrid);			

	return 0;
}