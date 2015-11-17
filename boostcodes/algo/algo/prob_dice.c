/*
 * Integrated to 'algo' lib.
 * 2015-1-8 23:07:22
 */
#include "prob_dice.h"

int samplespace_init(ss *S, int size)
{
	S->S = (ee *)malloc(size*sizeof(ee));
	int j = 0;
	for (int i = 1; i <= 6; i++)
	for (int k = 1; k <= 6; k++)
	{
	  S->S[j].s.dice1 = i;
	  S->S[j].s.dice2 = k;

//	  printf("[%d][%d]\n", S->S[j].s.dice1, S->S[j].s.dice2);

	  j++;
	}
	return 0;
}

int probability_distribute(ss *S, int size)
{
	double normal = 0.0;
	int j = 0;
	for (int i = 1; i <= 6; i++)
	for (int k = 1; k <= 6; k++)
	{
	  double uniform = 1/(double)size;
	  S->S[j].real_Pr = uniform;

//	  printf("[%2d][%d][%d]:Pr[%f]\n", j, S->S[j].s.dice1, S->S[j].s.dice2, S->S[j].real_Pr);

	  normal += S->S[j].real_Pr;
	  j++;
	}
	  printf("            Normal:Pr[%f]\n", normal);
	return 0;
}

int randomvariate_init(ss *S, int size)
{
	int j = 0;
	for (int i = 1; i <= 6; i++)
	for (int k = 1; k <= 6; k++)
	{
	  S->S[j].real_X = (i > k) ? i : k;
	  S->S[j].real_Y = (i < k) ? i : k;
	  S->S[j].real_Z = i + k;

	  printf("EE[%2d]:Point[%d][%d]:Pr[%f]:X[%f]:Y[%f]Z:[%04.1F]\n", j, S->S[j].s.dice1, S->S[j].s.dice2, S->S[j].real_Pr, S->S[j].real_X, S->S[j].real_Y, S->S[j].real_Z);

	  j++;
	}
	return 0;
}


double probability_density_discreteO(ss *S, double x)
{
	double prob = 0.0;
	for (int i = 0; i < S->size; i++)
	  prob += (S->S[i].real_X == x) ? S->S[i].real_Pr : 0.0;
	return prob;
}

double probability_density_discrete(ss *S, double x, double y, char mode)
{
	double pr = 0.0;

	if (mode == 0){
	for (int i = 0; i < S->size; i++)
		if (S->S[i].real_X == x && S->S[i].real_Y == y)
			pr += S->S[i].real_Pr;
	}

	if (mode == 'X'){
	x = x;
	for (int i = 0; i < S->size; i++)
		if (S->S[i].real_X == x)
			pr += S->S[i].real_Pr;
	}

	if (mode == 'Y'){
	y = x;
	for (int i = 0; i < S->size; i++)
		if (S->S[i].real_Y == y)
			pr += S->S[i].real_Pr;
	}

	if (mode == 'Z'){
	double z = x;
	for (int i = 0; i < S->size; i++)
		if (S->S[i].real_Z == z)
			pr += S->S[i].real_Pr;
	}

	return pr;
}

double conditinal_probability(ss *S, double x, double y)
{
	double condprob = 0.0;
	condprob  = probability_density_discrete(S, x, y, 0);
	condprob /= probability_density_discrete(S, y, 0, 'Y');
	return condprob;
}

double probability_distribution(ss *S)
{
	double normal = 0.0;
	double expectation = 0.0;

	rv *distX = (rv *)malloc(6*sizeof(rv));
	for (int x = 1; x <= 6; x++) {
	  distX[x-1].real_X = x;
	  distX[x-1].real_Pr = probability_density_discrete(S, (double)x, 0, 'X');

	  normal += distX[x-1].real_Pr;
	  expectation += distX[x-1].real_X*distX[x-1].real_Pr;

	  printf("X:[%f]Pr[%f]\n", distX[x-1].real_X, distX[x-1].real_Pr);
	}
	printf("Normal:[%f]\n", normal);
	printf("Expectation:[%f]\n", expectation);

	rv *distY = (rv *)malloc(6*sizeof(rv));
	normal = 0.0;
	expectation = 0.0;
	for (int y = 1; y <= 6; y++) {
	  distY[y-1].real_Y = y;
	  distY[y-1].real_Pr = probability_density_discrete(S, (double)y, 0, 'Y');

	  normal += distX[y-1].real_Pr;
	  expectation += distY[y-1].real_Y*distY[y-1].real_Pr;

	  printf("Y:[%f]Pr[%f]\n", distY[y-1].real_Y, distY[y-1].real_Pr);
	}
	printf("Normal:[%f]\n", normal);
	printf("Expectation:[%f]\n", expectation);

	rv *distZ = (rv *)malloc(12*sizeof(rv));
	normal = 0.0;
	expectation = 0.0;
	for (int z = 1; z <= 12; z++) {
	  distZ[z-1].real_Z = z;
	  distZ[z-1].real_Pr = probability_density_discrete(S, (double)z, 0, 'Z');

	  normal += distZ[z-1].real_Pr;
	  expectation += distZ[z-1].real_Z*distZ[z-1].real_Pr;

	  printf("Z:[%2.0f]Pr[%f]\n", distZ[z-1].real_Z, distZ[z-1].real_Pr);
	}
	printf("Normal:[%f]\n", normal);
	printf("Expectation:[%f]\n", expectation);


	rv *distXY = (rv *)malloc(36*sizeof(rv));
	normal = 0.0;
	int j = 0;
	for (int x = 1; x <= 6; x++)
	for (int y = 1; y <= 6; y++)
	{
	  distX[j].real_X = x;
	  distY[j].real_Y = y;
	  distY[j].real_Pr = probability_density_discrete(S, (double)x, (double)y, 0);

	  normal += distY[j].real_Pr;
	  printf("XY:[%f][%f]Pr[%f]\n", distX[j].real_X, distY[j].real_Y, distY[j].real_Pr);
	  j++;
	}
	printf("Normal:[%f]\n", normal);


	rv *distXgivenY = (rv *)malloc(36*sizeof(rv));
	j = 0;
	for (int y = 1; y <= 6; y++)
	{
	normal = 0.0;
	for (int x = 1; x <= 6; x++)
	{
	  distXgivenY[j].real_X = x;
	  distXgivenY[j].real_Y = y;
	  distXgivenY[j].real_Pr = conditinal_probability(S, (double)x, (double)y);

	  normal += distXgivenY[j].real_Pr;
	  printf("XgivenY:[%f][%f]Pr[%f]\n", distXgivenY[j].real_X, distXgivenY[j].real_Y, distXgivenY[j].real_Pr);
	  j++;
	}
	printf("Normal:[%f]\n", normal);
	}

	return 0.0;
}
