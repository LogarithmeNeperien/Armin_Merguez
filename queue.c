#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"



/** \brief Cr�ation d'une structure de file de taille maximale fixe et fournie
    en argument.
    \param max_size : Nombre maximal d'�l�ments dans la pile. Si cette taille
    est nulle, la file n'est pas cr�e.
    \return Le pointeur sur la file vide ou NULL si l'allocation a �chou�. */
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



/** \brief Lib�ration de la m�moire utilis�e par une file.
    \param q : Pointeur sur la file � lib�rer.
    \return : N�ant. */
void queue_free (struct queue_t *q)
{
  if (q == NULL) return ;
  if (q->data != NULL) free (q->data) ;
  free (q) ;
}



/** \brief Extraction de l'�l�ment en t�te de file s'il existe.
    \param q : Pointeur sur la file de laquelle extraire un �l�ment.
    \return L'information en t�te de file. Cette information est supprim�e
    de la file par l'extraction. Si la file est vide (ou le pointeur NULL),
    une erreur est signal�e qui interrompt le programme abruptement. */
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



/** \brief Ajout d'un �l�ment en queue de file si la file n'est pas pleine.
    \param q : Pointeur sur la file dans laquelle ins�rer l'information.
    \return : N�ant. Toutefois, si la file est pleine (ou le pointeur NULL),
    une erreur est signal�e qui interrompt le programme abruptement. */
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
    \param q : Pointeur sur la file � tester.
    \return Un bool�en true si la file est vide ou si le pointeur de file
    est NULL. Un bool�en false dans le cas contraire. */
bool is_empty (struct queue_t *q)
{
  return ((q == NULL) || (q->cur_nb == 0)) ;
}
