//#####################################################################
//#                                                                   #
//# Titre :	gestionListeChaineeLinkedINFO.c TP3 LINUX Automne 2016	  #
//#			SIF-1015 - Systeme d'exploitation                     	  #
//#			Universite du Quebec a Trois-Rivieres   	  			  #
//#                                                                   #
//# Auteur : 	Adam Lemire & Remi Petiteau           	              #
//#	Date :	18 decembre 2016                                       	  #
//#                                                                   #
//# Langage : 	ANSI C on LINUX                                  	  #
//#                                                                   #
//#####################################################################

#include "gestionListeChaineeLinkedINFO.h"

//Pointeur de head de liste
extern struct noeud* head;
//Pointeur de queue de liste pour ajout rapide
extern struct noeud* queue;

void* thread_ajout(void *arg){
  //Extraction des parametres
  p_struct_ajout ajt = arg;

  //Utilisation du semaphores P
  if(sem_wait(&sem_ajout)==-1){
    fprintf(stderr, "semaphore_p failed : %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }

  //Appel de la fonction associee
  addItemLinkedINFO(ajt->ptrNick, ajt->ptrSpecialite, ajt->ptrFormation, ajt->experience, ajt->socket, ajt->pid);
  
  //Utilisation du semaphores V
  if( sem_post(&sem_ajout)==-1){
    fprintf(stderr, "semaphore_v failed : %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }

  //Liberation de la structure
  free(ajt);
  //Fin du thread
  pthread_exit(0);
}


void* thread_elim(void* arg){
  //Extraction des paramètres
  p_struct_elim del = arg;

  //Utilisation du semaphore P
  if(sem_wait(&sem_elim)==-1){
    fprintf(stderr, "semaphore_p failed : %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }

  //Appel de la fonction associee
  removeItemLinkedINFO(del->ptrNick, del->ptrSpecialite, del->ptrFormation, del->experience);

  //Utilisation du semaphore V
  if( sem_post(&sem_elim)==-1){
    fprintf(stderr, "semaphore_v failed : %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }

  //Liberation de la struture
  free(del);
  //Fin du thread
  pthread_exit(0);
}

void* thread_affiche(void* arg){
  //Extraction des paramètres
  p_struct_afficheC aff = arg;

  //Utilisation du semaphore P
  if(sem_wait(&sem_affiche)==-1){
    fprintf(stderr, "semaphore_p failed : %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }

  //Appel de la fonction associee
  listItemsC(aff->nstart, aff->nend, aff->pid);

  //Utilisation du semaphore V
  if( sem_post(&sem_affiche)==-1){
    fprintf(stderr, "semaphore_v failed : %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }

  //Liberation de la struture
  free(aff);
  //Fin du thread
  pthread_exit(0);
}

void* thread_afficheS(void* arg){
  //Extraction des paramètres
  p_struct_afficheS aff = arg;

  //Utilisation du semaphore P
  if(sem_wait(&sem_affiche)==-1){
    fprintf(stderr, "semaphore_p failed : %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }

  //Appel de la fonction associee
  listItemsS(aff->ptrSpecialite, aff->pid);

  //Utilisation du semaphore V
  if( sem_post(&sem_affiche)==-1){
    fprintf(stderr, "semaphore_v failed : %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }

  //Liberation de la struture
  free(aff);
  //Fin du thread
  pthread_exit(0);
}

void* thread_afficheSE(void* arg){
  //Extraction des paramètres
  p_struct_afficheSE aff = arg;

  //Utilisation du semaphore P
  if(sem_wait(&sem_affiche)==-1){
    fprintf(stderr, "semaphore_p failed : %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }

  //Appel de la fonction associee
  listItemsSE(aff->ptrSpecialite,aff->nstart, aff->nend, aff->pid);

  //Utilisation du semaphore V
  if( sem_post(&sem_affiche)==-1){
    fprintf(stderr, "semaphore_v failed : %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }

  //Liberation de la struture
  free(aff);
  //Fin du thread
  pthread_exit(0);
}

void* thread_afficheSF(void* arg){
  //Extraction des paramètres
  p_struct_afficheSF aff = arg;

  //Utilisation du semaphore P
  if(sem_wait(&sem_affiche)==-1){
    fprintf(stderr, "semaphore_p failed : %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }

  //Appel de la fonction associee
  listItemsSF(aff->ptrSpecialite,aff->ptrFormation, aff->pid);

  //Utilisation du semaphore V
  if( sem_post(&sem_affiche)==-1){
    fprintf(stderr, "semaphore_v failed : %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }

  //Liberation de la struture
  free(aff);
  //Fin du thread
  pthread_exit(0);
}

void* thread_afficheSFE(void* arg){
  //Extraction des paramètres
  p_struct_afficheSFE aff = arg;

  //Utilisation du semaphore P
  if(sem_wait(&sem_affiche)==-1){
    fprintf(stderr, "semaphore_p failed : %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }

  //Appel de la fonction associee
  listItemsSFE(aff->ptrSpecialite,aff->ptrFormation,aff->nstart, aff->nend, aff->pid);

  //Utilisation du semaphore V
  if( sem_post(&sem_affiche)==-1){
    fprintf(stderr, "semaphore_v failed : %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }

  //Liberation de la struture
  free(aff);
  //Fin du thread
  pthread_exit(0);
}

void* thread_transmit(void* arg){
  //Extraction des paramètres
  p_struct_transmit transm = arg;

  //Utilisation du semaphore P
  if(sem_wait(&sem_transmit)==-1){
    fprintf(stderr, "semaphore_p failed : %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }
  //Appel de la fonction associee
  transTextPG(transm->ptrNick, transm->ptrSpecialite, transm->ptrTexte);
  
  //Utilisation du semaphore V
  if( sem_post(&sem_transmit)==-1){
    fprintf(stderr, "semaphore_v failed : %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }

  //Liberation de la struture
  free(transm);
  //Fin du thread
  pthread_exit(0);
}

void* thread_transmitpp(void* arg){
  //Extraction des paramètres
  p_struct_transmitpp transm = arg;

  //Utilisation du semaphore P
  if(sem_wait(&sem_transmit)==-1){
    fprintf(stderr, "semaphore_p failed : %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }
  //Appel de la fonction associee
  transTextPP(transm->ptrNick1, transm->ptrNick2, transm->ptrTexte);
  
  //Utilisation du semaphore V
  if( sem_post(&sem_transmit)==-1){
    fprintf(stderr, "semaphore_v failed : %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }

  //Liberation de la struture
  free(transm);
  //Fin du thread
  pthread_exit(0);
}

//#####################################################################
//#                                                                   #
//# Recherche le PREDECESSEUR d'un item dans la liste chainee         #
//#                                                                   #
//# RETOUR: Le pointeur vers le predecesseur est retourne             #
//#                                                                   #
//#                                                                   #
//# 		Retourne NULL dans le cas ou l'item est introuvable       #
//#                                                                   #
//#####################################################################

struct noeud * findPrevLinkedINFO(const char* ptrNick, const char* ptrSpecialite, const char* ptrFormation, const int experience){

  //La liste est vide
  if ((head==NULL)&&(queue==NULL)) return NULL;

  //Pointeur de navigation
  struct noeud * ptr = head;

  //Tant qu'un item suivant existe
  while (ptr->suivant!=NULL){

    //Est-ce le predecesseur de l'item recherche?
    if((strcmp(ptr->suivant->membre.ptrNick,ptrNick) == 0) && (strcmp(ptr->suivant->membre.ptrSpecialite,ptrSpecialite) == 0) ){

      //On retourne un pointeur sur l'item precedent
      return ptr;
    }

    //Deplacement du pointeur de navigation
    ptr=ptr->suivant;
  }

  //On retourne un pointeur NULL
  return NULL;
}

//#####################################################################
//#                                                                   #
//# Ajoute un item dans la liste chainee                              #
//#                                                                   #
//#####################################################################
void addItemLinkedINFO(const char* ptrNick, const char* ptrSpecialite, const char* ptrFormation, const int experience, const int socket, const int pid){


  //Creation de l'enregistrement en memoire
  struct noeud* ni = (struct noeud*)malloc(sizeof(struct noeud));


  //Affectation des valeurs des champs
  ni->membre.client_fd = socket;
  ni->membre.pid = pid;
  strcpy(ni->membre.ptrNick, ptrNick);
  strcpy(ni->membre.ptrSpecialite, ptrSpecialite);
  strcpy(ni->membre.ptrFormation, ptrFormation);
  ni->membre.experience = experience;

  if(sem_wait(&sem_list)==-1){
    fprintf(stderr, "semaphore failed : %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }

  if(head == NULL) // ajout au debut de la liste vide
    {
      //  premier noeud
      ni->suivant= NULL;
      queue = head = ni;

    }
  else  // ajout a la fin de la liste
    {
      struct noeud* tptr = queue;
      ni->suivant= NULL;
      queue = ni;
      tptr->suivant = ni;
    }

  if(sem_post(&sem_list)==-1){
    fprintf(stderr, "semaphore failed : %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }
}


//#####################################################################
//#                                                                   #
//# Retire un item de la liste chainee                                #
//#                                                                   #
//#####################################################################
void removeItemLinkedINFO(const char* ptrNick, const char* ptrSpecialite, const char* ptrFormation, const int experience){
  
  struct noeud * ptr;
  struct noeud * optr;

  if(sem_wait(&sem_list)==-1){
    fprintf(stderr, "semaphore failed : %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }

  //Verification sommaire liste non vide
   if ((head==NULL)&&(queue==NULL))
    return;

  //Pointeur de recherche
   if((strcmp(head->membre.ptrNick,ptrNick) == 0) && (strcmp(head->membre.ptrSpecialite,ptrSpecialite) == 0) ){
    ptr = head; // suppression du premier element de la liste
  }
  else{
    ptr = findPrevLinkedINFO(ptrNick,ptrSpecialite, ptrFormation, experience);
  }

  //Envoi d'une requete de fermeture de la fenetre reception
  struct_transac msg;
  sprintf(msg.transaction,"quit");
  write(ptr->membre.client_fd, &msg, sizeof(msg));

  //Item  trouve
  if (ptr!=NULL){

    // Memorisation du pointeur de l'item en cours de suppression
    // Ajustement des pointeurs
    if(head == ptr) // suppression de l'element de head
    {
		if(head==queue) // un seul element dans la liste
		{
			free(ptr);
			queue = head = NULL;
			return;
		}
		head = ptr->suivant;
		free(ptr);
    }
    else if (queue==ptr->suivant) // suppression de l'element de queue
    {
		queue=ptr;
		free(ptr->suivant);
		ptr->suivant=NULL;
		return;
    }
    else // suppression d'un element dans la liste
    {
		optr = ptr->suivant;
		ptr->suivant = ptr->suivant->suivant;
		free(optr);
    }
  }


  if(sem_post(&sem_list)==-1){
    fprintf(stderr, "semaphore failed : %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }
}

//#####################################################################
//#                                                                   #
//# Listage complet                                                   #
//#                                                                   #
//#####################################################################
void listItemsC(const int start, const int end, const int pid){
  if(sem_wait(&sem_list)==-1){
    fprintf(stderr, "semaphore failed : %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }
  struct noeud * client = head;
  while(client->membre.pid!=pid)
  {
    client = client->suivant;
  }
  //struct_fifo msg;
  struct_transac msg;
  int noentree=1;

  //Affichage des enheads de colonnes
  sprintf(msg.transaction,"========================================================");
  write(client->membre.client_fd, &msg, sizeof(msg));
  sprintf(msg.transaction,"=================LISTAGE COMPLET========================");
  write(client->membre.client_fd, &msg, sizeof(msg));
  sprintf(msg.transaction,"NICK		SPECIALITE	FORMATION     	EXPERIENCE   ");
  write(client->membre.client_fd, &msg, sizeof(msg));
  sprintf(msg.transaction,"========================================================");
  write(client->membre.client_fd, &msg, sizeof(msg));


  struct noeud * ptr = head;			//premier element

  while (ptr!=NULL){

    //L'item a un numero sequentiel dans l'interval defini
    if ((noentree>=start)&&(noentree<=end)){
      sprintf(msg.transaction,"%d: %s \t %s \t\t %s \t\t  %i",noentree,
	     ptr->membre.ptrNick,
	     ptr->membre.ptrSpecialite, 
	     ptr->membre.ptrFormation,
	     ptr->membre.experience);
       write(client->membre.client_fd, &msg, sizeof(msg));
    }
    if (noentree>end){
      //L'ensemble des items potentiels sont maintenant passes
      //Deplacement immediatement a� la FIN de la liste
      //Notez que le pointeur optr est toujours valide
      ptr=NULL;
    }
    else{
      ptr = ptr->suivant;
      noentree++;
    }
  }
  //Affichage des pieds de colonnes
  sprintf(msg.transaction,"========================================================");
  write(client->membre.client_fd, &msg, sizeof(msg));

  if(sem_post(&sem_list)==-1){
    fprintf(stderr, "semaphore failed : %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }
}

//#####################################################################
//#                                                                   #
//# Listage par specialité                                            #
//#                                                                   #
//#####################################################################
void listItemsS(const char* ptrSpecialite,const int pid){
  if(sem_wait(&sem_list)==-1){
    fprintf(stderr, "semaphore failed : %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }
  struct noeud * client = head;
  while(client->membre.pid!=pid)
  {
    client = client->suivant;
  }
  //struct_fifo msg;
  struct_transac msg;
  int noentree=1;

  //Affichage des enheads de colonnes
  sprintf(msg.transaction,"========================================================");
  write(client->membre.client_fd, &msg, sizeof(msg));
  sprintf(msg.transaction,"=================LISTAGE PAR SPECIALITE=================");
  write(client->membre.client_fd, &msg, sizeof(msg));
  sprintf(msg.transaction,"NICK		SPECIALITE	FORMATION     	EXPERIENCE   ");
  write(client->membre.client_fd, &msg, sizeof(msg));
  sprintf(msg.transaction,"========================================================");
  write(client->membre.client_fd, &msg, sizeof(msg));


  struct noeud * ptr = head;			//premier element

  while (ptr!=NULL){

		//L'item a un numero sequentiel dans l'interval defini
		if ((strcmp(ptr->membre.ptrSpecialite,ptrSpecialite) == 0)){
		  sprintf(msg.transaction,"%d: %s \t %s \t\t %s \t\t  %i",noentree,
		    ptr->membre.ptrNick,
		    ptr->membre.ptrSpecialite, 
		    ptr->membre.ptrFormation,
		    ptr->membre.experience);
		  write(client->membre.client_fd, &msg, sizeof(msg));
		  noentree++;
		}
			
		if(ptr->suivant != NULL){
		    ptr = ptr->suivant;		    
		}
		else{
		    ptr = NULL;
		}			
	}
  
  //Affichage des pieds de colonnes
  sprintf(msg.transaction,"========================================================");
  write(client->membre.client_fd, &msg, sizeof(msg));

  if(sem_post(&sem_list)==-1){
    fprintf(stderr, "semaphore failed : %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }
}

//#####################################################################
//#                                                                   #
//# Listage par specialité - expérience                               #
//#                                                                   #
//#####################################################################
void listItemsSE(const char* ptrSpecialite, const int start, const int end, const int pid){
  if(sem_wait(&sem_list)==-1){
    fprintf(stderr, "semaphore failed : %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }
  
  struct noeud * client = head;
  while(client->membre.pid!=pid)
  {
    client = client->suivant;
  }
  //struct_fifo msg;
  struct_transac msg;
  int noentree=1;

  //Affichage des enheads de colonnes
  sprintf(msg.transaction,"========================================================");
  write(client->membre.client_fd, &msg, sizeof(msg));
  sprintf(msg.transaction,"==============LISTAGE PAR SPECIALITE - EXPERIENCE==========");
  write(client->membre.client_fd, &msg, sizeof(msg));
  sprintf(msg.transaction,"NICK		SPECIALITE	FORMATION     	EXPERIENCE   ");
  write(client->membre.client_fd, &msg, sizeof(msg));
  sprintf(msg.transaction,"========================================================");
  write(client->membre.client_fd, &msg, sizeof(msg));


  struct noeud * ptr = head;			//premier element

  while (ptr!=NULL){

		//L'item a un numero sequentiel dans l'interval defini
		if ((strcmp(ptr->membre.ptrSpecialite,ptrSpecialite) == 0)&& ((ptr->membre.experience >= start) && (ptr->membre.experience <= end))){
		  sprintf(msg.transaction,"%d: %s \t %s \t\t %s \t\t  %i",noentree,
		    ptr->membre.ptrNick,
		    ptr->membre.ptrSpecialite, 
		    ptr->membre.ptrFormation,
		    ptr->membre.experience);
		  write(client->membre.client_fd, &msg, sizeof(msg));
		  noentree++;
		}
			
		if(ptr->suivant != NULL){
		    ptr = ptr->suivant;		    
		}
		else{
		    ptr = NULL;
		}			
	}
  
  //Affichage des pieds de colonnes
  sprintf(msg.transaction,"========================================================");
  write(client->membre.client_fd, &msg, sizeof(msg));

  if(sem_post(&sem_list)==-1){
    fprintf(stderr, "semaphore failed : %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }
}

//#####################################################################
//#                                                                   #
//# Listage par specialité - formation                                #
//#                                                                   #
//#####################################################################
void listItemsSF(const char* ptrSpecialite,const char* ptrFormation, const int pid){
  if(sem_wait(&sem_list)==-1){
    fprintf(stderr, "semaphore failed : %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }
  
  struct noeud * client = head;
  while(client->membre.pid!=pid)
  {
    client = client->suivant;
  }
  //struct_fifo msg;
  struct_transac msg;
  int noentree=1;

  //Affichage des enheads de colonnes
  sprintf(msg.transaction,"========================================================");
  write(client->membre.client_fd, &msg, sizeof(msg));
  sprintf(msg.transaction,"===========LISTAGE PAR SPECIALITE - FORMATION============");
  write(client->membre.client_fd, &msg, sizeof(msg));
  sprintf(msg.transaction,"NICK		SPECIALITE	FORMATION     	EXPERIENCE   ");
  write(client->membre.client_fd, &msg, sizeof(msg));
  sprintf(msg.transaction,"========================================================");
  write(client->membre.client_fd, &msg, sizeof(msg));



  struct noeud * ptr = head;			//premier element

  while (ptr!=NULL){

		//L'item a un numero sequentiel dans l'interval defini
		if ((strcmp(ptr->membre.ptrSpecialite,ptrSpecialite) == 0)&& (strcmp(ptr->membre.ptrFormation,ptrFormation) == 0)){
		  sprintf(msg.transaction,"%d: %s \t %s \t\t %s \t\t  %i",noentree,
		    ptr->membre.ptrNick,
		    ptr->membre.ptrSpecialite, 
		    ptr->membre.ptrFormation,
		    ptr->membre.experience);
		  write(client->membre.client_fd, &msg, sizeof(msg));
		  noentree++;
		}
			
		if(ptr->suivant != NULL){
		    ptr = ptr->suivant;		    
		}
		else{
		    ptr = NULL;
		}			
	}
 
  //Affichage des pieds de colonnes
  sprintf(msg.transaction,"========================================================");
  write(client->membre.client_fd, &msg, sizeof(msg));

  if(sem_post(&sem_list)==-1){
    fprintf(stderr, "semaphore failed : %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }
}


//#####################################################################
//#                                                                   #
//# Listage par specialité - formation - expérience                   #
//#                                                                   #
//#####################################################################
void listItemsSFE(const char* ptrSpecialite,const char* ptrFormation,const int start, const int end, const int pid){
  if(sem_wait(&sem_list)==-1){
    fprintf(stderr, "semaphore failed : %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }
  
  struct noeud * client = head;
  while(client->membre.pid!=pid)
  {
    client = client->suivant;
  }
  //struct_fifo msg;
  struct_transac msg;
  int noentree=1;

  //Affichage des enheads de colonnes
  sprintf(msg.transaction,"========================================================");
  write(client->membre.client_fd, &msg, sizeof(msg));
  sprintf(msg.transaction,"====LISTAGE PAR SPECIALITE - FORMATION - EXPERIENCE ====");
  write(client->membre.client_fd, &msg, sizeof(msg));
  sprintf(msg.transaction,"NICK		SPECIALITE	FORMATION     	EXPERIENCE   ");
  write(client->membre.client_fd, &msg, sizeof(msg));
  sprintf(msg.transaction,"========================================================");
  write(client->membre.client_fd, &msg, sizeof(msg));


  struct noeud * ptr = head;			//premier element

  while (ptr!=NULL){

		//L'item a un numero sequentiel dans l'interval defini
		if ((strcmp(ptr->membre.ptrSpecialite,ptrSpecialite) == 0)&& (strcmp(ptr->membre.ptrFormation,ptrFormation) == 0)&& (ptr->membre.experience >= start) && (ptr->membre.experience <= end)){
		  sprintf(msg.transaction,"%d: %s \t %s \t\t %s \t\t  %i",noentree,
		    ptr->membre.ptrNick,
		    ptr->membre.ptrSpecialite, 
		    ptr->membre.ptrFormation,
		    ptr->membre.experience);
		  write(client->membre.client_fd, &msg, sizeof(msg));
		  noentree++;
		}
			
		if(ptr->suivant != NULL){
		    ptr = ptr->suivant;		    
		}
		else{
		    ptr = NULL;
		}			
	}
  
  //Affichage des pieds de colonnes
  sprintf(msg.transaction,"========================================================");
  write(client->membre.client_fd, &msg, sizeof(msg));

  if(sem_post(&sem_list)==-1){
    fprintf(stderr, "semaphore failed : %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }
}

//#####################################################################
//#                                                                   #
//# Transmission d'un message aux membres d'un groupe                 #
//#                                                                   #
//#####################################################################
void transTextPG(const char* ptrNick, const char* ptrSpecialite,const char* ptrTexte){
  //struct_fifo msg;
  struct_transac msg;

	  if(sem_wait(&sem_list)==-1){
		fprintf(stderr, "semaphore failed : %s\n",strerror(errno));
		exit(EXIT_FAILURE);
	  }

	  struct noeud * ptr = head;			//premier element

	  sprintf(msg.transaction,"(group %s) %s : %s\n", ptrSpecialite, ptrNick, ptrTexte);

	  while (ptr!=NULL){
		if(strcmp(ptr->membre.ptrSpecialite,ptrSpecialite) == 0)
		  {
			write(ptr->membre.client_fd, &msg, sizeof(msg));
		  }
		ptr = ptr->suivant;

	  }

	  if(sem_post(&sem_list)==-1){
		fprintf(stderr, "semaphore failed : %s\n",strerror(errno));
		exit(EXIT_FAILURE);
	  }


}

void transTextPP(const char* ptrNick1, const char* ptrNick2, const char* ptrTexte){
  struct_transac msg;

	  if(sem_wait(&sem_list)==-1){
		fprintf(stderr, "semaphore failed : %s\n",strerror(errno));
		exit(EXIT_FAILURE);
	  }

	  struct noeud * ptr = head;			//premier element


	  sprintf(msg.transaction,"(private) %s : %s\n",ptrNick1,ptrTexte);

	  while (ptr!=NULL){
		if(strcmp(ptr->membre.ptrNick,ptrNick2) == 0)
		  {

			write(ptr->membre.client_fd, &msg, sizeof(msg));

		  }
		ptr = ptr->suivant;

	  }

	  if(sem_post(&sem_list)==-1){
		fprintf(stderr, "semaphore failed : %s\n",strerror(errno));
		exit(EXIT_FAILURE);
	  }


}
