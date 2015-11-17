#include "perm.h"

static char *p = NULL;

// remain: remove element indexed by 'i' from set 's'; remaining is stored in 't';
void remain(char *s, int n, int i, char *t)
{
	for (int k = 0; k < n; k++) {
		if (k == i) continue;
		*t++ = s[k];
	}
}


// permgen: construct n-permutations on 's' into 'p' one-by-one
int permgen(char *s, int n)
{
	if (n == 0) return printf("%s\n", p); 	// one perm is constructed!
	char *t = (char *) malloc(sizeof(char) * (n-1));
	for (int i = 0; i < n; i++) {
		remain(s,n,i,t);
		p[n-1] = s[i];
		permgen(t, n-1);
	}
	free(t);
}// recurrence: T(n) = nT(n-1) = O(n!)


/**
 * perms: print all permutations of string `s`
 *
 * [Knuth.TAOCP.v1.p45]
 * "..., permutations are so important, Vaughan Pratt has suggested calling them perms."
 *
**/

void perms(char *s)
{
	int n = strlen(s);
	p = (char *) malloc(sizeof(char) * n);
	permgen(s,n);
	free(p);
}

