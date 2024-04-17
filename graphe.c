/*
  Structures de type graphe
  Structures de donnees de type liste
  (Pas de contrainte sur le nombre de noeuds des  graphes)
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "file.h"

psommet_t chercher_sommet(pgraphe_t g, int label)
{
  psommet_t s;

  s = g;

  while ((s != NULL) && (s->label != label))
  {
    s = s->sommet_suivant;
  }
  return s;
}

parc_t existence_arc(parc_t l, psommet_t s)
{
  parc_t p = l;

  while (p != NULL)
  {
    if (p->dest == s)
      return p;
    p = p->arc_suivant;
  }
  return p;
}

void ajouter_arc(psommet_t o, psommet_t d, int distance)
{
  parc_t parc;

  parc = (parc_t)malloc(sizeof(arc_t));

  if (existence_arc(o->liste_arcs, d) != NULL)
  {
    fprintf(stderr, "ajout d'un arc deja existant\n");
    exit(-1);
  }

  parc->poids = distance;
  parc->dest = d;
  parc->arc_suivant = o->liste_arcs;
  o->liste_arcs = parc;
  return;
}

// ===================================================================

int nombre_sommets(pgraphe_t g)
{
  psommet_t p = g;
  int nb = 0;

  while (p != NULL)
  {
    nb = nb + 1;
    p = p->sommet_suivant;
  }

  return nb;
}

int nombre_arcs(pgraphe_t g)
{

  psommet_t p = g;
  int nb_arcs = 0;

  while (p != NULL)
  {
    parc_t l = p->liste_arcs;

    while (l != NULL)
    {
      nb_arcs = nb_arcs + 1;
      l = l->arc_suivant;
    }

    p = p->sommet_suivant;
  }
  return nb_arcs;
}

void init_distance_sommet(pgraphe_t g)
{
  psommet_t p = g;

  while (p != NULL)
  {
    p->distance = INT_MAX; // couleur indefinie
    p = p->sommet_suivant; // passer au sommet suivant dans le graphe
  }

  return;
}
void init_couleur_sommet(pgraphe_t g)
{
  psommet_t p = g;

  while (p != NULL)
  {
    p->couleur = 0;        // couleur indefinie
    p = p->sommet_suivant; // passer au sommet suivant dans le graphe
  }

  return;
}

int colorier_graphe(pgraphe_t g)
{
  /*
    coloriage du graphe g

    datasets
    graphe data/gr_planning
    graphe data/gr_sched1
    graphe data/gr_sched2
  */

  psommet_t p = g;
  parc_t a;
  int couleur;
  int max_couleur = INT_MIN; // -INFINI

  int change;

  init_couleur_sommet(g);

  while (p != NULL)
  {
    couleur = 1; // 1 est la premiere couleur

    // Pour chaque sommet, on essaie de lui affecter la plus petite couleur

    // Choix de la couleur pour le sommet p

    do
    {
      a = p->liste_arcs;
      change = 0;

      while (a != NULL)
      {
        if (a->dest->couleur == couleur)
        {
          couleur = couleur + 1;
          change = 1;
        }
        a = a->arc_suivant;
      }

    } while (change == 1);

    // couleur du sommet est differente des couleurs de tous les voisins

    p->couleur = couleur;
    if (couleur > max_couleur)
      max_couleur = couleur;

    p = p->sommet_suivant;
  }

  return max_couleur;
}

void afficher_graphe_largeur(pgraphe_t g, int r)
{
  pfile_t f = creer_file();
  psommet_t p;
  parc_t a;
  init_couleur_sommet(g);
  enfiler(f, chercher_sommet(g, r));
  while (!file_vide(f))
  {
    p = defiler(f);
    p->couleur = 1;
    printf("sommet %d \n", p->label);
    a = p->liste_arcs;
    while (a != NULL)
    {
      if (a->dest->couleur == 0)
      {
        a->dest->couleur = 1;
        enfiler(f, a->dest);
      }
      a = a->arc_suivant;
    }
  }
  detruire_file(f);
}


void rec(pgraphe_t g)
{
  g->couleur = 1;
  parc_t a = g->liste_arcs;
  printf("sommet %d \n", g->label);
  while (a != NULL)
  {
    if (a->dest->couleur == 0)
    {
      rec(a->dest);
    }
    a = a->arc_suivant;
  }
}

