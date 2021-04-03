/* Implementation of "square nim" game: Game state is an integer. In each round,
 * you and AI alternate subtracting a positive square number from the game
 * state. If a move brings the game state to zero or negative, the player who
 * made that move loses.
 * This implementation uses negamax for the AI. */

#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

int state;
bool *first_mover_loses;

void set_starting_number() {
	printf("Set starting value: ");
	scanf("%d", &state);
}

bool valid_move(int x) {
	if (x <= 0) return false;
	for (int i = 1; ; i++) {
		if (i * i == x) return true;
		if (i * i > x) return false;
	}
}

int get_player_move() {
	int move;
	while (true) {
		printf("Player move: ");
		scanf("%d", &move);
		if (valid_move(move)) {
			return move;
		} else printf("Invalid move, try again\n");
	}
}

bool compute_first_mover_loses(int curr_state) {
	for (int i = 1; i * i <= curr_state; i++) {
		const int new_state = curr_state - (i*i);
		if (first_mover_loses[new_state]) return false;
	}
	return true;
}

void compute_state_values(int max_state) {
	first_mover_loses = malloc((max_state + 1) * sizeof(bool));
	first_mover_loses[0] = false;
	for (int i = 1; i <= max_state; i++) {
		first_mover_loses[i] = compute_first_mover_loses(i);
	}
}

int get_ai_move() {
	int best_move = -1;
	for (int i = 1; i * i <= state; i++) {
		const int move = i*i;
		const int new_state = state - move;
		if (first_mover_loses[new_state]) {
			best_move = move;
			// Don't break, rather take highest move that still guarantees win
		}
	}

	if (best_move == -1) return 1;
	else return best_move;
}

void game_loop() {
	while (true) {
		int player_move = get_player_move();
		state -= player_move;
		printf("Player subtracts %d, state is now %d\n\n", player_move, state);
		if (state <= 0) {
			printf("AI wins\n");
			return;
		}

		int ai_move = get_ai_move();
		state -= ai_move;
		printf("AI subtracts %d, state is now %d\n\n", ai_move, state);
		if (state <= 0) {
			printf("Player wins\n");
			return;
		}
	}
}

int main() {
	set_starting_number();
	compute_state_values(state);
	printf("\n");
	game_loop();
}
