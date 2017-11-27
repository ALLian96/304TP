#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "programme.h"


void gestion_erreur_programme(erreur_programme e) {
  switch(e.type_err) {
  case OK_PROGRAMME: break;
  case ERREUR_FICHIER_PROGRAMME:
    printf("Erreur lecture du programme : erreur d'ouverture du fichier\n");
    exit(2);
  case ERREUR_BLOC_NON_FERME:
    printf("Erreur lecture du programme : bloc non fermé\n");
    exit(2);
  case ERREUR_FERMETURE_BLOC_EXCEDENTAIRE:
    printf("Erreur lecture du programme : fermeture de bloc excédentaire\n");
    affichage_position_programme(e);
    exit(2);
  case ERREUR_COMMANDE_INCORRECTE:
    printf("Erreur lecture du programme : commande incorrecte\n");
    affichage_position_programme(e);
    exit(2);
  }
}

int main(int argc, char ** argv){
  FILE *f_res;
  Terrain T;
  int N,L,H,nb_step_max,graine;
  float d;
  Programme prog;
  erreur_programme errp;
  etat_inter etat;
  resultat_inter res;
  Environnement env;
  int nb_pas,nb_pastotal;
  int resstats,i,nbts,nbtb,nbto;  
  /*resstats: résultat de statistique; nbts: nombre de terrains d'où le robot est sorti, nbtb:nombre de terrains d'où le robot est bloqué, nbto;nombre de terrains d'où le robot est rentré dans un obstacle */
  nbts = 0;
  nbtb = 0;
  nbto = 0;
  nb_pastotal=0;
  if(argc<9){
	printf("Usage:%s <fichier_programme> <N> <L> <H> <d> <graine> <nb_step_max>       <fichier_res>\n",argv[0]);
  }
  f_res = fopen(argv[8],"w");
  N = strtol(argv[2], NULL, 10);
  L = strtol(argv[3], NULL, 10);
  H = strtol(argv[4], NULL, 10);
  d = strtof(argv[5], NULL);
  if (L>DIM_MAX || L%2 == 0) {
	printf("Largeur incorrecte : doit être impaire et <= %d\n", DIM_MAX);
   	return 1;
  }
  if (H>DIM_MAX || H%2 == 0) {
    printf("Hauteur incorrecte : doit être impaire et <= %d\n", DIM_MAX);
    return 1;
  }
  if ((d > 1) || (d < 0)) {
    printf("Densité incorrecte : doit être comprise entre 0 et 1\n");
    return 1;
  } 
  graine = strtol(argv[6], NULL, 10);
  nb_step_max = strtol(argv[7], NULL, 10);
  
  //Initialisation de la fonction srand
  srand(graine);
  
  /* Lire le fichier programme */
  errp = lire_programme(&prog, argv[1]);
  gestion_erreur_programme(errp);
  //Initialisation du robot
  init_robot(&(envt->r), (L-1)/2, (H-1)/2, Est);	
  // Génération aléatoire le terrain et tester
  fprintf(f,"%d\n",N);
  for(i=0;i<N;i++){
 	nb_pas=0;
	generation_aleatoire(&T,L,H,d);
	env.t = T;
	 /* Initialisation de l'état */
  	init_etat(&etat);
  	res  = OK_ROBOT;
  	while(res == OK_ROBOT && nb_pas < nb_step_max){
    	  res = exec_pas(&prog, &envt, &etat);   
     	  switch(res){
		case OK_ROBOT    : nb_pas ++;break;
      		case SORTIE_ROBOT: nbts++;fprintf(f,"%d\n",nb_pas);break;
      		case ARRET_ROBOT : nbtb++;resstats = -1;fprintf(f,"%d\n",resstats);break;
      		case PLOUF_ROBOT : resstats = -2;fprintf(f,"%d\n",resstats);break;
      		case CRASH_ROBOT :  nbto++;resstats = -3;fprintf(f,"%d\n",resstats);break;
    	  } 
  	}
	nb_pastotal += nb_pas;
  }
  /* décider le résultat */	
  }
    
  printf("nombre de terrains d'où le robot est sorti : %d soit %.2f%%\n",nbts,(float)nbts/N*100);
  printf("nombre de terrains d'où le robot est resté bloqué : %d soit %.2f%%\n",nbtb,(float)nbtb/N*100);
  printf("nombre de terrains d'où le robot est rentré dans un obstacle : %d soit %.2f%%\n",nbto,(float)nbto/N*100);
  printf(" nombre moyen de pas effectués pour les sorties : %.2f\n",nb_pastotal);
}