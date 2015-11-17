#include "matrix.h"

int main(int argc, char *argv[]){

    double mmvalues[] = {2.0,3.0,1.0,1.0,4.0,2.0,2.0,1.0,2.0,1.0,4.0,2.0,2.0,3.0,1.0,1.0,4.0,2.0,2.0,1.0,2.0,1.0,4.0,2.0,5.0,4.0,2.0,2.0,1.0,2.0,\
                         4.0,2.0,2.0,1.0,2.0,1.0,6.0,3.0,1.0,1.0,4.0,2.0,2.0,1.0,9.0,1.0,4.0,2.0,5.0,4.0,2.0,2.0,1.0,2.0,5.0,5.0,2.0,2.0,1.0,2.0};

    matrix_t mm, ma, mb, mc, md, mx, my, mz;
    init_matrix(&mm, 'm', 6, 6, mmvalues);
    init_matrix(&ma, 'a', 3, 3, NULL);
    init_matrix(&mb, 'b', 3, 3, NULL);
    init_matrix(&mc, 'c', 3, 3, NULL);

    display_matrix(&mm);
    display_matrix(&ma);
    display_matrix(&mb);
    display_matrix(&mc);

    free_matrix(&ma);
    ma = get_submatrix(&mm, 2, 1, 4, 4);
    display_matrix(&ma);

    free_matrix(&mb);
    mb = get_submatrix(&mm, 3, 2, 4, 4);
    display_matrix(&mb);

    mx = matrix_mul(&ma, &mb, 'X');
    my = square_matrix_mul_recursive(&ma, &mb, 'Y');
    mz = square_matrix_mul_strassen(&ma, &mb, 'Z');

    printf("the result is \n");

    display_matrix(&mx);
    display_matrix(&my);
    display_matrix(&mz);

    ma = get_submatrix(&mm, 1, 2, 6, 1);
    mb = get_submatrix(&mm, 2, 1, 1, 6);

    display_matrix(&ma);
    display_matrix(&mb);

    mc = matrix_mul(&mb, &ma, '1');
    display_matrix(&mc);

    md = matrix_mul(&ma, &mb, 'S');
    display_matrix(&md);

    free_matrix(&mc);
    mc = matrix_scale(&md, 2, '2');
    display_matrix(&mc);

    free_matrix(&ma);
    free_matrix(&mb);
    free_matrix(&mc);
    free_matrix(&md);
    free_matrix(&mx);
    free_matrix(&my);
    free_matrix(&mz);

    return 0;
}//main
