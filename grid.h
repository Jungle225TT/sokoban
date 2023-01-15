#ifndef GRID_HEADER
#define GRID_HEADER

#include "player.h"

/**
 * @enum CaseType grid.h
 * \param WALL '#'
 * \param BOX '$'
 * \param PLAYER '@'
 * \param GOAL '.'
 * \param NONE ' '
 * \param BOX_LOADED '*'
 * 
 * @brief this enum contains information concerning creation map of the game
*/
enum CaseType{
	WALL = '#',
	BOX = '$',
	PLAYER = '@',
	GOAL = '.',
	NONE = ' ',
	BOX_LOADED = '*' //Box is the drop zone
};
/**
 * @struct Grid grid.h
 * \param[in] CaseType **game_grid
 * \param int column_number 
 * \param int row_number 
 * \param struct Player position 
 * \param int goals_nmr_d (goals number in total)
 * \param int goals_nmr_d (goals number done in total)
 * 
 * @brief Cette structure contient les informations concernant la grille du jeu et son contenu
 */
struct Grid{
	enum CaseType **game_grid; 	///< Tableau contenant les entités présents dans le jeu
	int column_number; ///< Nombre de colonne de game_grid
	int row_number; ///< Nomber de ligne de game_grid
	struct Player position; //player position
	int goals_nmr;  //goals number
	int goals_nmr_d; //goals done number
};

/**
 * \fn init_level(const char* file_path, struct Grid *lGrid);
 * 
 * \remark The procedure takes a file as a parameter txt with the game board and a \struct Grid
 * that will allocate the game board with all the information of the game level.
 * The procedure will open the file for reading txt file, then it will browse the file
 * to retrieve the values of rows, columns and objects, this information will be loaded into the \struct Grid,
 * then it goes through the rest of the file to retrieve 
 * the elements concerning the game board and they are loaded into the 
 * \struct Grid->game_grid. the procedure does not return anything, all allocations are made through the address pass.
 * 
 * \brief Function init_level allows to read .txt file which contain structure game levels
 * 
 * \param[in] const char* file_path 
 * \param[in] struct Grid *lGrid
 * 
 * \return void
 */
void init_level(const char* file_path, struct Grid *lGrid);

/**
 * \fn display(struct Grid *lGrid);
 * 
 * \remark The display procedure takes as a parameter an already filled \struct Grid, 
 * the procedure will use 2 index variables to browse the Grid->game_grid 
 * \struct where the game array elements are located, and also it will also use another variable line_returned. 
 * display will browse the row column by column in the \struct, 
 * and so it will display element by element content in the current position, 
 * then when the maximum number of column and traversed it will display a newline.
 * 
 * \brief Function display allows to display the game
 * 
 * \param[in] struct Grid *lGrid
 * \return void
*/
void display(struct Grid *lGrid);

/**
 * \fn freegrid(struct Grid *lGrid);
 * 
 * \brief The liberegrid procedure deallocates (clean) the addresses allocated for variable game_grid
 * 
 * \remark the liberegrid procedure takes as a parameter a \struct Grid the procedure will browse pointer by pointer 
 * in the \struct Grid -> game_grid  where the elements of the game are located, 
 * then it will release the allocations made with the function init_level, 
 * so that we free the memory, the procedure returns nothing and everything is done by passing by address.
 * 
 * \param[in] struct Grid *lGrid
 * \return void
*/
void freegrid(struct Grid *lGrid);

/**
 * \fn move_player(struct Grid *pGrid, struct Grid *mGrid, enum Direction mp, struct Player position);
 * 
 * \remark The function move_player takes as a parameter a \struct Grid and \enum Direction. 
 * The function uses a local variable new_position of type \struct Player to register 
 * the new direction, this new direction will be obtained with the operations
 * that the function does, according to the enter key as a parameter, 
 * it takes the current position of the personage in the \struct Grid->position
 * and does the operations -1 or +1 or even nothing, depending on the input key, 
 * then it saves the value in the local new_position variable for the later 
 * verification with if, in the later checks the function
 * will check what is in the next position and depending on what is in it, 
 * it may or may not move the personage symbol, then it erases (place NONE) 
 * what was in the current position. In this way if the next position contains a WALL or BOX 
 * the personage will not be able to move.
 * 
 * \brief The function move_player move player in direction Top, Left, Right, Bottom
 * 
 * \param[in] struct Grid *lGrid
 * \param[in] struct Grid *mGrid
 * \param enum Direction mp
 * \param struct Player position
 * \return void
*/
void move_player(struct Grid *lGrid, struct Grid *mGrid, enum Direction mp, struct Player position);

#endif