/**
 * TITLE: ThreeD Expectation
 * AUTHOR: LiYing
 * DATE: 2012-8-17 12:04:03
 * NOTE: Birthday of Chinese Calendar: a present for myself
 *
 * Integrated to 'algo' lib.
 * 2015-1-8 23:07:22
 */

#ifndef prob_threed_h
#define prob_threed_h

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef unsigned long ulong;
typedef unsigned int uint;
typedef double randn;
typedef double realn;
typedef double real;


typedef struct point {
    unsigned x;         /* e.g. 7 */
    unsigned y;         /* e.g. 2 */
    unsigned z;         /* e.g. 8 */
} point;

typedef struct element {
    ulong index;        /* index: 728 */
    point threed;       /* threed: (threed.x, threed.y, three.z) = (7,2,8) */
    realn prob;         /* prob: 1/1000 used to compute theorital value */
    ulong occurs;       /* occurs: 8 ? */
    realn freq;         /* freq: 8/256 (stats.trials = 256) */
    randn rand;         /* rand: 728.00 random number assigned to this element */
    ulong sell;		    /* sell: used for selling statistics before each trial */
    ulong score;	    /* score: used for predicating next outcome */
} elem;

typedef struct statistics {
    elem *space;	    /* space: elementary element sample space */
    uint  size;		    /* size: the of the sample space */
    uint  trials;	    /* trials: number of trials */
    real  mean;		    /* mean: expectation value of space[index].rand */
    real  variance;	    /* variance: variance of space[index].rand with expectation mean */
} stats;

typedef struct trial {
    ulong index;        /* e.g. 2012001 - 2012365 */
    point result;	    /* result: (result.x, result.y, result.z) = (7,2,8) */
    ulong open;         /* open: 1-0 */
    ulong machine;	    /* machine: 01 / 02 */
    ulong ballset;	    /* ballset: 01 / 02 */
} trial;

typedef struct game {
    trial *trials;	    /* trials: trials[index].result.x: 7 */
    ulong  size;	    /* size: current size of the game */
    stats *sells;       /* sells: sells distribution before each trial */
} tridgame;

stats sample;		    /* the sample space of point(x, y, z) */
tridgame trid;		    /* the trid game: a sequence of trials */

char* threed_get_word(char *s, char *buffer);
int threed_trial_get(trial *t, char* s);
int print_trial(trial *t);
int threed_game_init(char *path, tridgame *g);
int threed_trials_traverse(trial *t, int size);
int print_elem(elem *e);
int threed_sample_init(stats *s, trial* t, int size);
int threed_sample_update(stats *s, trial* t, int size);
int threed_element_traverse(elem *s);

#endif

