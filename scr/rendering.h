#include <Windows.h>

#ifndef rendering_h
#define rendering_h

void render_game(SDL_Renderer *renderer, const game_t *game);
void render_cover(SDL_Renderer * renderer, game_t *game);
#endif /* rendering_h */

//FUNCTION PROTOTYPES

const SDL_Color GRID_COLOUR = { .r = 255,.g = 255,.b = 255 };
const SDL_Color PLAYER_X_COLOR = { .r = 255,.g = 50,.b = 50 };
const SDL_Color PLAYER_O_COLOR = { .r = 50,.g = 100,.b = 255 };
const SDL_Color TIE_COLOR = { .r = 100,.g = 100,.b = 100 };

void render_grid(SDL_Renderer *renderer, const SDL_Color *color) {
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);

	for (int i = 0; i < N; ++i) {
		SDL_RenderDrawLine(renderer, i * CELL_LENGTH, 0, i * CELL_LENGTH, SCREEN_WIDTH);
		SDL_RenderDrawLine(renderer, 0, i* CELL_WIDTH, SCREEN_LENGTH, i * CELL_WIDTH);
	}
	
}

void render_x(SDL_Renderer *renderer, int row, int column) {

	SDL_Texture *X_image;
	SDL_Surface *X_surface = NULL;

	X_surface = IMG_Load("X.png");
	if (X_surface == NULL) {
		printf("Image error 31415\n\n");
		SDL_Quit();
		system("PAUSE");
		return 0;
	}

	X_image = SDL_CreateTextureFromSurface(renderer, X_surface);            ////////////////////Images Here
	SDL_FreeSurface(X_surface);
	SDL_Rect Ximage = { column * CELL_LENGTH, row * CELL_WIDTH,32,32 };
	SDL_RenderCopy(renderer, X_image, NULL, &Ximage);
}

void render_o(SDL_Renderer *renderer, int row, int column) {
	
	SDL_Texture *O_image;
	SDL_Surface *O_surface = NULL;

	O_surface = IMG_Load("O.png");
	if (O_surface == NULL) {
		printf("Image error 31415\n\n");
		SDL_Quit();
		system("PAUSE");
		return 0;
	}

	O_image = SDL_CreateTextureFromSurface(renderer, O_surface);
	SDL_FreeSurface(O_surface);
	SDL_Rect Oimage = { column * CELL_LENGTH, row * CELL_WIDTH,32,32 };
	SDL_RenderCopy(renderer, O_image, NULL, &Oimage);
}
void render_board(SDL_Renderer *renderer, const int *board[][N], const SDL_Color *player_x_color, const SDL_Color *player_o_color) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			int temp = board[i][j];
			switch (temp) {
			case PLAYER_X:
				render_x(renderer, i, j);
				break;
			case PLAYER_O:
				render_o(renderer, i, j);
				break;

			default: {}

			}
		}
	}
}


void render_game_state(SDL_Renderer *renderer, const game_t *game) {
	render_grid(renderer, &GRID_COLOUR);
	render_board(renderer, game->board, &PLAYER_X_COLOR, &PLAYER_O_COLOR);
}

void render_gamewon_state(SDL_Renderer * renderer, const game_t *game, const SDL_Color *color) {
	SDL_Texture *X_won_image;
	SDL_Surface *X_won_surface = NULL;
	SDL_Texture *O_won_image;
	SDL_Surface *O_won_surface = NULL;

	X_won_surface = IMG_Load("X_won.png");
	if (X_won_surface == NULL) {
		printf("Image error 31415\n\n");
		SDL_Quit();
		system("PAUSE");
		return 0;
	}

	X_won_image = SDL_CreateTextureFromSurface(renderer, X_won_surface);
	SDL_FreeSurface(X_won_surface);
	SDL_Rect Xwonimage = { 0, 0,1080,720};

	O_won_surface = IMG_Load("O_won.png");
	if (O_won_surface == NULL) {
		printf("Image error 31415\n\n");
		SDL_Quit();
		system("PAUSE");
		return 0;
	}

	O_won_image = SDL_CreateTextureFromSurface(renderer, O_won_surface);
	SDL_FreeSurface(O_won_surface);
	SDL_Rect Owonimage = { 0, 0,1080,720};
	
	if (game->state == PLAYER_O_WON_STATE) {
		SDL_RenderCopy(renderer, O_won_image, NULL, &Owonimage);
	}
	if (game->state == PLAYER_X_WON_STATE) {
		SDL_RenderCopy(renderer, X_won_image, NULL, &Xwonimage);
		printf("%d\score is", game->score);
	}

}

void render_game(SDL_Renderer *renderer, game_t *game) {
	switch (game->state) {
	case RUNNING_STATE:
		render_game_state(renderer, game);
		break;

	case PLAYER_X_WON_STATE:
		render_gamewon_state(renderer, game, &PLAYER_X_COLOR);
		break;

	case PLAYER_O_WON_STATE:
		render_gamewon_state(renderer, game, &PLAYER_O_COLOR);
		break;

	case COVER_STATE:
		render_cover(renderer, game);
		break;

	default: {}
	}
}

void checks_game(SDL_Renderer *renderer, game_t *game) {

	game->score = 0;

	if (game->grids == 19 * 19) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				game->score += game->board[i][j];
			}
		}
		if (game->score > 0 && game->state == RUNNING_STATE)
			game->state = PLAYER_X_WON_STATE;
		if (game->score < 0 && game->state == RUNNING_STATE)
			game->state = PLAYER_O_WON_STATE;
	}
}

void render_cover(SDL_Renderer * renderer, game_t *game) {

	SDL_Texture *Cover_image;
	SDL_Surface *Cover_surface = NULL;

	

	Cover_surface = IMG_Load("Cover.png.png");
	if (Cover_surface == NULL) {
		printf("Image error 31415\n\n");
		SDL_Quit();
		system("PAUSE");
		return 0;
	}

	Cover_image = SDL_CreateTextureFromSurface(renderer, Cover_surface);
	SDL_FreeSurface(Cover_surface);
	SDL_Rect Coverimage = {0,0,1080,720 };
	SDL_RenderCopy(renderer, Cover_image, NULL, &Coverimage);

	//////////////////////////

	SDL_Rect posdim = { 0, 2 * game->pos,32,32 };
	//printf("%d\n", game->pos);
	//SDL_RenderCopy(renderer, game->Shooting_star, NULL, &posdim);
	
	return;
}
