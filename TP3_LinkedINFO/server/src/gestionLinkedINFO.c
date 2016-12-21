//#####################################################################
//#                                                                   #
//# Titre : 	gestionLinkedINFO TP3 LINUX Automne 2016              #
//#			SIF-1015 - Systeme d'exploitation                         #
//#			Universite du Quebec a Trois-Rivieres                     #
//#                                                                   #
//# Auteur : 	Adam Lemire & Remi Petiteau                           #
//#	Date :	18 decembre 2016                                           #
//#                                                                   #
//# Langage : 	ANSI C on LINUX                                       #
//#                                                                   #
//#####################################################################

#include "gestionListeChaineeLinkedINFO.h"

//Pointeur de tete de liste
extern struct noeud* head;
//Pointeur de queue de liste pour ajout rapide
extern struct noeud* queue;

//#define MAX_THREAD 100

//#####################################################################
//#                                                                   #
//# Affiche un message et quitte le programme						  #
//#                                                                   #
//#####################################################################
void error(const int exitcode, const char * message){
  printf("\n-------------------------\n%s\n",message);
  exit(exitcode);
}



//#####################################################################
//#                                                                   #
//# fonction utilisee par les threads de transactions									#
//#                                                                   #
//#####################################################################
void* readTransLinkedINFO(struct Info_Transaction my_data){
  char *tok, *sp;

  //creation d'un thread
  pthread_t thread_transac;

  tok = strtok_r(my_data.transaction, " ", &sp);

   //Branchement selon le type de transaction
   switch(tok[0]){
	case 'A':
	case 'a':{
		//Definition de la structure des parametres du thread ajout
		p_struct_ajout ajout = (p_struct_ajout)malloc(sizeof(struct_ajout));
		//Extraction des parametres
		ajout->ptrNick = strtok_r(NULL, " ", &sp);
		ajout->ptrSpecialite = strtok_r(NULL, " ", &sp);
		ajout->ptrFormation = strtok_r(NULL, " ", &sp);
		ajout->experience = atoi(strtok_r(NULL, "\n", &sp));
      
		ajout->pid=my_data.pid_client;
      
		//ajout du socket
		struct sockaddr_un soketaddr_comm;

		socklen_t len;
		int socket_comm;
		len = sizeof(soketaddr_comm);
		socket_comm = accept(server_socket_comm, (struct sockaddr *)&soketaddr_comm, &len);
		if( socket_comm == -1 ) 
			fprintf(stderr, "Client refuse\n");
		ajout->socket=socket_comm;
      
		//Creation du thread
		pthread_create(&thread_transac,NULL, thread_ajout,ajout);
		break;
    }

    case 'E':
    case 'e':{
      //Definition de la struture des parametres du thread elim
      p_struct_elim elim = (p_struct_elim)malloc(sizeof(struct_elim));
      //Extraction du parametre
      elim->ptrNick = strtok_r(NULL, " ", &sp);
      elim->ptrSpecialite = strtok_r(NULL, " ", &sp);
      elim->ptrFormation = strtok_r(NULL, " ", &sp);
      elim->experience = atoi(strtok_r(NULL, "\n", &sp));
      //Creation du thread
      pthread_create(&thread_transac,NULL, thread_elim,elim);
      break;
    }
    case 'L':
    case 'l':{
      //Extraction des parametres
      char *ptrType = strtok_r(NULL, " ", &sp);
      
      
      if(strcmp(ptrType, "C") == 0) // affichage complet
			{
				//Definition de la struture des parametres du thread affiche
				p_struct_afficheC affiche = (p_struct_afficheC)malloc(sizeof(struct_afficheC));
				//Extraction des parametres
				affiche->nstart = atoi(strtok_r(NULL, "-", &sp));
				affiche->nend = atoi(strtok_r(NULL, "\n", &sp));
				affiche->pid = my_data.pid_client;
	  
				//Creation du thread
				pthread_create(&thread_transac,NULL, thread_affiche,affiche);
				break;
			}
	
			else if(strcmp(ptrType, "S") == 0) // affichage par specialite
			{				
				p_struct_afficheS affiche = (p_struct_afficheS) malloc(sizeof(infoLISTS));
		
				affiche->ptrSpecialite = strtok_r(NULL, "\n", &sp);
				affiche->pid = my_data.pid_client;
			
				//Appel de la fonction associee
				pthread_create(&thread_transac,NULL, thread_afficheS,affiche);
				break;
			}
	
      
			else if(strcmp(ptrType, "SE") == 0) // affichage par specialite
			{				
				p_struct_afficheSE affiche = (p_struct_afficheSE) malloc(sizeof(infoLISTSE));
		
				affiche->ptrSpecialite = strtok_r(NULL, " ", &sp);
				affiche->nstart = atoi(strtok_r(NULL, "-", &sp));
				affiche->nend = atoi(strtok_r(NULL, "\n", &sp));
				affiche->pid = my_data.pid_client;
			
				//Appel de la fonction associee
				pthread_create(&thread_transac,NULL, thread_afficheSE,affiche);
				break;
			}
	
	
			else if(strcmp(ptrType, "SF") == 0) // affichage par specialite
			{				
				p_struct_afficheSF affiche = (p_struct_afficheSF) malloc(sizeof(infoLISTSF));
		
				affiche->ptrSpecialite = strtok_r(NULL, " ", &sp);
				affiche->ptrFormation = strtok_r(NULL, "\n", &sp);
				affiche->pid = my_data.pid_client;
			
				//Appel de la fonction associee
				pthread_create(&thread_transac,NULL, thread_afficheSF,affiche);
				break;
			}
	
	
			else if(strcmp(ptrType, "SFE") == 0) // affichage par specialite
			{				
				p_struct_afficheSFE affiche = (p_struct_afficheSFE) malloc(sizeof(infoLISTSFE));
		
				affiche->ptrSpecialite = strtok_r(NULL, " ", &sp);
				affiche->ptrFormation = strtok_r(NULL, " ", &sp);
				affiche->nstart = atoi(strtok_r(NULL, "-", &sp));
				affiche->nend = atoi(strtok_r(NULL, "\n", &sp));
				affiche->pid = my_data.pid_client;
			
				//Appel de la fonction associee
				pthread_create(&thread_transac,NULL, thread_afficheSFE,affiche);
				break;
			}
      
		}
    case 'T':
    case 't':{
      
      //Extraction des parametres
			char *ptrType = strtok_r(NULL, " ", &sp);
				
			if(strcmp(ptrType, "PG") == 0) // affichage personne a groupe
			{
				//Definition de la struture des parametres du thread transmit
				p_struct_transmit transmitpg = (p_struct_transmit)malloc(sizeof(struct_transmit));
				//Extraction des parametres
				transmitpg->ptrNick = strtok_r(NULL, " ", &sp);
				transmitpg->ptrSpecialite = strtok_r(NULL, " ", &sp);
				transmitpg->ptrTexte = strtok_r(NULL, "\n", &sp);
				//Creation du thread
				pthread_create(&thread_transac,NULL, thread_transmit,transmitpg);
				break;
			}
	
			if(strcmp(ptrType, "PP") == 0) // affichage personne a personne
			{
				//Definition de la struture des parametres du thread transmit
				p_struct_transmitpp transmitpp = (p_struct_transmitpp)malloc(sizeof(struct_transmitpp));
				//Extraction des parametres
				transmitpp->ptrNick1 = strtok_r(NULL, " ", &sp);
				transmitpp->ptrNick2 = strtok_r(NULL, " ", &sp);
				transmitpp->ptrTexte = strtok_r(NULL, "\n", &sp);
				//Creation du thread
				pthread_create(&thread_transac,NULL, thread_transmitpp,transmitpp);
				break;
			}
	
    }
  }

  //Attente de la fin des thread
  pthread_join(thread_transac,NULL);


  //Retour
  return NULL;
}