void afficher_graphe_profondeur(pgraphe_t g, int r)
{
  init_couleur_sommet(g);
  psommet_t p = chercher_sommet(g, r);
  rec(p);
}
void affiche_poids(pgraphe_t g, int r)
{
  pfile_t f = creer_file();
  psommet_t p;
  parc_t a;
  init_couleur_sommet(g);
  enfiler(f, chercher_sommet(g, r));
  while (!file_vide(f))
  {
    p = defiler(f);
    p->couleur = 1;
    printf("sommet %d, distance %d \n", p->label, p->distance);
    a = p->liste_arcs;
    while (a != NULL)
    {
      if (a->dest->couleur == 0)
      {
        a->dest->couleur = 1;
        enfiler(f, a->dest);
      }
      a = a->arc_suivant;
    }
  }
  detruire_file(f);
}
void algo_dijkstra(pgraphe_t g, int r)
{
  init_distance_sommet(g);
  psommet_t p = chercher_sommet(g, r);
  pfile_t f = creer_file();
  p->distance = 0;
  enfiler(f, p);
  while (!file_vide(f))
  {
    p = defiler(f);
    parc_t a = p->liste_arcs;
    while (a != NULL)
    {
      if (a->dest->distance > p->distance + a->poids)
      {
        a->dest->distance = p->distance + a->poids;
        enfiler(f, a->dest);
      }
      a = a->arc_suivant;
    }
  }
  detruire_file(f);
  return;
}
void affiche_chemin(pchemin_t c)
{
  //printf("\nChemin : \n");
  printf("(%d)", c->sommet->label);
  if (c->longueur == 1)
  {
    printf("\n");
    return;
  }
  int i = 0;
  for (;i < c->longueur - 1; i++)
  {
    if (i == c->longueur - 2)
    {
      break;
    }
    
    printf("->%d", c->liste_arc[i]->dest->label);
  }
  printf("->(%d)\n", c->liste_arc[i]->dest->label);
}
pchemin_t creer_chemin(pgraphe_t g, int taille, int *r)
{

  psommet_t s = chercher_sommet(g, r[0]);
  if (s == NULL)
  {
    //printf("erreur sommet inexistant\n");
    return NULL;
  }
  pchemin_t p = malloc(sizeof(chemin_t));
  p->liste_arc = malloc(sizeof(arc_t) * taille);
  p->longueur = taille;
  p->sommet = s;
  for (int i = 1; i < taille; i++)
  {
    parc_t a = existence_arc(s->liste_arcs, chercher_sommet(g, r[i]));
    if (a == NULL)
    {
      //fprintf(stderr, "erreur arc inexistant\n");
      return NULL;
    }

    p->liste_arc[i - 1] = a;
    s = a->dest;
  }
  return p;
}

void detruire_chemin(pchemin_t c)
{
  free(c->liste_arc);
  free(c);
}

// ======================================================================
int elementaire(pgraphe_t g, chemin_t c)
{
  init_couleur_sommet(g);
  c.sommet->couleur = 1;
  for (int i = 0; i < c.longueur - 1; i++)
  {
    if (c.liste_arc[i]->dest->couleur == 0)
    {
      c.liste_arc[i]->dest->couleur = 1;
    }
    else
    {
      return 0;
    }
  }
  return 1;
}


int simple(pgraphe_t g, chemin_t c)
{
  for (int i = 0; i < c.longueur - 1; i++)
  {
    for (int j = i + 1; j < c.longueur - 1; j++)
    {
      if (c.liste_arc[i] == c.liste_arc[j])
        return 0;
    }
  }
  return 1;
}


int longueur_chemin(pchemin_t c, int x, int y)
{
  int longeur = 0;
  if (c->sommet->label == x)
  {
    for (int i = 0; i < c->longueur - 1; i++)
    {
      longeur += c->liste_arc[i]->poids;
      if (c->liste_arc[i]->dest->label == y)
      {
        return longeur;
      }
    }
  }
  else
  {
    for (int i = 0; i < c->longueur - 1; i++)
    {
      if (c->liste_arc[i]->dest->label == x)
      {
        for (int j = i + 1; j < c->longueur - 1; j++)
        {
          if (c->liste_arc[j]->dest->label == y)
          {
            return longeur;
          }
          longeur += c->liste_arc[j]->poids;
        }
      }
    }
  }
  return 0;
}

