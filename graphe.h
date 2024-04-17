
typedef struct a *parc_t;

/*
  definition des types sommet et pointeur de sommet
  un graphe est constitué d'une liste de sommets
*/

typedef struct s
{
  int label;                // label du sommet
  parc_t liste_arcs;        // arcs sortants du sommet
  struct s *sommet_suivant; // sommet suivant dans le graphe
  int couleur;              // couleur du sommet
  int distance;             // distance du sommet
} sommet_t, *psommet_t;

/*
  definition des types arc et pointeur d'arc
  Les arcs sortants d'un sommet sont chainés
  Pour chaque arc, il y a un poids qui peut par exemple correspondre a une distance
*/

typedef struct a
{

  int poids;             // poids de l arc
  psommet_t dest;        // pointeur sommet destinataire
  struct a *arc_suivant; // arc suivant

} arc_t, *parc_t;

typedef struct chemin_t // Un chemin est une suite consécutive d’arcs dans un graphe.
{
  psommet_t sommet;  // arc de depart du chemin
  parc_t *liste_arc; // chemin suivant
  int longueur;      // longueur du chemin
} chemin_t, *pchemin_t;

/*
  pgraphe_t: pointeur vers le premier sommet d'un graphe
*/

typedef psommet_t pgraphe_t;

psommet_t chercher_sommet(pgraphe_t g, int label);

void ajouter_arc(psommet_t o, psommet_t d, int distance);

int nombre_arcs(pgraphe_t g);

int nombre_sommets(pgraphe_t g);

void lire_graphe(char *file_name, pgraphe_t *g);

void ecrire_graphe(psommet_t p);

void ecrire_graphe_colorie(psommet_t p);

int colorier_graphe(pgraphe_t g);

void afficher_graphe_profondeur(pgraphe_t g, int r);

void afficher_graphe_largeur(pgraphe_t g, int r);

void algo_dijkstra(pgraphe_t g, int r);
void affiche_poids(pgraphe_t g, int r);
void affiche_chemin(pchemin_t c);
pchemin_t creer_chemin(pgraphe_t g, int taille, int *r);
void detruire_chemin(pchemin_t c);
int elementaire(pgraphe_t g, chemin_t c);
int simple(pgraphe_t g, chemin_t c);
int longueur_chemin(pchemin_t c, int x, int y);
int distance(pgraphe_t g, int x, int y);
int excentricite(pgraphe_t g, int n);
int diametre(pgraphe_t g);
int eulerien(pgraphe_t g, pchemin_t c);
int hamiltonien(pgraphe_t g, pchemin_t c);
int graphe_hamiltonien(pgraphe_t g);
int rec_graphe_hamil(pgraphe_t g, psommet_t p, int *tab, int taille, int indice);
int deja_visite_hamil(int *tab, int taille, int r);
int graphe_eulerien(pgraphe_t g);