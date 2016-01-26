#ifndef comb_h
#define comb_h

#include <stdio.h>


typedef int (*procedure)();

int print(char *s);
int printn(char *s, int n);
int printnset(char *s, int n);

int kstring(char *string, int k, char *set, int n, procedure p);
int kpermutation(char *perm, int k, char *set, int n, procedure p);
int kcombination(char *comb, int k, char *set, char *in, int n, procedure p);
int ksubset(char *subset, int k, char *set, char *in, int n, procedure p);
int subsets(char *subset, char *set, char *in, int n, procedure p);

#endif
