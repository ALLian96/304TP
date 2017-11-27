#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "generation_terrains.h"

int nb_cases_occupees(Terrain T){
	int occupee = 0;
	int x, y;
	for(x=0; x<largeur(T); x++){
		for(y=0; y<hauteur(T); y++){
			if(T.tab[x][y] != LIBRE)
			occupee++;
		}
	}
	return occupee;
}

// Test de generation aléatoire de terrains
// Le programme génère n terrains de largeur et hauteur fixes
// avec largeur et hauteur impaires et inférieures a dimension_max de terrain.h
// avec densité d'obstacle dObst
// autre que la case centrale soit occupee
// l'appel du programme se fait avec 5 arguments :
// generation_terrains N largeur hauteur dObstacle fichier_res
// la sortie se fait dans le fichier resultat

int main(int argc, char ** argv){
  int N, i, l, h;
  float dObst;
  float dmoyen,perc_valide;
  FILE* resFile;
  Terrain T;
  int compt_terrain_v=0;
  int nbtotal_case_occup=0;
  if (argc < 6) {
    printf("Usage: %s <N> <largeur> <hauteur> <densite_obstacle> <fichier_res> \n", argv[0]);
    return 1;
  }
    
  N = strtol(argv[1], NULL, 10);
  l = strtol(argv[2], NULL, 10);
  h = strtol(argv[3], NULL, 10);
  dObst = strtof(argv[4], NULL);
  
  // test de l et h
  if (l>DIM_MAX || l%2 == 0) {
    printf("Largeur incorrecte : doit être impaire et <= %d\n", DIM_MAX);
    return 1;
  }
  if (h>DIM_MAX || h%2 == 0) {
    printf("Hauteur incorrecte : doit être impaire et <= %d\n", DIM_MAX);
    return 1;
  }
  if ((dObst > 1) || (dObst < 0)) {
    printf("Densité incorrecte : doit être comprise entre 0 et 1\n");
    return 1;
  }
	
  // Ouverture du fichier résultat
  resFile = fopen(argv[5], "w");
  // Écriture du nombre de terrains
  fprintf(resFile, "%d\n", N);
	
  //Initialisation de la fonction random
  srand(time(NULL));

  // Génération aléatoire des terrains
  for(i=0;i<N;i++){
  	generation_aleatoire(&T,l,h,dObst);
  // Écriture des terrains générés dans le fichier resFile
        ecrire_terrain(resFile,T,l,h);
	if(existe_chemin_vers_sortie(T)){
	compt_terrain_v++;	
	}
	nbtotal_case_occup=nbtotal_case_occup + nb_cases_occupees(T);
  }
  // Écriture/Affichage des statistiques
  dmoyen = (float)nbtotal_case_occup/(N*l*h);
  fprintf(resFile,"la densité d'obstacle moyenne : %.3f\n",dmoyen);
  
  perc_valide = (float)compt_terrain_v/N*100;
  fprintf(resFile,"le pourcentage de terrain valides : %.2f%%\n",perc_valide);
  // fermeture des fichiers	
  fclose(resFile);
  return 0;
}
