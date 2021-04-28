#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"



/** \brief Création d'une structure de file de taille maximale fixe et fournie
    en argument.
    \param max_size : Nombre maximal d'éléments dans la pile. Si cette taille
    est nulle, la file n'est pas crée.
    \return Le pointeur sur la file vide ou NULL si l'allocation a échoué. */
struct queue_t* queue_alloc (unsigned int max_size)
{
  struct queue_t *q ;

  if (max_size == 0) return (NULL) ;
  q = malloc (sizeof (struct queue_t)) ;
  if (q == NULL) return (NULL) ;
  q->data = malloc (max_size * sizeof (struct point_info_t)) ;
  if (q->data == NULL) {
    free (q) ;
    return (NULL) ;
  }
  q->max_nb = max_size ;
  q->cur_nb = 0 ;
  q->first = 0 ;
  return (q) ;
}



/** \brief Libération de la mémoire utilisée par une file.
    \param q : Pointeur sur la file à libérer.
    \return : Néant. */
void queue_free (struct queue_t *q)
{
  if (q == NULL) return ;
  if (q->data != NULL) free (q->data) ;
  free (q) ;
}



/** \brief Extraction de l'élément en tête de file s'il existe.
    \param q : Pointeur sur la file de laquelle extraire un élément.
    \return L'information en tête de file. Cette information est supprimée
    de la file par l'extraction. Si la file est vide (ou le pointeur NULL),
    une erreur est signalée qui interrompt le programme abruptement. */
struct point_info_t take (struct queue_t *q)
{
  struct point_info_t res ;
  if ((q == NULL) || (q->cur_nb == 0)) {
    /* File vide. */
    printf ("Error: empty queue.\n") ;
    exit (-1) ;
  }
  res = q->data[q->first] ;
  q->first = (q->first + 1) % q->max_nb ;
  q->cur_nb-- ;
  return (res) ;
}



/** \brief Ajout d'un élément en queue de file si la file n'est pas pleine.
    \param q : Pointeur sur la file dans laquelle insérer l'information.
    \return : Néant. Toutefois, si la file est pleine (ou le pointeur NULL),
    une erreur est signalée qui interrompt le programme abruptement. */
void enqueue (struct queue_t *q, struct point_info_t pi)
{
  if ((q == NULL) || (q->cur_nb == q->max_nb)) {
    /* File pleine. */
    printf ("Error: full queue.\n") ;
    exit (-1) ;
  }
  q->data[(q->first + q->cur_nb) % q->max_nb] = pi ;
  q->cur_nb++ ;
}



/** \brief Test si la fil est vide.
    \param q : Pointeur sur la file à tester.
    \return Un booléen true si la file est vide ou si le pointeur de file
    est NULL. Un booléen false dans le cas contraire. */
bool is_empty (struct queue_t *q)
{
  return ((q == NULL) || (q->cur_nb == 0)) ;
}
