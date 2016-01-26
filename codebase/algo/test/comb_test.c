#include "comb.h"

int main()
{
	char string[4]; string[3] = 0;
	char *set = "123";
	char in[3];

	// kstring(string,3,set,3,print);
	// kpermutation(string,3,set,3,print);
	// ksubset(string,0,set,in,3,printnset);
	subsets(string, set, in, 3, printnset);
}
