#define PLAYER_X_WON_STATE 1
#define PLAYER_O_WON_STATE 2
#define TIE_STATE 3
#define QUIT_STATE 4
#define COVER_STATE 6

#include <stdio.h>

typedef struct {
	int board[N][N];
	int tempboard[N + 2][N + 2];
	int grids;
	int state;
	int turn;
	int score;
	int pos;
	SDL_Texture *Shooting_star;
	SDL_Surface *Star_sur;
}game_t;
#endif /* thegame_h */
