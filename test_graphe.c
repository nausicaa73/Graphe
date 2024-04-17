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

  printf("\nnombre de sommets du graphe %d nombre arcs %d \n", nombre_sommets(g), nombre_arcs(g));
  fflush(stdout);

  ecrire_graphe(g);

  nc = colorier_graphe(g);

  printf("\nnombre chromatique graphe = %d\n", nc);

  // ecrire_graphe_colorie(g);
  printf("\nAfficher graphe en largeur : \n");
  afficher_graphe_largeur(g, g->label);
  printf("\nAfficher graphe en profondeur : \n");
  afficher_graphe_profondeur(g, g->label);
  printf("\nAfficher Dijkstra : \nAvant : \n");
  affiche_poids(g, g->label);
  algo_dijkstra(g, g->label);
  printf("\nAprès : \n");
  affiche_poids(g, g->label);
  printf("\n");


  // test des fonctions de chemin
  
  int x, y;
  
  int chemin[] = {1, 2, 1, 1, 3, 2, 1};
  pchemin_t c = creer_chemin(g, sizeof(chemin) / sizeof(int), chemin);
  if (c != NULL)
  {
    printf("\n================================chemin 1========================================================\n");

    affiche_chemin(c);
    printf("\nLe chemin %s élémentaire\n", elementaire(g, *c) ? "est" : "n'est pas");
    printf("Le chemin %s simple\n", simple(g, *c) ? "est" : "n'est pas");

    int x = c->sommet->label, y = c->liste_arc[c->longueur - 2]->dest->label;
    printf("La longueur du chemin entre (%d) et (%d) est %d\n",x,y,longueur_chemin(c, x,y));
    
    printf("Le chemin %s eulerien\n", eulerien(g, c) ? "est" : "n'est pas");
    printf("Le chemin %s hamiltonien\n\n", hamiltonien(g, c) ? "est" : "n'est pas");

    detruire_chemin(c);
  }

  int chemin2[] = {1};
  c = creer_chemin(g, sizeof(chemin2) / sizeof(int), chemin2);
  if (c != NULL)
  {
    printf("\n================================chemin 2========================================================\n");

    affiche_chemin(c);
    printf("\nLe chemin %s élémentaire\n", elementaire(g, *c) ? "est" : "n'est pas");
    printf("Le chemin %s simple\n", simple(g, *c) ? "est" : "n'est pas");

    printf("La longueur du chemin entre (%d) et (%d) est %d\n",1,1,longueur_chemin(c, 1,1));
    
    printf("Le chemin %s eulerien\n", eulerien(g, c) ? "est" : "n'est pas");
    printf("Le chemin %s hamiltonien\n\n", hamiltonien(g, c) ? "est" : "n'est pas");
  }


  int chemin3[] = {1,6,2,1,6,2,3,6,2};
  c = creer_chemin(g, sizeof(chemin3) / sizeof(int), chemin3);
  if (c != NULL)
  {
    printf("\n================================chemin 3========================================================\n");

    affiche_chemin(c);
    printf("\nLe chemin %s élémentaire\n", elementaire(g, *c) ? "est" : "n'est pas");
    printf("Le chemin %s simple\n", simple(g, *c) ? "est" : "n'est pas");

    int x = c->sommet->label, y = c->liste_arc[c->longueur - 2]->dest->label;
    printf("La longueur du chemin entre (%d) et (%d) est %d\n",x,y,longueur_chemin(c, x,y));
    
    printf("Le chemin %s eulerien\n", eulerien(g, c) ? "est" : "n'est pas");
    printf("Le chemin %s hamiltonien\n\n", hamiltonien(g, c) ? "est" : "n'est pas");

    detruire_chemin(c);
  }

  int chemin4[] = {1,6,2,1,6,2,3,6,2,5,3,4,5,3,6};
  c = creer_chemin(g, sizeof(chemin4) / sizeof(int), chemin4);
  if (c != NULL)
  {
    printf("\n================================chemin 4========================================================\n");

    affiche_chemin(c);
    printf("\nLe chemin %s élémentaire\n", elementaire(g, *c) ? "est" : "n'est pas");
    printf("Le chemin %s simple\n", simple(g, *c) ? "est" : "n'est pas");

    int x = c->sommet->label, y = c->liste_arc[c->longueur - 2]->dest->label;
    printf("La longueur du chemin entre (%d) et (%d) est %d\n",x,y,longueur_chemin(c, x,y));
    
    printf("Le chemin %s eulerien\n", eulerien(g, c) ? "est" : "n'est pas");
    printf("Le chemin %s hamiltonien\n\n", hamiltonien(g, c) ? "est" : "n'est pas");

    detruire_chemin(c);
  }

  int chemin5[] = {1,7,3,12,9,12,9,12,6,11,10,5,9,2,7,1};
  c = creer_chemin(g, sizeof(chemin5) / sizeof(int), chemin5);
  if (c != NULL)
  {
    printf("\n================================chemin 5========================================================\n");

    affiche_chemin(c);
    printf("\nLe chemin %s élémentaire\n", elementaire(g, *c) ? "est" : "n'est pas");
    printf("Le chemin %s simple\n", simple(g, *c) ? "est" : "n'est pas");

    int x = c->sommet->label, y = c->liste_arc[c->longueur - 2]->dest->label;
    printf("La longueur du chemin entre (%d) et (%d) est %d\n",x,y,longueur_chemin(c, x,y));
    
    printf("Le chemin %s eulerien\n", eulerien(g, c) ? "est" : "n'est pas");
    printf("Le chemin %s hamiltonien\n\n", hamiltonien(g, c) ? "est" : "n'est pas");

    detruire_chemin(c);
  }

  int chemin6[] = {9,8,9,6,7,4,5,2,3};
  c = creer_chemin(g, sizeof(chemin6) / sizeof(int), chemin6);
  if (c != NULL)
  {
    printf("\n================================chemin 6========================================================\n");

    affiche_chemin(c);
    printf("\nLe chemin %s élémentaire\n", elementaire(g, *c) ? "est" : "n'est pas");
    printf("Le chemin %s simple\n", simple(g, *c) ? "est" : "n'est pas");

    int x = c->sommet->label, y = c->liste_arc[c->longueur - 2]->dest->label;
    printf("La longueur du chemin entre (%d) et (%d) est %d\n",x,y,longueur_chemin(c, x,y));
    
    printf("Le chemin %s eulerien\n", eulerien(g, c) ? "est" : "n'est pas");
    printf("Le chemin %s hamiltonien\n\n", hamiltonien(g, c) ? "est" : "n'est pas");

    detruire_chemin(c);
  }




  
  printf("Le graphe %s hamiltonien\n\n", graphe_hamiltonien(g) ? "est" : "n'est pas");
  printf("Le graphe %s eulerien\n", graphe_eulerien(g) ? "est" : "n'est pas");

  x = g->label;
  for (int i = 1; i <= nombre_sommets(g); i++){
    printf("\nLa distance entre les sommets %d et %d est de %d", x,i,distance(g, x, i));
  }

  printf("\n");
  
  for (int i = 1; i <= nombre_sommets(g); i++){
    printf("\nL'excentricité du sommet %d est de %d", i, excentricite(g, i));
  }
  printf("\n\nLe diamètre du graphe est de %d\n", diametre(g));

}
