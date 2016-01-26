#include "prob_threed.h"

int main(int argc, char *argv[]){

{ //test: threed_get_word
	char *s = "Today is my birthday!\n";
	char *p = s;
	char buffer[0xf];
	while (*p != '\n'){
	  p = threed_get_word(p, buffer);
	  printf("%s\n", buffer);
	}
} //test: threed_get_word

{ //test: threed_trial_get
	char *s = "2012001	111	1	1	1\n";
	trial t;
	int r = threed_trial_get(&t, s);
	if (r != 0) printf("threed_trial_get test failed!\n");
	print_trial(&t);
} //test: threed_trial_get

{ //test: threed_game_init
	threed_game_init(argv[1], &trid);
} //test: threed_game_init

{ //test: threed_trials_traverse
	threed_trials_traverse(trid.trials, trid.size);
} //test: threed_trials_traverse

{ //test: threed_sample_init
	threed_sample_init(&sample, trid.trials, trid.size);
} //test: threed_sample_init

{ //test: threed_element_traverse
	threed_element_traverse(sample.space);
} //test: threed_element_traverse

	return 0;
}//main

