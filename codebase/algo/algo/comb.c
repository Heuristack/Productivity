#include "comb.h"

int print(char *s)
{
	return printf("%s\n", s);
}

int printn(char *s, int n)
{
	for (int i = 0; i < n; i++) putchar(s[i]);
	return putchar('\n');
}

int printnset(char *s, int n)
{
	printf("{");
	for (int i = 0; i < n - 1; i++) printf("%c,", s[i]);
	if (n) printf("%c", s[n-1]);
	printf("}\n");
}

int kstring(char *string, int k, char *set, int n, procedure p)
{
	static char *s = NULL; if (!s) s = string;
	if (k == 0) return p(s);
	for (int i = 0; i < n; i++) {
		*string = set[i];
		kstring(string+1,k-1,set,n, p);
	}
}

// remain: remove element indexed by 'i' from set 's'; remaining is stored in 't';
void remain(char *s, int n, int i, char *t)
{
	for (int k = 0; k < n; k++) {
		if (k == i) continue;
		*t++ = s[k];
	}
}

int kpermutation(char *perm, int k, char *set, int n, procedure p)
{
	static char *s = NULL; if (!s) s = perm;
	if (k == 0) return p(s);
	char *t = (char *) malloc(sizeof(char) * (n-1));
	for (int i = 0; i < n; i++) {
		remain(set,n,i,t);
		*perm = set[i];
		kpermutation(perm+1,k-1,t,n-1,p);
	}
	free(t);
}

int kform(char *subset, int k, char *set, char *in, int n)
{
	int numin = 0;
	for (int i = 0; i < n; i++) if (in[i] == '1') ++numin;
	if (numin != k) return 0;
	for (int i = 0; i < n; i++) if (in[i] == '1') {
		*subset++ = set[i];
	}
	return 1;
}

int ksubset(char *subset, int k, char *set, char *in, int n, procedure p)
{
	static char *s = NULL; if (!s) s = in;
	static int m = -1; if (m == -1) m = n;
	if (n == 0) {
		if (!kform(subset, k, set, s, m)) return 0;
		else return p(subset, k);
	}
	for (int i = 0; i < 2; i++) {
		*in = '0' + i;
		ksubset(subset, k, set, in+1, n-1, p);
	}
}

int kcombination(char *subset, int k, char *set, char *in, int n, procedure p)
{
	return ksubset(subset,k,set,in,n,p);
}

int form(char *subset, char *set, char *in, int n)
{
	int numin = 0;
	for (int i = 0; i < n; i++) if (in[i] == '1') {
		*subset++ = set[i];
		++numin;
	}
	return numin;
}

int subsets(char *subset, char *set, char *in, int n, procedure p)
{
	static char *s = NULL; if (!s) s = in;
	static int m = -1; if (m == -1) m = n;
	if (n == 0) {
		int k = form(subset, set, s, m);
		return p(subset, k);
	}
	for (int i = 0; i < 2; i++) {
		*in = '0' + i;
		subsets(subset, set, in+1, n-1, p);
	}
}

