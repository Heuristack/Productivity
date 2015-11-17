/**
 *
 * This program is used to illustrate the "matrix multipication principle"
 * The problem could be simulated as putting m*kmax*n pair-product-ball into
 * the m*n result matrix. So the six different "ijk" patterns represent
 * different putting method respectively. This kind of analysis could be called
 * "The Combinatics Analysis of Matrix Computation".
 *
 * 20:28 2012-4-12. All rights reserved.
 * The author's mailboxes are liying@abchina.com and guaguashu@gmail.com
 *
 * matrix multiplication design under the paradigm of divide-and-conquer
 * theta(n^lg(8))
 * 2012-12-5 19:35:31.
 *
 * matrix multiplication strassen's algorithm which is really miraculous
 * "The key to Strassen¡¯s method is to make the recursion tree slightly less bushy." - CLRS.v3.pg79
 * theta(n^lg(7))
 * 2012-12-6 12:25:52
 *
 * vector and view concept
 * 2012-12-6 15:27:43
 *
 * integrated this matrix implementation into "algo" lib
 * mail address: liyinglance@gmail.com and liying.hku@gmail.com
 * 2015-1-8 22:54:03
 *
**/

#include "matrix.h"

int init_matrix(matrix_t *matrix, int name, int m, int n, double *values){
  int i, j;
  int k, kmax = m*n;

  matrix->name = name;
  matrix->m = m;
  matrix->n = n;
  matrix->amendcount = 0;
  matrix->e = (element_t *)malloc(kmax * sizeof(element_t));

  for (k = 0, i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      matrix->e[k].name = name;
      matrix->e[k].i = i; matrix->e[k].r = i+1;
      matrix->e[k].j = j; matrix->e[k].c = j+1;
      matrix->e[k].amendcount = 0;
      if (values != NULL) matrix->e[k].value = values[k];
      else matrix->e[k].value = 0.0;
      k++;
    }//interloop
  }//outerloop

  return 0;
}//init_matrix

void free_matrix(matrix_t *matrix){
  matrix->name = 0;
  matrix->m = matrix->n = 0;
  free(matrix->e);
}//free_matrix

int display_matrix(matrix_t *matrix){
  int i, j;
  int k;

  printf("%d*%d matrix: %c [%02d]\n", matrix->m, matrix->n, matrix->name, matrix->amendcount);
  for (k = 0, i = 0; i < matrix->m; i++) {
    for (j = 0; j < matrix->n; j++) {
      printf("[%d.%d]", matrix->e[k].r, matrix->e[k].c);
      printf("[%04.1f][%d]\t", matrix->e[k].value, matrix->e[k].amendcount);
      k++;
    }//interloop
    printf("\n");
  }//outerloop

}//display_matrix

double get_elem(matrix_t *matrix, int r, int c){
  // todo: range check and optimize the search below by computing
  int k, kmax = matrix->m * matrix->n;
  for (k = 0; k < kmax; k++)
    if (matrix->e[k].r == r && matrix->e[k].c == c)
      break;
  return matrix->e[k].value;
}//get_elem

void set_elem(matrix_t *matrix, int r, int c, double value){
  int k, kmax = matrix->m * matrix->n;
  for (k = 0; k < kmax; k++)
    if (matrix->e[k].r == r && matrix->e[k].c == c)
      break;
  matrix->e[k].value = value;
  matrix->e[k].amendcount++;
  matrix->amendcount++;
}//set_elem

matrix_t matrix_add(matrix_t *ma, matrix_t *mb, int mresult){
  matrix_t mr;
  if (ma->m != mb->m){
    mr.name = -1;
    return mr;
  }
  if (ma->n != mb->n){
    mr.name = -2;
    return mr;
  }
  init_matrix(&mr, mresult, ma->m, ma->n, NULL);
  int r, c;
  for (r = 1; r <= mr.m; r++) {
  for (c = 1; c <= mr.n; c++) {
      set_elem(&mr, r, c, get_elem(ma,r,c) + get_elem(mb,r,c));
  }
  }
  return mr;
}//matrix_add

matrix_t matrix_sub(matrix_t *ma, matrix_t *mb, int mresult){
  matrix_t mr;
  if (ma->m != mb->m){
    mr.name = -1;
    return mr;
  }
  if (ma->n != mb->n){
    mr.name = -2;
    return mr;
  }
  init_matrix(&mr, mresult, ma->m, ma->n, NULL);
  int r, c;
  for (r = 1; r <= mr.m; r++) {
  for (c = 1; c <= mr.n; c++) {
      set_elem(&mr, r, c, get_elem(ma,r,c) - get_elem(mb,r,c));
  }
  }
  return mr;
}//matrix_sub

