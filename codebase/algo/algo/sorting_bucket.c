#include "sorting.h"

#define maxbucketnum 0x20

typedef struct bucket {
	double store[maxbucketnum];
	int num;
} bucket_t;

int printa(double a[], int n){
	for ( int i = 0; i < n; i++ )
		printf("%f ", a[i]);
	putchar('\n');
return 0; }/*printa*/

int printbucket(bucket_t *pbucket){
	for ( int i = 0; i < pbucket->num; i++ )
		printf("%f ", pbucket->store[i]);
	putchar('\n');
return 0; }/*printbucket*/

int bucketinsert(double value, bucket_t b[], int n){
	int i = (int)(n*value);
	b[i].store[b[i].num++] = value;
return 0; }/*bucketinsert*/

int sortbucket(bucket_t *pbucket){
	double key = 0.0;
	for ( int j, i = 1; i < pbucket->num; i++ ) {
		key = pbucket->store[i];
		for ( j = i - 1; j >= 0 && pbucket->store[j] > key; j-- )
            pbucket->store[j+1] = pbucket->store[j];
        pbucket->store[j+1] = key;
	}
return 0; }/*insertionsort*/

int bucket_sort(double a[], int n){
	bucket_t b[maxbucketnum];
	for ( int i = 0; i < n; i++ ) b[i].num = 0;
	for ( int i = 0; i < n; i++ ) bucketinsert(a[i], b, n);
	for ( int i = 0; i < n; i++ ) sortbucket(&b[i]);
	int k = 0;
	for ( int i = 0; i < n; i++ )
	for ( int j = 0; j < b[i].num; j++ ) a[k++] = b[i].store[j];
return 0; }/*bucket_sort*/
