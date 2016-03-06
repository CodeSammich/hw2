#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {

  screen s;
  struct matrix *edges;
  struct matrix *transform;

  edges = new_matrix(4, 4);
  transform = new_matrix(4, 4);

  printf("\n Original Edges \n " );
  print_matrix( edges );
  printf("\n Original Transform \n ");
  print_matrix( transform );

  printf( "\nIdentity Edges\n" );
  ident( edges );
  print_matrix( edges );
  printf( "\nScalar Multiply Edges by 5" );
  scalar_mult( 5, edges);
  print_matrix( edges );

  printf( "\n Ident Transform \n");
  ident( transform );
  print_matrix( transform );

  printf( "\nMatrix Multiply Edges and Transform\n" );
  matrix_mult( edges, transform );
  print_matrix( transform );
  
  free_matrix( transform );
  free_matrix( edges );
}  
