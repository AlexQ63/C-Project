#include "player.h"
#include <stdio.h>

char * defineNextPlay() {
  	char answer[2];
    printf("Did you select the right piece? Press  no  for return or enter another pair of positions for continue your play: ");
	scanf("%s", answer);
	return answer;
}