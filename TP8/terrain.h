#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifndef _TERRAIN_H_
#define _TERRAIN_H_

typedef enum { LIBRE, EAU, ROCHER } Case;

#define DIM_MAX 256

// indexation utilis�e : 
//  1er  indice : abscisse = colonne (colonne de gauche : abscisse = 0)
//  2�me indice : ordonn�e = ligne   (ligne du haut     : ordonn�e = 0)

typedef struct {
  int largeur, hauteur;
  Case tab[DIM_MAX][DIM_MAX];
} Terrain;

typedef enum {
  OK,
  ERREUR_FICHIER, //le fichier dont le nom est pass� en param�tre ne peut �tre ouvert
  LARGEUR_VIDE, //si on n'a pas trouv� la valeur de largeur
  ERREUR_LARGEUR_INCORRECTE,  //largeur<0 et >DIM_MAX
  HAUTEUR_VIDE, //si on n'a pas trouv� la valeur de hauteur
  ERREUR_HAUTEUR_INCORRECTE,  //hauteur<0 et >DIM_MAX
  ERREUR_LARGEUR_TAILLE,  //la longueur d'une ligne n'est pas �gale � la largeur 
  ERREUR_HAUTEUR_TAILLE,//le nombre de lignes n'est pas �gal � la hauteur 
  ERREUR_LECTURE_HAUTEUR,
  ERREUR_LECTURE_LARGEUR,
  ERREUR_LIGNES_MANQUANTES,
  ERREUR_LIGNE_TROP_COURTE,
  ERREUR_LIGNE_TROP_LONGUE,
  ERREUR_CARACTERE_INCORRECT,
  ERREUR_POSITION_ROBOT_MANQUANTE,
} erreur_terrain;


/* Lecture d'un terrain dans un fichier de nom nom_f
   R�sultats :
   t le terrain lu
   x, y position initiale du robot lue dans le fichier terrain
   Renvoie :
   OK si la lecture s'est d�roul�e correctement
   ERREUR_FICHIER si le fichier n'a pas pu �tre ouvert
   ... (� compl�ter)
 */
erreur_terrain lire_terrain(char * nom_fichier, Terrain * t, int * x, int * y);

/* Largeur d'un terrain */
int largeur(Terrain t);

/* Hauteur d'un terrain */
int hauteur(Terrain t);

/* Indique si la case de coordonn�es (x,y) est libre
   Renvoie vrai ssi les 3 conditions suivantes sont vraies :
    - 0 <= x < largeur
    - 0 <= y < hauteur
    - t.tab[x][y] = LIBRE
 */
int est_case_libre(Terrain t, int x, int y);

void afficher_terrain(Terrain * t);

void ecrire_terrain(FILE *f, Terrain T, int x, int y);
#endif
