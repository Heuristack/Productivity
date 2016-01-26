#include "sorting.h"
#include "algo.h"

static int input[MAX];
static int n = 0;

void readinput(int x)
{
	if (!(x < MAX)) return;
	if (!(n < MAX)) return;
	if (scanf("%d", &x) == EOF) return;
	input[n++] = x;
	readinput(n);
}

void getinput(int A[])
{
	for (int i = 0; i < n; i++)
		A[i] = input[i];
}

void getinputchar(int A[])
{
	for (int i = 0; i < n; i++)
		A[i] = (char)input[i];
}

void print(char *prompt, int A[])
{
	if (!prompt) prompt = "!><";
	printf("%s", prompt);
	if (!A) A = input;
	for (int i = 0; i < n; i++) {
		printf(" %d", A[i]);
	}
	printf("\n");
}


int test()
{

	printf("%s\n", "sorting test [enter!]");

	readinput(1);
	printf("input\n");
	print(":>>", NULL);

	printf("\n%s\n", "sorting by exchange:");
	printf("bubblesort:\n"); {
	int A[MAX]; getinput(A);
	bubblesort(A, n); print(":<<", A); }

	printf("shellsort:\n"); {
	int A[MAX]; getinput(A);
	shellsort(A, n); print(":<<", A); }

	printf("shellsortmcgs:\n"); {
	int A[MAX]; getinput(A);
	shellsortmcgs(A, n); print(":<<", A); }

	printf("\n%s\n", "sorting by partition:");
	printf("quicksort:\n"); {
	int A[MAX];	getinput(A);
	int p = 0; int q = n - 1;
	quicksort(A, p, q); print(":<<", A); }

	printf("sortbypartitionbyexchange:\n"); {
	int A[MAX];	getinput(A);
	int p = 0; int q = n - 1;
	sortbypartitionbyexchange(A, p, q); print(":<<", A); }

	printf("sortbypartition3byexchange:\n"); {
	int A[MAX];	getinput(A);
	int p = 0; int q = n - 1;
	sortbypartition3byexchange(A, p, q); print(":<<", A); }


	printf("\n%s\n", "sorting by selection:");
	printf("selectsort:\n"); {
	int A[MAX];	getinput(A);
	selectsort(A, n); print(":<<", A); }

	printf("selectminsort:\n"); {
	int A[MAX];	getinput(A);
	selectminsort(A, n); print(":<<", A); }

	printf("selectionsort:\n"); {
	int A[MAX];	getinput(A);
	selectionsort(A, n); print(":<<", A); }

	printf("reselectminsort:\n"); {
	int A[MAX];	getinput(A);
	int p = 0; int q = n - 1;
	reselectminsort(A, p, q); print(":<<", A); }

	printf("\n%s\n", "sorting by insertion:");
	printf("insertsortbyshift:\n"); {
	int A[MAX];	getinput(A);
	insertsortbyshift(A, n); print(":<<", A); }

	printf("insertsortbyexchange:\n"); {
	int A[MAX];	getinput(A);
	insertsortbyexchange(A, n); print(":<<", A); }

	printf("sortbyinsertionbyshifting:\n"); {
	int A[MAX];	getinput(A);
	sortbyinsertionbyshifting(A, n); print(":<<", A); }

	printf("sortbyinsertionbyexchange:\n"); {
	int A[MAX];	getinput(A);
	sortbyinsertionbyexchange(A, n); print(":<<", A); }


	printf("sortbysiftup:\n"); {
	int A[MAX];	getinput(A);
	sortbysiftup(A, n); print(":<<", A); }

	printf("sortbycounting:\n"); {
	int A[MAX];	getinput(A);
	countingsort(A, n); print(":<<", A); }

	printf("radix sort:\n"); {
	int A[MAX];	getinput(A);
	byteradixsort(A, n); print(":<<", A); }


	{
	double a[] = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68};
	double b[] = {0.79, 0.13, 0.16, 0.64, 0.39, 0.20, 0.89, 0.53, 0.71, 0.42};
	int n = sizeof(a)/sizeof(double);
	printa(a, n);
	bucket_sort(a, n);
	printa(a, n);
	printa(b, n);
	bucket_sort(b, n);
	printa(b, n);
	}

	printf("%s\n", "sorting test [leave!]");
}

int main()
{

	readinput(1);
	printf("input\n");
	print(":>>", NULL);

	printf("sortbypartition3byexchange:\n"); {
	int A[MAX];	getinput(A);
	int p = 0; int q = n - 1;
	sortbypartition3byexchange(A, p, q); print(":<<", A); }
}

