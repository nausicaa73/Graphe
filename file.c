#include <stdlib.h>

#include "file.h"

pfile_t creer_file()
{
  pfile_t res = malloc(sizeof(file_t));
  res->tete = 0;
  res->queue = 0;
  return res;
}

int detruire_file(pfile_t f)
{
  if (f == NULL)
    return 0;
  free(f);
  return 1;
}

int file_vide(pfile_t f)
{
  return f->tete == f->queue;
}

int file_pleine(pfile_t f)
{
  return (f->queue == MAX_FILE_SIZE - 1 && f->tete <= 1) || (f->tete - f->queue == 1);
}

psommet_t defiler(pfile_t f)
{
  if (file_vide(f))
    return NULL;
  psommet_t res = f->Tab[f->tete];

  if (f->tete == MAX_FILE_SIZE - 1)
  {
    f->tete = 0;
  }
  else
  {
    f->tete++;
  }
  return res;
}

int enfiler(pfile_t f, psommet_t p)
{
  if (file_pleine(f))
    return 0;
  f->Tab[f->queue] = p;
  if (f->queue == MAX_FILE_SIZE - 1)
  {
    f->queue = 0;
  }
  else
  {
    f->queue++;
  }
  return 1;
}
