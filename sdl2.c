#include "sdl2.h"
#include "grid.h"
#include <ncurses.h>

SDLContext context;

void sdl_init() {
  int const width = 1280;
  int const height = 720;
  context = (SDLContext){NULL, NULL, .width = 0, .height = 0};
  if (SDL_Init(SDL_INIT_VIDEO)) return;

  SDL_Window *window = SDL_CreateWindow("Sokoban", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
  if (!window) return;
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  context = (SDLContext){.window = window, .renderer = renderer, .width = width, .height = height};
}

/**
 * \brief Destruction of renderer and window
*/
void sdl_quit() {
  SDL_DestroyWindow(context.window);
  SDL_DestroyRenderer(context.renderer);
  context.window = NULL;
  context.renderer = NULL;
  SDL_Quit(); // close SDL
}

void display_sdl2(struct Grid * lGrid){
  float w = context.width / lGrid->column_number; 
  float h = context.height / lGrid->row_number; 
  float x = 0, y = 0;
  SDL_SetRenderDrawColor(context.renderer, 160, 160, 160, 255); // Set color Gray
  SDL_RenderClear(context.renderer); // clears the current render
  SDL_Rect rectangle;
	for(int i = 0; i < lGrid->row_number; i++) {
    for (int j = 0; j < lGrid->column_number; j++) {
      char current_position = lGrid->game_grid[i][j];
      switch (current_position)
      {
        case WALL:{
          SDL_SetRenderDrawColor(context.renderer, 178, 34, 34, 255); //set color red mixed orange for a wall
          rectangle.x = x, rectangle.y = y, rectangle.w = w, rectangle.h = h;
          SDL_RenderFillRect(context.renderer, &rectangle); // fill on the current render target with color
          break;
        }
        case PLAYER:{ 
          SDL_SetRenderDrawColor(context.renderer, 255, 255, 0, 255); //set color yellow for a player
          rectangle.x = x, rectangle.y = y, rectangle.w = w, rectangle.h = h;
          SDL_RenderFillRect(context.renderer, &rectangle); 
          break;
        }   
        case GOAL:{ 
          SDL_SetRenderDrawColor(context.renderer, 255, 255, 255, 255); //set color white for a goal 
          rectangle.x = x, rectangle.y = y, rectangle.w = w, rectangle.h = h;
          SDL_RenderFillRect(context.renderer, &rectangle);
          break;
        }
        case BOX:{ 
          SDL_SetRenderDrawColor(context.renderer, 102, 20, 0, 255); //set color brown for a box
          rectangle.x = x, rectangle.y = y, rectangle.w = w, rectangle.h = h;
          SDL_RenderFillRect(context.renderer, &rectangle); 
          break;
        }
        case BOX_LOADED:{ 
          SDL_SetRenderDrawColor(context.renderer, 0, 255, 0, 255); //set color green for loaded box
          rectangle.x = x, rectangle.y = y, rectangle.w = w, rectangle.h = h;
          SDL_RenderFillRect(context.renderer, &rectangle); 
          break;
        }
      }
      x = x + w;
    }
    x = 0;
    y = y + h;
  }
  SDL_RenderPresent(context.renderer); // show all
}

Event event_sdl2(){
  SDL_Event event;
  SDL_WaitEvent(&event); 
  switch (event.type){
        case SDL_KEYUP:{
          switch(event.key.keysym.sym){
            case SDLK_q: return Quit; break;
            case SDLK_h: return U; break;
            case SDLK_j: return D; break;
            case SDLK_k: return R; break;
            case SDLK_l: return L; break;
          }
          return None;
        } 
    }
    return None;
}


Event event(){
  noecho();
  cbreak();
  switch (getch()){
      case 'q': return Quit; break;
      case 'h': return U;    break;
      case 'j': return D;    break;
      case 'k': return R;    break;
      case 'l': return L;    break;
    }
  return None;
}
