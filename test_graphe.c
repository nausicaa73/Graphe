#include <stdio.h>
#include <stdlib.h>

#include "file.h"

int main(int argc, char **argv)
{
  pgraphe_t g;
  int nc;

  if (argc != 2)
  {
    lire_graphe("./data/gr7", &g);
  }
  else
  {
    lire_graphe(argv[1], &g);
  }

  /*
     la fonction lire_graphe alloue le graphe (matrice,...)
     et lit les donnees du fichier passe en parametre
   */
  /*
    la fonction ecrire_graphe affiche le graphe a l'ecran
  */

  printf("nombre de sommets du graphe %d nombre arcs %d \n", nombre_sommets(g), nombre_arcs(g));
  fflush(stdout);

  ecrire_graphe(g);

  nc = colorier_graphe(g);

  printf("nombre chromatique graphe = %d\n", nc);

  // ecrire_graphe_colorie(g);

  afficher_graphe_largeur(g, g->label);
  printf("\n-------------------------\n");
  afficher_graphe_profondeur(g, g->label);
  algo_dijkstra(g, g->label);
  affiche_poids(g, g->label);
  printf("Le graphe %s hamiltonien\n", graphe_hamiltonien(g) ? "est" : "n'est pas");
  printf("Le graphe %s eulerien\n", graphe_eulerien(g) ? "est" : "n'est pas");
  int chemin[] = {1, 2, 1, 1, 3, 2, 1};
  pchemin_t c = creer_chemin(g, sizeof(chemin) / sizeof(int), chemin);
  if (c == NULL)
  {
    printf("Erreur lors de la création du chemin\n");
    exit(1);
  }
  affiche_chemin(c);
  printf("Le chemin %s élémentaire\n", elementaire(g, *c) ? "est" : "n'est pas");
  printf("Le chemin %s simple\n", simple(g, *c) ? "est" : "n'est pas");
  printf("La longueur du chemin entre 1 et 5 est %d\n", longueur_chemin(c, c->sommet->label, c->liste_arc[c->longueur - 2]->dest->label));
  printf("La distance entre 1 et 7 est %d\n", distance(g, g->label, g->sommet_suivant->label));
  printf("L'excentricité de 1 est %d\n", excentricite(g, g->label));
  printf("Le diamètre du graphe est %d\n", diametre(g));
  printf("Le chemin %s eulerien\n", eulerien(g, c) ? "est" : "n'est pas");
  printf("Le chemin %s hamiltonien\n", hamiltonien(g, c) ? "est" : "n'est pas");
}
