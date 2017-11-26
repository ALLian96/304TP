#include "terrain.h"
#include "robot.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

erreur_terrain lire_terrain(char * nom_fichier, Terrain * t, int * x, int * y) {
  FILE * f;
  int l, h; // Dimensions du terrain
  int rx, ry; // Coordonnées initiales du robot
  int pos_robot = 0; // Booléen : vrai si la position du robot a été lue
  int n; // Nombre de valeurs lues
  char * res; // Résultat de la lecture d'une ligne
  int lgligne; // Longueur de la ligne lue
  int i, j;
  char ligne[DIM_MAX];
  Case c;

  // Ouverture du fichier en lecture
  f = fopen(nom_fichier, "r"); 
  if (f == NULL) {
	printf("123");
	exit(-1);
    return ERREUR_FICHIER;
  }
  // Lecture de la largeur
  n = fscanf(f,"%d", &l);
  if (n == 0) {
    return ERREUR_LECTURE_LARGEUR;
  } else if ((l < 0) || (l > DIM_MAX)) {
    return ERREUR_LARGEUR_INCORRECTE;
  }
  t->largeur = l;
  // Lecture de la hauteur
  fscanf(f,"%d", &h);
  if (n == 0) {
    return ERREUR_LECTURE_HAUTEUR;
  } else if ((h < 0) || (h > DIM_MAX)) {
    return ERREUR_HAUTEUR_INCORRECTE;
  }
  t->hauteur = h;
  // Lecture du terrain
  // Lecture du caractère de retour à la ligne précédant la première ligne
  fscanf(f,"\n");
  for(j = 0; j < h; j++) {
    // Lecture d'une ligne dans le fichier
    res = fgets(ligne, DIM_MAX, f);
    if (res == NULL) {
      return ERREUR_LIGNES_MANQUANTES;
    }
    lgligne = strlen(ligne) - 1; // Tenir compte du caractère de retour à la ligne
    if(lgligne < l) {
      return ERREUR_LIGNE_TROP_COURTE;
    } else if (lgligne > l) {
      return ERREUR_LIGNE_TROP_LONGUE;
    }
    // Parcours de la ligne
    for(i = 0; i < l; i++) {
      // Initialisation d'une case
      switch(ligne[i]) {
      case '.': c = LIBRE; break; 
      case '#': c = ROCHER; break; 
      case '~': c = EAU; break;
      case 'C':
        c = LIBRE;
        rx = i;
        ry = j;
        pos_robot = 1;
        break;
      default:
        return ERREUR_CARACTERE_INCORRECT;
      }
      t->tab[i][j] = c;
    }
  }
  if (!pos_robot) {
    return ERREUR_POSITION_ROBOT_MANQUANTE;
  }
  // Initialisation de la position du robot
  *x = rx;
  *y = ry;
  fclose(f);
  return OK;
}

int largeur(Terrain t) {
  return t.largeur;
}

int hauteur(Terrain t) {
  return t.hauteur;
}

int est_case_libre(Terrain t, int x, int y) {
  if ((x >= 0) && (x < t.largeur)
      && (y >= 0) && (y < t.hauteur)) {
    return t.tab[x][y] == LIBRE;
  } else {
    return 0; // false
  }
}

void afficher_terrain(Terrain * t) {
  int i, j;
  char c;

  for(j = 0; j < t->hauteur; j++) {
    for(i = 0; i < t->largeur; i++) {
      switch(t->tab[i][j]) {
      case LIBRE : c = '.'; break;
      case ROCHER: c = '#'; break;
      case EAU   : c = '~'; break;
      }
      printf("%c", c);
    }
    printf("\n");
  }
}

void ecrire_terrain(FILE *f, Terrain T, int x, int y){
	int i,j;
	char c;
	float dObst_obtenu;
	int compteur_libre;
 	f = fopen("terrain_test.txt","w");
	if(f ! = NULL){
		fprintf(f,"%d\n",x);
		fprintf(f,"%d\n",y);
		for(j=0;j < hauteur(T); j++){
			for(i = 0; i< largeur(T); i++){
				switch(T.tab[i][j]){
				   case LIBRE : c = '.'; compteur_libre++; break;
                                   case ROCHER: c = '#'; 		   break;
      				   case EAU   : c = '~'; 		   break;
				}
				fprintf(f,"%c",c);
			}
		 	fputfc("\n",f);
		}
		dObst_obtenu = (l*h-compteur_libre)/l*h;
		fprintf(resFile,"%.2f\n",dObst_obtenu);
	}
}
