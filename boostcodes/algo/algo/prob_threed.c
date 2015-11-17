/**
 * TITLE: ThreeD Expectation
 * AUTHOR: LiYing
 * DATE: 2012-8-17 12:05:46
 * NOTE: Birthday of Chinese Calendar: a present for myself
 *
 * Integrated to 'algo' lib.
 * 2015-1-8 23:07:22
 */

//1. no performance consideration
//2. iterative programming

#include "prob_threed.h"

char* threed_get_word(char *s, char *buffer){
//note: stirng s must ended with '\n' at present
	char *p = s;
	while (isblank(*p) && *p != '\n') p++;
	while (*p != ' ' && *p != '\t' && *p != '\n'){
	    *buffer++ = *p++;
	}
	*buffer = '\0';
	return p;
}//threed_get_word

int threed_trial_get(trial *t, char* s){
	char *p = s;
	char buffer[0xf];

	if (*p != '2') return -1;

	p = threed_get_word(p, buffer);
	t->index = (unsigned long)atoi(buffer);

	p = threed_get_word(p, buffer);
	t->result.x = buffer[0] - '0';
	t->result.y = buffer[1] - '0';
	t->result.z = buffer[2] - '0';

	p = threed_get_word(p, buffer);
	t->open = (unsigned long)atoi(buffer);

	p = threed_get_word(p, buffer);
	t->machine = (unsigned long)atoi(buffer);

	p = threed_get_word(p, buffer);
	t->ballset = (unsigned long)atoi(buffer);

	return 0;
}//threed_trial_get

int print_trial(trial *t){
	printf("[%ld|%d.%d.%d|%1d|%1d|%1d]", t->index, \
	t->result.x, t->result.y, t->result.z, \
	t->open, t->machine, t->ballset);
	return 0;
}//print_trial

int threed_game_init(char *path, tridgame *g){

	FILE* fp;
	fp = fopen(path, "r");

	char line[0xff];
	unsigned int num = 0;
	while (fgets(line, 0xff, fp) != NULL){
	  if (line[0] != '2') continue;
	  printf("%s", line);
	  num++;
	}
	printf("threed_game_init: number of legal lines: %d\n", num);
	fclose(fp);

	g->size = num;
	g->trials = (trial* )malloc(trid.size*sizeof(trial));

	fp = fopen(path, "r");
	unsigned int index = 0;
	while (fgets(line, 0xff, fp) != NULL){
	  if (line[0] != '2') continue;
	  threed_trial_get(&g->trials[index], line);
	  index++;
	}
	fclose(fp);

	return 0;
}//threed_game_init

int threed_trials_traverse(trial *t, int size){
	while (size--){
	print_trial(t++);
	printf("\n");
	}
	return 0;
}//threed_trials_traverse

int print_elem(elem *e){
	printf("[%03d|%d.%d.%d|%03d|%3.3f|%3.3f|%03.0f]", e->index, \
	e->threed.x, e->threed.y, e->threed.z, \
	e->occurs, e->freq, e->prob, e->rand);
}//print_elem

int threed_sample_init(stats *s, trial* t, int size){

	s->trials = size;
	s->size = 1000;
	s->space = (elem* )malloc(s->size*sizeof(elem));

	unsigned x, y, z, k = 0;
	for (x = 0; x < 10; x++)
	for (y = 0; y < 10; y++)
	for (z = 0; z < 10; z++)
	{
	    s->space[k].index = k;

	    s->space[k].threed.x = x;
	    s->space[k].threed.y = y;
	    s->space[k].threed.z = z;

	    s->space[k].occurs = 0;
	    s->space[k].freq = 0.0;
	    s->space[k].prob = 0.001;
	    s->space[k].rand = 0.0;

	    k++;
	}

	for (k = 0; k < size; k++, t++)
	{
	    unsigned index = 100*(t->result.x) + 10*(t->result.y) + 1*(t->result.z);
	    ++(s->space[index].occurs);
	}

	return 0;
}//threed_sample_init

int threed_sample_update(stats *s, trial* t, int size){
	s->trials += size;
	while (size--)
	{
	    unsigned index = 100*(t->result.x) + 10*(t->result.y) + 1*(t->result.z);
	    ++(s->space[index].occurs);
	}
	return 0;
}//threed_sample_update

int threed_element_traverse(elem *s){
	unsigned x, y, z, k = 0;
	for (x = 0; x < 10; x++){
	for (y = 0; y < 10; y++){
	for (z = 0; z < 10; z++){

	    print_elem(s++);
	    printf(" ");
	    k++;
            if(z == 4) printf("\n");
	}//z
	    printf("\n");
	}//y
	    printf("\n");
	}//x
	return 0;
}//threed_element_traverse

