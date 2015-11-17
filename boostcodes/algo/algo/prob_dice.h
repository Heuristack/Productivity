#ifndef prob_dice_h
#define prob_dice_h

typedef struct {
	int dice1;
	int dice2;
} outcome;

typedef struct elementary_event {
	outcome s;
	double real_Pr;
	double real_X;
	double real_Y;
	double real_Z;
} ee;

typedef struct sample_space {
	int size;
	ee *S;
} ss;

typedef struct random_variate {
	double real_Pr;
	double real_X;
	double real_Y;
	double real_Z;
} rv;

int samplespace_init(ss *S, int size);
int probability_distribute(ss *S, int size);
int randomvariate_init(ss *S, int size);
double probability_density_discreteO(ss *S, double x);
double probability_density_discrete(ss *S, double x, double y, char mode);
double conditinal_probability(ss *S, double x, double y);
double probability_distribution(ss *S);


#endif
