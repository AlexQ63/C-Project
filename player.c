#include "player.h"
#include "board.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * defineNextPlay() {
  	char * answer = malloc (2 * sizeof(char));
    printf("Did you select the right piece? Press  no  for return or enter anything for continue your play: ");
	scanf("%2s", answer);

	return answer;
}

/*if (player == PLAYER1 || player == PLAYER2) {
			playerPlay(player, pieceBoard);
		}
		else {
			printf("You only can be the Player 1 or the Player 2");
			return;*/