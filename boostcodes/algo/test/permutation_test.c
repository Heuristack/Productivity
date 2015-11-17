#include "algo.h"

void remain(char *s, int n, int i, char *t)
{
	for (int k = 0; k < n; k++) {
		if (k == i) continue;
		*t++ = s[k];
	}
}


int permgen(char *s, int n)
{
	static char *p = NULL;
	if (!p) p = (char *) malloc(sizeof(char) * n);
	// 1. memory leak: seems inevitable
	// 2. not ok: permgen("123", 3); permgen("1234",4);

	if (n == 0) return printf("%s\n", p); // one perm is constructed!
	char *t = (char *) malloc(sizeof(char) * (n-1));
	for (int i = 0; i < n; i++) {
		remain(s,n,i,t);
		p[n-1] = s[i];
		permgen(t, n-1);
	}
	free(t);
}

int main()
{
	char *s = "123";
	int n = strlen(s);
	permgen(s,n);
	return 0;
}
