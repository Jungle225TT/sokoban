#ifndef SDL2_HEADER
#define SDL2_HEADER
#pragma once
#include <SDL2/SDL.h>
#include "grid.h"

/**
 * @struct declaration of \struct SDLContext sdl2.h
 * 
 * \param[in] SDL_Window *window
 * \param[in] SDL_Render *render 
 * \param int height  
 * \param int width  
 * 
 * @brief \struct using for creating (size height, width) and working window.
*/
typedef struct SDLContext {
  SDL_Window *window;    
  SDL_Renderer *renderer; 
  int width;            
  int height;            
} SDLContext;

/**
 * @enum declaration of \enum Event sdl2.h
 * 
 * \param Enum contains U (up), D(down), L(left), R(right), None and quit
 * 
 * @brief enum Event using for moving on the game
*/
typedef enum Event{
  U, 
  D, 
  L, 
  R,
  None,
  Quit
} Event;

/**
 * @brief Declaration global context
*/
extern SDLContext context; 

/**
 * \fn void sdl_init();
 * \remark function sdl_init initializes a global extern SDLContext context
 * 
 * \param extern SDLContext context
 * 
 * @brief If there is an error during initialization -> context.window = NULL and
 *                                                      context.render = NULL
 * \return void
*/
void sdl_init();

/**
 * \fn void sdl_quit();
 * 
 * @brief function sdl_quit clean global extern SDLContext context
 * 
 * \param extern SDLContext context
 * \return void
*/
void sdl_quit();

/**
 * \fn void display_sdl2(struct Grid * lGrid);
 * 
 * @brief function display_sdl2 display game with SDL2
 * 
 * \remark function procedure takes as a parameter an already filled \struct Grid,
 * choose the sand background color for the game window and browse 
 * the Grid->game_grid structure where the the elements of the game board and display,
 * the elements in the form of with the assigned colors 
 * Player is yellow, Wall is red, 
 * Box is dark brown, Deposit area is white, Box in the drop zone is green
 * 
 * @param[in] struct Grid *lGrid 
 * \return void
*/
void display_sdl2(struct Grid * lGrid);

/**
 * \fn Event event_sdl2();
 * 
 * \remark SDLK_* allows to move in game. it work due to with special commands. Game allow commands(keys) like: h-up, j-down, k-left l-righ and q-quit
 * 
 * @brief the procedure allows to move in game.Direction using h-up, j-down, k-left l-righ and q-quit keys
 * \return Event
*/
Event event_sdl2();

/**
 * \fn Event event();
 * \remark unlike event_sdl2() this function work with ASCII
 * @brief choosen command allows to move in game. Direction using h-up, j-down, k-left l-righ and q-quit keys
 * \return Event
*/
Event event();

#endif