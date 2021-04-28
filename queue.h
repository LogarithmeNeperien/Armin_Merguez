#ifndef __QUEUE_H__
#define __QUEUE_H__
#include <stdbool.h>

struct point_info_t {
  unsigned int x, y ;
  unsigned char r, g, b ;
};


struct queue_t {
  unsigned int max_nb ;      /* Nombre max d'éléments. */
  unsigned int cur_nb ;      /* Nombre actuel d'éléments. */
  unsigned int first ;       /* Indice du premier élément. */
  struct point_info_t *data ;
};

struct queue_t *queue_alloc (unsigned int max_size) ;
void queue_free (struct queue_t *q) ;
struct point_info_t take (struct queue_t *q) ;
void enqueue (struct queue_t *q, struct point_info_t pi) ;
bool is_empty (struct queue_t *q) ;
#endif
