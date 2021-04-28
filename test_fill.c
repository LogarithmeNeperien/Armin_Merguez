#include <unistd.h>    /* Pour getpid. */
#include "fill.h"
#include "paint.h"
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (600)


int main (int argc, char *argv[])
{

  if (argc != 2) {
    printf ("Wrong argument. Expected <nb initial points>.\n") ;
    return (-1) ;
  }

  
  unsigned char* window=create_pixels(SCREEN_WIDTH,SCREEN_HEIGHT);

  srand (getpid ()) ;

  /* Calcul du remplissage. */
  fill (SCREEN_WIDTH, SCREEN_HEIGHT, atoi (argv[1]),window) ;

  save_BMP("dessin.bmp", SCREEN_WIDTH,SCREEN_HEIGHT,window);


  return (0) ;
}
