#ifndef clickoncell_h
#define clickoncell_h

void click_on_cell(game_t *game, int row, int column);


void player_turn(game_t *game, int row, int column) {
	
	int count1;
	int count2;
	int score;
	

	for (count1 = 0; count1 < N; count1++) {
		for (count2 = 0; count2 < N; count2++) {
			game->tempboard[count1 + 1][count2 + 1] = game->board[count1][count2];
		}
	}

	for (count1 = 0; count1 < N; count1++) {
		for (count2 = 0; count2 < N; count2++) {

			score = game->tempboard[count1][count2 + 1] + game->tempboard[count1 + 2][count2 + 1] +
				game->tempboard[count1 + 1][count2] + game->tempboard[count1 + 1][count2 + 2];

			if (game->tempboard[count1+1][count2+1] == 0 && score > 0) {
				game->board[count1][count2] = 1;
				game->grids++;
				
			}
			if (game->tempboard[count1+1][count2+1] == 0 && score < 0) {
				game->board[count1][count2] = -1;
				game->grids++;
			}
		}
	}
	if (game->turn % 4 == 0 || game->turn % 4 == 3) {
		if (game->board[row][column] == EMPTY) {
			game->grids++;
		}
		game->board[row][column] = 1;
		
	}
	else {
		if (game->board[row][column] == EMPTY) {
			game->grids++;
		}
		game->board[row][column] = -1;
	}
	
	game->turn++;
	
	return;
}
void reset_game(SDL_Renderer * renderer, game_t *game) {
	SDL_RenderClear(renderer);
	game->turn = 0;
	game->grids = 0;
	game->score = 0;
	game->state = RUNNING_STATE;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			game->board[i][j] = EMPTY;
		}
	}
	return;
}
void click_on_cell(SDL_Renderer * renderer, game_t *game, int row, int column) {
	if (game->state == RUNNING_STATE) {
		if (game->board[row][column] == EMPTY) {
			player_turn(game, row, column);
		}
	}
	else {
		
		if (game->state == COVER_STATE) {
			if (row > 14 && column > 14 && row < 18 && column < 18) {
				game->state = QUIT_STATE;
			}
			if (row > 8 && column >= 2 && row < 16 && column < 15) {
				SDL_RenderClear(renderer);
				game->state = RUNNING_STATE;

			}
		}
		else {
			if (row < 10 && column > 10)
				reset_game(renderer, game);
			if (row > 10 && column < 10)
				game->state = QUIT_STATE;
		}
		
	}
	return;
}
#endif /* clickoncell_h */
