#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"

/*-------------- struct matrix *new_matrix() --------------
Inputs:  int rows
         int cols 
Returns: 

Once allocated, access the matrix as follows:
m->m[r][c]=something;
if (m->lastcol)... 
*/
struct matrix *new_matrix(int rows, int cols) {
  double **tmp;
  int i;
  struct matrix *m;

  tmp = (double **)malloc(rows * sizeof(double *));
  for (i=0;i<rows;i++) {
      tmp[i]=(double *)malloc(cols * sizeof(double));
    }

  m=(struct matrix *)malloc(sizeof(struct matrix));
  m->m=tmp;
  m->rows = rows;
  m->cols = cols;
  m->lastcol = 0;

  return m;
}


/*-------------- void free_matrix() --------------
Inputs:  struct matrix *m 
Returns: 

1. free individual rows
2. free array holding row pointers
3. free actual matrix
*/
void free_matrix(struct matrix *m) {

  int i;
  for (i=0;i<m->rows;i++) {
      free(m->m[i]);
    }
  free(m->m);
  free(m);
}


/*======== void grow_matrix() ==========
Inputs:  struct matrix *m
         int newcols 
Returns: 

Reallocates the memory for m->m such that it now has
newcols number of collumns
====================*/
void grow_matrix(struct matrix *m, int newcols) {
  
  int i;
  for (i=0;i<m->rows;i++) {
      m->m[i] = realloc(m->m[i],newcols*sizeof(double));
  }
  m->cols = newcols;
}


/*-------------- void print_matrix() --------------
Inputs:  struct matrix *m 
Returns: 

print the matrix
*/
void print_matrix(struct matrix *m) {
  int i = 0;
  int j = 0;
  printf( "\n[ ");
  for(; i < m -> rows; i++ ) {
    for(j = 0; j < m -> cols; j++)
      printf( " %f ", m -> m[i][j] );
    printf( "\n" );
  }
  printf( " ]\n" );
}

/*-------------- void ident() --------------
Inputs:  struct matrix *m <-- assumes m is a square matrix
Returns: 

turns m in to an identity matrix
*/
void ident(struct matrix *m) {
  int i = 0;
  int j = 0;
  for(; i < (m -> rows); i++ ) {
    for(j = 0; j < (m -> cols); j++) {
      if( i == j)
	m -> m[i][j] = 1;
      else
	m -> m[i][j] = 0;
    }
  }
}


/*-------------- void scalar_mult() --------------
Inputs:  double x
         struct matrix *m 
Returns: 

multiply each element of m by x
*/
void scalar_mult(double x, struct matrix *m) {
  int i = 0;
  int j = 0;
  double original_value;
  for(; i < (m -> rows); i++ ) {
    for(j = 0; j < (m -> cols); j++) {
      original_value = m -> m[i][j];
      m -> m[i][j] = original_value * x;
    }
  }
}


/*-------------- void matrix_mult() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

a*b -> b
*/
void matrix_mult(struct matrix *a, struct matrix *b) {
  struct matrix* temp;
  temp = new_matrix( a -> rows, b -> cols );
  int a_cols = 0;
  int b_rows = 0;
  int current_row = 0;
  int current_col = 0;
  double value = 0;
  
  for(; current_row < a -> rows; current_row++) {
    //    print_matrix(temp);
    
    for(current_col = 0; current_col < b -> cols; current_col++){
      
      while( a_cols < a -> cols && b_rows < b -> rows) {
	value += a -> m[current_row][a_cols] * b -> m[b_rows][current_col];
	//	printf( "value: %f, added value: %f, a_cols: %d, b_rows %d, current_row: %d, current_col: %d\n", value, a -> m[current_row][a_cols] * b -> m[b_rows][current_col], a_cols, b_rows, current_row, current_col );
	a_cols++;
	b_rows++;
      }
      
      temp -> m[current_row][current_col] = value;
      //      print_matrix( temp );
      value = 0;
      a_cols = 0;
      b_rows = 0;
    }
    
    // current_row++;
  }
  //  print_matrix( temp );
  copy_matrix( temp, b);
}


/*-------------- void copy_matrix() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

copy matrix a to matrix b
*/
void copy_matrix(struct matrix *a, struct matrix *b) {

  int r, c;

  for (r=0; r < a->rows; r++) 
    for (c=0; c < a->cols; c++)  
      b->m[r][c] = a->m[r][c];  
}

/*======== struct matrix * make_translate() ==========
Inputs:  int x
         int y
         int z 
Returns: The translation matrix created using x, y and z 
as the translation offsets.
====================*/
struct matrix * make_translate(double x, double y, double z) {
  struct matrix * temp = new_matrix( 4, 4 );
  ident( temp );
  //  print_matrix( temp );
  
  temp -> m[0][3] = x;
  temp -> m[1][3] = y;
  temp -> m[2][3] = z;

  return temp;
}

/*======== struct matrix * make_scale() ==========
Inputs:  int x
         int y
         int z 
Returns: The translation matrix creates using x, y and z
as the scale factors
====================*/
struct matrix * make_scale(double x, double y, double z) {
  struct matrix * temp = new_matrix( 4, 4);
  ident( temp );

  temp -> m[0][0] = x;
  temp -> m[1][1] = y;
  temp -> m[2][2] = z;

  return temp;
}

/*======== struct matrix * make_rotX() ==========
Inputs:  double theta, assume degree input

Returns: The rotation matrix created using theta as the 
angle of rotation and X as the axis of rotation.
====================*/
struct matrix * make_rotX(double theta) {
  //Convert degree theta to radians
  theta = theta * M_PI / 180;
  
  struct matrix * temp = new_matrix( 4, 4);
  ident( temp );

  temp -> m[1][1] = cos( theta );
  temp -> m[1][2] = -1 * cos( theta );
  temp -> m[2][1] = sin( theta );
  temp -> m[2][2] = cos( theta );

  return temp;
}

/*======== struct matrix * make_rotY() ==========
Inputs:  double theta, assume degree input

Returns: The rotation matrix created using theta as the 
angle of rotation and Y as the axis of rotation.
====================*/
struct matrix * make_rotY(double theta) {
  //Convert degree theta to radians
  theta = theta * M_PI / 180;
  
  struct matrix * temp = new_matrix( 4, 4);
  ident( temp );

  temp -> m[0][0] = cos( theta );
  temp -> m[0][2] = -1 * sin( theta );
  temp -> m[2][0] = sin( theta );
  temp -> m[2][2] = cos( theta );

  return temp;
}

/*======== struct matrix * make_rotZ() ==========
Inputs:  double theta, assume degree input

Returns: The rotation matrix created using theta as the 
angle of rotation and Z as the axis of rotation.
====================*/
struct matrix * make_rotZ(double theta) {
  //Convert degree theta to radians
  theta = theta * M_PI / 180;
  
  struct matrix * temp = new_matrix( 4, 4);
  ident( temp );

  temp -> m[0][0] = cos(theta);
  temp -> m[0][1] = -1 * sin( theta );
  temp -> m[1][0] = sin( theta );
  temp -> m[1][1] = cos( theta );

  return temp;
}