int distance(pgraphe_t g, int x, int y)
{
  init_distance_sommet(g);
  algo_dijkstra(g, x);
  return chercher_sommet(g, y)->distance;
}

int excentricite(pgraphe_t g, int n)
{
  init_distance_sommet(g);
  algo_dijkstra(g, n);
  int max = INT_MIN;
  for (int i = 1; i <= nombre_sommets(g); i++)
  {
    psommet_t temp = chercher_sommet(g, i);
    if (temp->distance > max && temp->distance != INT_MAX)
    {
      max = temp->distance;
    }
  }
  return max;
}

int diametre(pgraphe_t g)
{
  int max = INT_MIN;
  psommet_t p = g;

  while (p != NULL)
  {

    int temp = excentricite(g, p->label);
    if (temp > max)
    {
      max = temp;
    }
    p = p->sommet_suivant;
  }
  return max;
}
int arc_dans_chemin(pchemin_t c, parc_t a)
{
  for (int i = 0; i < c->longueur - 1; i++)
  {
    if (c->liste_arc[i] == a)
    {
      return 1;
    }
  }
  return 0;
}

int eulerien(pgraphe_t g, pchemin_t c)
{
  psommet_t p = g;
  while (p != NULL)
  {
    arc_t *a = p->liste_arcs;
    while (a != NULL)
    {
      if (!arc_dans_chemin(c, a))
      {
        return 0;
      }
      a = a->arc_suivant;
    }
    p = p->sommet_suivant;
  }

  return 1;
}

int sommet_dans_chemin(pchemin_t c, psommet_t s)
{
  if (c->sommet == s)
  {
    return 1;
  }
  for (int i = 0; i < c->longueur - 1; i++)
  {
    if (c->liste_arc[i]->dest == s)
    {
      return 1;
    }
  }
  return 0;
}
int hamiltonien(pgraphe_t g, pchemin_t c)
{
  psommet_t p = g;
  while (p != NULL)
  {

    if (!sommet_dans_chemin(c, p))
    {
      return 0;
    }
    p = p->sommet_suivant;
  }

  return 1;
}
int deja_visite_hamil(int *tab, int taille, int r)
{

  for (int i = taille - 1; i >= 0; i--)
  {
    if (tab[i] == r)
    {
      return i;
    }
  }
  return -1;
}

int rec_graphe_hamil(pgraphe_t g, psommet_t p, int *tab, int taille, int indice)
{
  if (indice == taille)
  {
    return 0;
  }

  // partie qui évite que le chemin boucle
  int i = deja_visite_hamil(tab, indice, p->label); // regarde si le sommet a deja été visité
  int double_visite = 0;
  int temp;
  if (i != -1) // si le sommet a deja été visité
  {
    for (int j = i + 1; j < indice; j++) // on parcours tout les points visités depuis la dernière visite du sommet
    {
      temp = 0;
      for (int k = 0; k < i; k++) // et on regarde si le sommet a deja été visité avant
      {
        if (tab[j] == tab[k])
        {
          temp = 1;
          break;
        }
      }
      if (temp == 1)
      {
        double_visite = 1;
        break;
      }
    }
    if (double_visite) // s'il n'y a pas eu de nouveau sommet découvert depuis la visite du sommet précédente on arrete
    {
      return 0;
    }
  }

  // partie de test d'un chemin
  parc_t a = p->liste_arcs;
  int res;
  tab[indice++] = p->label;
  pchemin_t c = creer_chemin(g, indice, tab);
  if (c == NULL)
  {
    return 0;
  }
  // affiche_chemin(c);
  if (hamiltonien(g, c))
  {
    affiche_chemin(c);
    return 1;
  }
  free(c->liste_arc);
  free(c);
  while (a != NULL)
  {

    res = rec_graphe_hamil(g, a->dest, tab, taille, indice);
    if (res == 1)
    {
      return 1;
    }
    a = a->arc_suivant;
  }
  return 0;
}

