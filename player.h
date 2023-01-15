#ifndef PLAYER_HEADER
#define PLAYER_HEADER

/**
 * @enum Direction player.h
 * @brief Direction contain direction to move Top='h', Left='k', Right='l', Bottom='j'
*/
enum Direction{
    Top = 'h' ,
    Left = 'k',
    Right = 'l',
    Bottom = 'j',
};

/**
 * @struct Player player.h
 * \param x int
 * \param y int
 * @brief struct Player contain positions of player: x and y 
*/
struct Player{
    int x;
    int y;
};

#endif