matrix_t matrix_scale(matrix_t *ma, int scale, int mresult){
  matrix_t mr;

  init_matrix(&mr, mresult, ma->m, ma->n, NULL);
  int r, c;
  for (r = 1; r <= mr.m; r++) {
  for (c = 1; c <= mr.n; c++) {
      set_elem(&mr, r, c, get_elem(ma,r,c)*scale);
  }
  }
  return mr;
}//matrix_scale

matrix_t get_submatrix(matrix_t *matrix, int r, int c, int m, int n)
{
  int i,j;
  matrix_t msub;
  init_matrix(&msub, 0, m, n, NULL);

  for (i = 0; i < m; i++)
  for (j = 0; j < n; j++)
    set_elem(&msub, 1+i, 1+j, get_elem(matrix, r+i, c+j));

  return msub;
}//get_submatrix

void set_submatrix(matrix_t *matrix, int r, int c, matrix_t *value)
{
  int i,j;
  for (i = 0; i < value->m; i++)
  for (j = 0; j < value->n; j++)
    set_elem(matrix, r+i, c+j, get_elem(value, 1+i, 1+j));
}//set_submatrix

matrix_t matrix_transpose(matrix_t *m, int mresult){
  matrix_t mr;

  init_matrix(&mr, mresult, m->n, m->m, NULL);

  int r, c;

  for (r = 1; r <= m->m; r++) {
  for (c = 1; c <= m->n; c++) {
    set_elem(&mr, c, r, get_elem(m, r, c));
    display_matrix(&mr);
  }
  }

  return mr;
}//matrix_transpose

matrix_t matrix_mul(matrix_t *ma, matrix_t *mb, int mresult){

  matrix_t mr;

  if (ma->n != mb->m){
    mr.name = -1;
    return mr;
  }
  init_matrix(&mr, mresult, ma->m, mb->n, NULL);

  int r, c, k, kmax = ma->n;
  for (r = 1; r <= mr.m; r++)
    for (c = 1; c <= mr.n; c++) {
      double sum = 0.0;
      for (k = 1; k <= kmax; k++) {
        sum += get_elem(ma, r, k)*get_elem(mb, k, c);
//      printf("(%d %d %d) : %5.2f\n", r, c, k, sum);
      }
      set_elem(&mr, r, c, sum);
//    display_matrix(&mr);
    }

  return mr;
}//matrix_mul

matrix_t matrix_mul_ijk(matrix_t *ma, matrix_t *mb, int mresult){

  matrix_t mr;

  if (ma->n != mb->m){
    mr.name = -1;
    return mr;
  }
  init_matrix(&mr, mresult, ma->m, mb->n, NULL);

  int r, c, k, kmax = ma->n;

  for (r = 1; r <= mr.m; r++) {
  for (c = 1; c <= mr.n; c++) {
  for (k = 1; k <= kmax; k++) {
      int pair_product = get_elem(ma, r, k)*get_elem(mb, k, c);
      set_elem(&mr, r, c, pair_product + get_elem(&mr, r, c));
      display_matrix(&mr);
  }
  }
  }

  return mr;
}//matrix_mul_ijk

matrix_t matrix_mul_jik(matrix_t *ma, matrix_t *mb, int mresult){

  matrix_t mr;

  if (ma->n != mb->m){
    mr.name = -1;
    return mr;
  }
  init_matrix(&mr, mresult, ma->m, mb->n, NULL);

  int r, c, k, kmax = ma->n;

  for (c = 1; c <= mr.n; c++) {
  for (r = 1; r <= mr.m; r++) {
  for (k = 1; k <= kmax; k++) {
      int pair_product = get_elem(ma, r, k)*get_elem(mb, k, c);
      set_elem(&mr, r, c, pair_product + get_elem(&mr, r, c));
      display_matrix(&mr);
  }
  }
  }

  return mr;
}//matrix_mul_jik

matrix_t matrix_mul_jki(matrix_t *ma, matrix_t *mb, int mresult){

  matrix_t mr;

  if (ma->n != mb->m){
    mr.name = -1;
    return mr;
  }
  init_matrix(&mr, mresult, ma->m, mb->n, NULL);

  int r, c, k, kmax = ma->n;


  for (c = 1; c <= mr.n; c++) {
  for (k = 1; k <= kmax; k++) {
  for (r = 1; r <= mr.m; r++) {
      int pair_product = get_elem(ma, r, k)*get_elem(mb, k, c);
      set_elem(&mr, r, c, pair_product + get_elem(&mr, r, c));
      display_matrix(&mr);
  }
  }
  }

  return mr;
}//matrix_mul_jki

