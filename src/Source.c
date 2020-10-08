#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>.

#include "SDL.h"
#include "SDL_image.h"

#include "thegame.h"
#include "rendering.h"
#include "clickoncell.h"



int main(int argc, char *argv[]) {

	

	

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Cannnot initialize SDL2: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	SDL_Window *window = SDL_CreateWindow("Propaganda - YingQi & JunYao", 100, 100, SCREEN_LENGTH, SCREEN_WIDTH, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		fprintf(stderr, "Failed to Create Window Error: %s\n", SDL_GetError()); //ignore the warning message here
		return EXIT_FAILURE;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == NULL) {
		SDL_DestroyWindow(window);
		fprintf(stderr, "Renderer Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}


	int emptyboard[N][N];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			emptyboard[i][j] = EMPTY;
		}
	}
	int emptyboard2[N + 2][N + 2];
	for (int i = 0; i < N + 2; i++) {
		for (int j = 0; j < N + 2; j++) {
			emptyboard2[i][j] = EMPTY;
		}
	}

	game_t game = {
		.board = emptyboard,
		.grids = 0,
		.state = COVER_STATE,
		.turn = 0,
		.tempboard = emptyboard2,
		.score = 0,
		.pos = 0,
		.Surface = NULL
	};

	//This is to for debugging: create a surface and texture to make sure the image is loaded correctly.

	game.Surface = IMG_Load("O.png");
	if (game.Surface == NULL) {
		printf("Image error 31415\n\n");
		SDL_Quit();
		system("PAUSE");
		return 0;
	}

	game.Texture = SDL_CreateTextureFromSurface(renderer, game.Surface);
	SDL_FreeSurface(game.Surface);
	
	//////////////////////////////////////////


	game.board[0][0] = 0; // I had to manually add this because although I made all entries in game.board zero.
	                      // I have no idea why this happens.
	
	
	SDL_Event e;

	while (game.state != QUIT_STATE ) {
		
		while (SDL_PollEvent(&e)) {
			
			switch (e.type) {
			case SDL_QUIT:
				game.state = QUIT_STATE;
				break;
			case SDL_MOUSEBUTTONDOWN:
				click_on_cell(renderer, &game, e.button.y / CELL_WIDTH, e.button.x / CELL_LENGTH);
				break;
			default: {}
			}
		}

		checks_game(renderer, &game);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		render_game(renderer, &game);
		SDL_RenderPresent(renderer);
		game.pos++;
		if (game.pos > 360)
			game.pos = 0;
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}



