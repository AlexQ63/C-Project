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

_Bool compareCharWithList(char * selectPiece, char * list) {
	char * oneLetter;
	for (int i = 0; i < 4; i++) {
		oneLetter = &list[i];
		if (strcmp(oneLetter, &selectPiece[0])) {
			return TRUE;
		}
	}
	return FALSE;
}