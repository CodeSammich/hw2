#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main() {

  screen s;
  struct matrix *edges;
  struct matrix *transform;
  struct matrix *rotate;
  struct matrix *scale;
  color c;

  c.red = 255;
  c.green = 0;
  c.blue = 0;
  clear_screen(s);

  edges = new_matrix(4, 4);
  transform = new_matrix(4, 4);
  
  ident( edges );
  ident( transform );

  copy_matrix( make_translate( 3 * XRES/4, YRES / 8, 0), transform); 
  //  print_matrix( transform );
  //draw square in lower left corner
  
  add_edge( edges, 0, 0, 0, 0, YRES / 4, 0 );
  add_edge( edges, XRES / 4, 0, 0, XRES / 4, YRES / 4, 0 );
  add_edge( edges, 0, 0, 0, XRES / 4, 0, 0 );
  add_edge( edges, 0, YRES / 4, 0, XRES / 4, YRES / 4, 0 );

  add_edge( edges, 0, 3 * YRES / 4, 0, 0, YRES, 0 );
  add_edge( edges, 0, 3 * YRES / 4, 0, XRES / 4, 3 * YRES / 4, 0 );
  add_edge( edges, XRES / 4, 3 * YRES / 4, 0, XRES / 4, YRES, 0 );
  add_edge( edges, XRES / 4, YRES, 0, 0, YRES, 0 );

  add_edge( edges, 0, 0, 0, XRES, YRES / 2, 0 );
  add_edge( edges, XRES, YRES / 2, 0, 0, YRES, 0 );
  add_edge( edges, 0, YRES, 0, 0, 0, 0 );

  add_edge( edges, 3 * XRES / 8, 3 * YRES / 4, 0, 3 * XRES / 8, 3 * YRES /8, 0);
  add_edge( edges, 5 * XRES / 8, 3 * YRES / 4, 0, 5 * XRES / 8, 3 * YRES /8, 0);

  add_edge( edges, 3 * XRES / 8, YRES / 4, 0, XRES / 2, 0, 0 );
  add_edge( edges, 5 * XRES / 8, YRES / 4, 0, XRES / 2, 0, 0 );
  add_edge( edges, 5 * XRES / 8, YRES / 4, 0, 3 * XRES / 8, YRES / 4, 0);
  
  draw_lines( edges, s, c );
  
  
  //  matrix_mult( edges, transform );
  //  print_matrix( edges );
  
  //  draw_lines( transform, s, c);
  //  print_matrix( transform );
  /*
  copy_matrix( make_translate( 0, YRES / 2, 0 ), transform );
  draw_lines( edges, s, c);
  
  matrix_mult( transform, edges );
  print_matrix( edges);

  //draw to screen
  draw_lines( edges, s, c );
  
  */
  
  //save to ppm
  save_ppm( s, "image.ppm" );
  display( s );
  
  free_matrix( transform );
  free_matrix( edges );

  display( s );
  /* ===================================== */
  
  /* matrices.c testing
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

  printf("\n Copy edges to transform\n" );
  copy_matrix( edges, transform );
  print_matrix( transform );
  
  printf( "\nMatrix Multiply Edges and Transform\n" );
  matrix_mult( edges, transform );
  print_matrix( transform );

  printf("\n Translation matrix with x: 1, y: 5, z: 7 \n");
  print_matrix( make_translate( 1, 5, 7 ) );

  //Degree input
  printf("\n Rotate X 90\n");
  print_matrix( make_rotX( 90 ));

  printf("\n Rotate Y 90\n");
  print_matrix( make_rotY( 90 ));
  
  printf("\n Rotate Z 90\n");
  print_matrix( make_rotZ( 90 ));

  printf("\n Scale Matrix by 8, 7, 3\n" );
  print_matrix( make_scale( 8, 7, 3 ));
  */


}  
