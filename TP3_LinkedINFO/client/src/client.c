//#####################################################################
//#                                                                   #
//# Titre : 	CLIENT TP3 LINUX Automne 2016                         #
//#			SIF-1015 - Systeme d'exploitation                         #
//#			Universite du Quebec a Trois-Rivieres                     #
//#                                                                   #
//# Auteur : 	Adam Lemire & Remi Petiteau                           #
//#	Date :	18 decembre 2016                                           #
//#                                                                   #
//# Langage : 	ANSI C on LINUX 								      #			
//#                                                                   #
//#####################################################################

#include "../../server/src/gestionListeChaineeLinkedINFO.h"



int main(int argc, char* argv[]){

  pthread_t thread_transmit;
  pthread_t thread_receiv;
  
  
  //Création des fenetre
  init_screen();
  screen_ID();
  screen_transmit();
  screen_reception();

  pthread_create(&thread_transmit,NULL, transmit_msg,NULL);
  pthread_create(&thread_receiv,NULL, receiv_msg,NULL);
  
  pthread_join(thread_transmit,NULL);
  pthread_join(thread_receiv,NULL);

  end_screen();



  //Fin du programme
  exit(0);
}