int graphe_hamiltonien(pgraphe_t g)
{
  int taille = nombre_sommets(g);
  int indice = 0;
  int *tab = malloc(sizeof(int) * taille * taille); // au dela on suppose que le graphe n'est pas hamiltonien
  for (int i = 0; i < taille * taille; i++)
  {
    tab[i] = 0;
  }
  psommet_t p = g;
  while (p != NULL)
  {
    if (rec_graphe_hamil(g, p, tab, taille * taille, 0))
    {
      return 1;
    }
    p = p->sommet_suivant;
  }
  free(tab);
  return 0;
}
int deja_visite_eul(int *tab, int taille, int r, int r2)
{
  for (int i = taille - 2; i > 0; i--)
  {
    if (tab[i] == r2 && tab[i - 1] == r)
    {
      return i - 1;
    }
  }
  return -1;
}
int rec_graphe_eul(pgraphe_t g, psommet_t p, int *tab, int taille, int indice)
{
  if (indice == taille)
  {
    return 0;
  }
  parc_t a = p->liste_arcs;
  int res;
  tab[indice++] = p->label;
  pchemin_t c = creer_chemin(g, indice, tab);
  if (c == NULL)
  {
    return 0;
  }
  // affiche_chemin(c);
  if (eulerien(g, c))
  {
    affiche_chemin(c);
    return 1;
  }
  free(c->liste_arc);
  free(c);

  // optimisation
  while (a != NULL)
  {
    tab[indice] = a->dest->label;
    int i = deja_visite_eul(tab, indice + 1, p->label, a->dest->label);
    int double_visite = 0;
    int temp;
    if (i != -1) // si le sommet a deja été visité
    {

      for (int j = i + 1; j < indice + 1; j++) // on parcours tout les points visités depuis la dernière visite du sommet
      {
        temp = 0;
        for (int k = 0; k < i; k++) // et on regarde si le sommet a deja été visité avant
        {
          if (tab[j] == tab[k] && tab[j + 1] == tab[k + 1])
          {
            temp = 1;
            break;
          }
        }
        if (temp == 1)
        {
          double_visite = 1;
          break;
        }
      }
      if (double_visite) // s'il n'y a pas eu de nouveau sommet découvert depuis la visite du sommet précédente on arrete
      {
        // a = a->arc_suivant;
        // continue;
        return 0;
      }
    }

    // s'il n'y a pas eu de nouveau sommet découvert depuis la visite du sommet précédente on arrete

    res = rec_graphe_eul(g, a->dest, tab, taille, indice);
    if (res == 1)
    {
      return 1;
    }

    a = a->arc_suivant;
  }
  return 0;
}

int graphe_eulerien(pgraphe_t g)
{
  int taille = nombre_sommets(g);
  int indice = 0;
  int *tab = malloc(sizeof(int) * taille * taille);
  for (int i = 0; i < taille * taille; i++)
  {
    tab[i] = 0;
  }
  psommet_t p = g;
  while (p != NULL)
  {
    if (rec_graphe_eul(g, p, tab, taille * taille, 0))
    {
      return 1;
    }
    p = p->sommet_suivant;
  }
  free(tab);
  return 0;
}

int degre_sortant_sommet(pgraphe_t g, psommet_t s)
{
  /*
    Cette fonction retourne le nombre d'arcs sortants
    du sommet n dans le graphe g
  */

  return 0;
}

int degre_entrant_sommet(pgraphe_t g, psommet_t s)
{
  /*
    Cette fonction retourne le nombre d'arcs entrants
    dans le noeud n dans le graphe g
  */

  return 0;
}

int degre_maximal_graphe(pgraphe_t g)
{
  /*
    Max des degres des sommets du graphe g
  */

  return 0;
}

int degre_minimal_graphe(pgraphe_t g)
{
  /*
    Min des degres des sommets du graphe g
  */

  return 0;
}

int independant(pgraphe_t g)
{
  /* Les aretes du graphe n'ont pas de sommet en commun */

  return 0;
}

int complet(pgraphe_t g)
{
  /* Toutes les paires de sommet du graphe sont jointes par un arc */

  return 0;
}

int regulier(pgraphe_t g)
{
  /*
     graphe regulier: tous les sommets ont le meme degre
     g est le ponteur vers le premier sommet du graphe
     renvoie 1 si le graphe est régulier, 0 sinon
  */

  return 0;
}

/*
  placer les fonctions de l'examen 2017 juste apres
*/