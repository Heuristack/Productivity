#ifndef matrix_h
#define matrix_h

#include "stdlib.h"

typedef struct {
  int name;
  int index;          // for vectors
  int r, i;
  int c, j;
  int amendcount;     //# pair-product-ball or say 'k'
  double value;
} element_t;

typedef struct {
  int name;
  int m;              //# rows
  int n;              //# cols
  int amendcount;     //# pair-product-ball in the scope of matrix
  element_t *e;
} matrix_t;

typedef struct {
  int name;
  int m;              // if m = 1 the vector is row vector
  int n;              // if n = 1 the vector is col vector
  int amendcount;
  element_t *e;
} vector_t;

typedef struct {
  int i, j;           // (i,j) index of the corner-point
  int r, c;           // left-most & up-most corner-point of the view
  int m, n;           // scale of the view in vertical and horizontal direction
  matrix_t *matrix;
} view_t;

int init_matrix(matrix_t *matrix, int name, int m, int n, double *values);
void free_matrix(matrix_t *matrix);

int display_matrix(matrix_t *matrix);

double get_elem(matrix_t *matrix, int r, int c);
void set_elem(matrix_t *matrix, int r, int c, double value);

matrix_t matrix_add(matrix_t *ma, matrix_t *mb, int mresult);
matrix_t matrix_sub(matrix_t *ma, matrix_t *mb, int mresult);
matrix_t matrix_scale(matrix_t *ma, int scale, int mresult);

matrix_t get_submatrix(matrix_t *matrix, int r, int c, int m, int n);
void set_submatrix(matrix_t *matrix, int r, int c, matrix_t *value);

matrix_t matrix_transpose(matrix_t *m, int mresult);
matrix_t matrix_mul(matrix_t *ma, matrix_t *mb, int mresult);

matrix_t matrix_mul_ijk(matrix_t *ma, matrix_t *mb, int mresult);
matrix_t matrix_mul_jik(matrix_t *ma, matrix_t *mb, int mresult);
matrix_t matrix_mul_jki(matrix_t *ma, matrix_t *mb, int mresult);
matrix_t matrix_mul_kji(matrix_t *ma, matrix_t *mb, int mresult);
matrix_t matrix_mul_ikj(matrix_t *ma, matrix_t *mb, int mresult);
matrix_t matrix_mul_kij(matrix_t *ma, matrix_t *mb, int mresult);

matrix_t square_matrix_mul_strassen(matrix_t *ma, matrix_t *mb, int mresult);
matrix_t square_matrix_mul_recursive(matrix_t *ma, matrix_t *mb, int mresult);

#endif //matrix_h
