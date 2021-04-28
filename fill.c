#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "paint.h"


void fill (int width, int height, int nb_init,unsigned char* pixels)
{
  int i ;
  bool *processed ;
  struct queue_t *q ;
  struct point_info_t *init_points ;

  /* Allocation de la file. Taille max: width * height. */
  q = queue_alloc (width * height) ;
  if (q == NULL) {
    printf ("No mem for queue.\n") ;
    return ;
  }

  /* Allocation du tableau pour se souvenir des points initiaux et redessiner
     par dessus en noir � la fin. */
  init_points = malloc (nb_init * sizeof (struct point_info_t)) ;
  if (init_points == NULL) {
    printf ("Nom mem for initial points.\n") ;
    queue_free (q) ;
    return ;
  }

  /* Allocation du tableau disant si un point a d�j� �t� mis en file. */
  processed = malloc (width * height * sizeof (bool)) ;
  if (processed == NULL) {
    printf ("No mem for processed array.\n") ;
    free (init_points) ;
    queue_free (q) ;
    return ;
  }
  /* Au d�but, aucun point n'a d�j� �t� trait�. */
  for (i = 0; i < width * height; i++) processed[i] = false ;


/* ----------------------------------------------------------------------------
                        DEBUT DE L'ALGORITHME ICI
   ----------------------------------------------------------------------------*/

  /* Initiation des nb_init points et de leur couleurs respectives */
  
  for (int i = 0; i < nb_init; ++i)
  {
      //Attribution d'une position
      init_points[i].x = rand()%width; 
      init_points[i].y = rand()%height;
    
      //Attribution d'une couleur
      init_points[i].r = rand()%256; 
      init_points[i].g = rand()%256; 
      init_points[i].b = rand()%256;
    
      //On envoie ces messieurs dans la file
      enqueue(q,init_points[i]);
      
      //et l'on n'oublie pas de pr�venir qu'ils sont trait�s !
      processed[init_points[i].y*width+init_points[i].x]=true;
  }

  /* Processus de remplissage */

  while(q->cur_nb != 0) 
  { 

      //on prend le nombre de points courants
      int in_queue = q->cur_nb;
      //printf("A cette �tape, on a %d points dans la file \n",in_queue);

      for (int i = 0; i < in_queue;++i)
      { 
          //on traite les points en les sortant de la file
          struct point_info_t head = take(q);
          /* Pas de probl�me d'allocation car on a d�j� test� si q �tait vide*/

          color_pixel(head.x,head.y,head.r,head.g,head.b,width,height,pixels);
          
          //puis dans les 4 directions autour
          for (int j = 0; j < 4;++j)
          { 
              int new_x = head.x+1*(j==0)-1*(j==2);
              int new_y = head.y+1*(j==1)-1*(j==3);
              
              //si on ne sort pas, ou qu'on a pas d�j� trait� ce point
              if (!(new_x >= width || new_x < 0 || new_y >= height || new_y < 0 ||
               processed[new_y*width+new_x] == true)) 
              {
                //on ajoute ses voisins � la file
                struct point_info_t voisin = {new_x,new_y,head.r,head.g,head.b};
                enqueue(q,voisin);
                processed[new_y*width+new_x] = true;
              }
          }

      }

  }

/* EXPLICATION de l'algorithme
A chaque tour de boucle, on colorie puis l'on retire les points pr�sents dans la file en y ajoutant leurs 4 voisins 
si ces derniers ne sont pas d�j� colori�s ou ne sortent pas du cadre. S'il ne reste plus de points � ajouter, le programme
continue de colorier un par un les points restants jusqu'� ce que q soit vide.
*/

  queue_free (q) ;
  free (processed) ;

  for (i = 0; i < nb_init; i++)
    color_pixel(init_points[i].x, init_points[i].y,
                 init_points[i].r, init_points[i].g, init_points[i].b, width, height, pixels);
    
  free (init_points) ;
}