matrix_t matrix_mul_kji(matrix_t *ma, matrix_t *mb, int mresult){

  matrix_t mr;

  if (ma->n != mb->m){
    mr.name = -1;
    return mr;
  }
  init_matrix(&mr, mresult, ma->m, mb->n, NULL);

  int r, c, k, kmax = ma->n;

  for (k = 1; k <= kmax; k++) {
  for (c = 1; c <= mr.n; c++) {
  for (r = 1; r <= mr.m; r++) {
    int pair_product = get_elem(ma, r, k)*get_elem(mb, k, c);
    set_elem(&mr, r, c, pair_product + get_elem(&mr, r, c));
    display_matrix(&mr);
  }
  }
  }

  return mr;
}//matrix_mul_kji

matrix_t matrix_mul_ikj(matrix_t *ma, matrix_t *mb, int mresult){

  matrix_t mr;

  if (ma->n != mb->m){
    mr.name = -1;
    return mr;
  }
  init_matrix(&mr, mresult, ma->m, mb->n, NULL);

  int r, c, k, kmax = ma->n;


  for (r = 1; r <= mr.m; r++) {
  for (k = 1; k <= kmax; k++) {
  for (c = 1; c <= mr.n; c++) {
      int pair_product = get_elem(ma, r, k)*get_elem(mb, k, c);
      set_elem(&mr, r, c, pair_product + get_elem(&mr, r, c));
      display_matrix(&mr);
  }
  }
  }

  return mr;
}//matrix_mul_ikj

matrix_t matrix_mul_kij(matrix_t *ma, matrix_t *mb, int mresult){

  matrix_t mr;

  if (ma->n != mb->m){
    mr.name = -1;
    return mr;
  }
  init_matrix(&mr, mresult, ma->m, mb->n, NULL);

  int r, c, k, kmax = ma->n;

  for (k = 1; k <= kmax; k++) {
  for (r = 1; r <= mr.m; r++) {
  for (c = 1; c <= mr.n; c++) {
    int pair_product = get_elem(ma, r, k)*get_elem(mb, k, c);
    set_elem(&mr, r, c, pair_product + get_elem(&mr, r, c));
    display_matrix(&mr);
  }
  }
  }

  return mr;
}//matrix_mul_kij

