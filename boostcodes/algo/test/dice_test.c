#include "prob_dice.h"

int main(int argc, char *argv[])
{
	ss S;
	S.size = 36;


	samplespace_init(&S, S.size);

	probability_distribute(&S, S.size);

	randomvariate_init(&S, S.size);

	probability_distribution(&S);

	return 0;
}