matrix_t square_matrix_mul_strassen(matrix_t *ma, matrix_t *mb, int mresult){

  matrix_t mr;

  if (ma->m != ma->n){
    mr.name = -1;
    return mr;
  }
  if (mb->m != mb->n){
    mr.name = -2;
    return mr;
  }
  if (ma->n != mb->m){
    mr.name = -3;
    return mr;
  }

  matrix_t *mc = &mr;

  init_matrix(mc, mresult, ma->m, mb->n, NULL);

  int i, j, k, n = ma->m;

  /**
   *
   * Straight Solution
   *
  **/

  if (n == 1) {
    set_elem(mc, 1, 1, get_elem(ma,1,1)*get_elem(mb,1,1));
    return mr;
  }


  /**
   *
   * Step1: Divide the input matrices A and B and output matrix C into (n/2)*(n/2) submatrices.
   *
  **/
  int N = n/2;
  matrix_t A[2][2], B[2][2], C[2][2];

  for (i = 0; i < 2; i++)
  for (j = 0; j < 2; j++)
  {
    A[i][j] = get_submatrix(ma, 1+N*i, 1+N*j, N, N);
    B[i][j] = get_submatrix(mb, 1+N*i, 1+N*j, N, N);
    C[i][j] = get_submatrix(mc, 1+N*i, 1+N*j, N, N);
  }

  /**
   *
   * Step2: Create 10 matrices S1,S2,...,S10, each of which is (n/2)*(n/2)
   *        and is the sum or difference of two matrices created in step 1.
   *
  **/
  matrix_t S[10];
  S[0] = matrix_sub(&B[1-1][2-1], &B[2-1][2-1], mresult);
  S[1] = matrix_add(&A[1-1][1-1], &A[1-1][2-1], mresult);
  S[2] = matrix_add(&A[2-1][1-1], &A[2-1][2-1], mresult);
  S[3] = matrix_sub(&B[2-1][1-1], &B[1-1][1-1], mresult);
  S[4] = matrix_add(&A[1-1][1-1], &A[2-1][2-1], mresult);
  S[5] = matrix_add(&B[1-1][1-1], &B[2-1][2-1], mresult);
  S[6] = matrix_sub(&A[1-1][2-1], &A[2-1][2-1], mresult);
  S[7] = matrix_add(&B[2-1][1-1], &B[2-1][2-1], mresult);
  S[8] = matrix_sub(&A[1-1][1-1], &A[2-1][1-1], mresult);
  S[9] = matrix_add(&B[1-1][1-1], &B[1-1][2-1], mresult);

  /**
   *
   * Step3: Using the submatrices created in step 1 and the 10 matrices created in step 2,
   *        recursively compute seven matrix products P1,P2,...,P7. Each matrix Pi is (n/2)*(n/2).
   *
   *
  **/
  matrix_t P[7];
  P[1-1] = square_matrix_mul_strassen(&A[1-1][1-1], &S[1-1], mresult);
  P[2-1] = square_matrix_mul_strassen(&S[2-1], &B[2-1][2-1], mresult);
  P[3-1] = square_matrix_mul_strassen(&S[3-1], &B[1-1][1-1], mresult);
  P[4-1] = square_matrix_mul_strassen(&A[2-1][2-1], &S[4-1], mresult);
  P[5-1] = square_matrix_mul_strassen(&S[5-1], &S[6-1], mresult);
  P[6-1] = square_matrix_mul_strassen(&S[7-1], &S[8-1], mresult);
  P[7-1] = square_matrix_mul_strassen(&S[9-1], &S[10-1], mresult);

  /**
   *
   * Step4: Compute the desired submatrices C11;C12;C21;C22 of the result matrix C by
   *        adding and subtracting various combinations of the Pi matrices.
   *
   *
  **/
  matrix_t temp, temp1, temp2, temp3;

  temp = matrix_add(&P[5-1],&P[4-1], mresult);
  temp = matrix_sub(&temp,&P[2-1], mresult);
  C[1-1][1-1] = matrix_add(&temp,&P[6-1], mresult);

  C[1-1][2-1] = matrix_add(&P[1-1],&P[2-1], mresult);
  C[2-1][1-1] = matrix_add(&P[3-1],&P[4-1], mresult);

  temp = matrix_add(&P[5-1],&P[1-1], mresult);
  temp = matrix_sub(&temp,&P[3-1], mresult);
  C[2-1][2-1] = matrix_sub(&temp,&P[7-1], mresult);

  //Combine
  for (i = 0; i < 2; i++)
  for (j = 0; j < 2; j++)
  {
    set_submatrix(mc, 1+N*i, 1+N*j, &C[i][j]);
  }

  return mr;

}//square_matrix_mul_strassen

matrix_t square_matrix_mul_recursive(matrix_t *ma, matrix_t *mb, int mresult){

  matrix_t mr;

  if (ma->m != ma->n){
    mr.name = -1;
    return mr;
  }
  if (mb->m != mb->n){
    mr.name = -2;
    return mr;
  }
  if (ma->n != mb->m){
    mr.name = -3;
    return mr;
  }

  matrix_t *mc = &mr;

  init_matrix(mc, mresult, ma->m, mb->n, NULL);

  int i, j, k, n = ma->m;

  if (n == 1) {
    set_elem(mc, 1, 1, get_elem(ma,1,1)*get_elem(mb,1,1));
    return mr;
  }


  //Divide
  int N = n/2;
  matrix_t A[2][2], B[2][2], C[2][2];

  for (i = 0; i < 2; i++)
  for (j = 0; j < 2; j++)
  {
    A[i][j] = get_submatrix(ma, 1+N*i, 1+N*j, N, N);
    B[i][j] = get_submatrix(mb, 1+N*i, 1+N*j, N, N);
    C[i][j] = get_submatrix(mc, 1+N*i, 1+N*j, N, N);

//  display_matrix(&A[i][j]);
//  display_matrix(&B[i][j]);
//  display_matrix(&C[i][j]);
  }

  //Conquer
  for (i = 0; i < 2; i++)
  for (j = 0; j < 2; j++)
  for (k = 0; k < 2; k++)
  {
    matrix_t product = square_matrix_mul_recursive(&A[i][k], &B[k][j], mresult);
    C[i][j] = matrix_add(&C[i][j], &product, mresult);
  }

  //Combine
  for (i = 0; i < 2; i++)
  for (j = 0; j < 2; j++)
  {
    set_submatrix(mc, 1+N*i, 1+N*j, &C[i][j]);
//  display_matrix(&C[i][j]);
//  display_matrix(mc);
  }

  return mr;

}//square_matrix_mul_recursive


