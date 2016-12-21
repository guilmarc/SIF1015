

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>

#include "../../server/src/gestionListeChaineeLinkedINFO.h"


int row, col;
WINDOW* fenetre;
WINDOW* fenetre_trans;
WINDOW* fenetre_recp;

char* ptrNick;
char* ptrNick2;
char* ptrSpecialite;
char* ptrFormation;
char* strExperience;
int Experience;
struct Info_Transaction my_data;


int sockfd;


void init_client(void){
  
  int len;
  struct sockaddr_un address;
  
  
  //Création de la socket
  sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
  //Identification de la socket
  address.sun_family = AF_UNIX;
  strcpy(address.sun_path, SERVER_NAME_TRANSACTION);
  len = sizeof(address);
  //Connection de la socket
  if(connect(sockfd, (struct sockaddr *)&address, len) == -1) {
  	fprintf(stderr, "Error - connection impossible\n");
    exit(1);
  }
  
}


void init_screen(void){
	initscr();
	keypad(fenetre,TRUE);
	getmaxyx(stdscr,row,col);

	//Initialisation des couleur
	if(!has_colors()){
		endwin();
		fprintf(stderr, "Error - no color support on this terminal\n");
		exit(1);
	}
	if(start_color() != OK){
		endwin();
		fprintf(stderr, "Error - could not initialize colors\n");
		exit(2);
	}
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
}

void screen_ID(void){
	char msg[200];

	//Création de la fenetre d'identification'
	fenetre = newwin(nb_ligne,nb_colonne,0,(col-nb_colonne)/2);
	box(fenetre,ls,bs);
	mvwaddstr(fenetre,5,(nb_colonne-20)/2,"Nick : ");
	mvwaddstr(fenetre,7,(nb_colonne-20)/2,"Specialite :");
	mvwaddstr(fenetre,9,(nb_colonne-20)/2,"Formation :");
	mvwaddstr(fenetre,11,(nb_colonne-20)/2,"Annees d experience :");
	wrefresh(fenetre);
	ptrNick = (char*)malloc(size);
	ptrSpecialite = (char*)malloc(size);
	ptrFormation= (char*)malloc(size);
	strExperience = (char*)malloc(size);
	mvwgetstr(fenetre,6,(nb_colonne-20)/2,ptrNick);
	mvwgetstr(fenetre,8,(nb_colonne-20)/2,ptrSpecialite);
	mvwgetstr(fenetre,10,(nb_colonne-20)/2,ptrFormation);
	mvwgetstr(fenetre,12,(nb_colonne-20)/2,strExperience);
	Experience = atoi(strExperience);

	
	init_client();

	//Creation de la requete
	sprintf(msg,"A %s %s %s %s\n",ptrNick,ptrSpecialite,ptrFormation,strExperience);
	//Envoi de la requete
	strcpy(my_data.transaction, msg);
	my_data.pid_client = getpid();
	
	//Envoi de la requete
	write(sockfd, &my_data, sizeof(my_data));
    
	delwin(fenetre);
}

void screen_transmit(void){
	char* msg;
	fenetre_trans = newwin(nb_ligne,col/2,0,0);
	box(fenetre_trans,ls,bs);
	scrollok(fenetre_trans,TRUE);
	wattrset(fenetre_trans,COLOR_PAIR(1));
	msg = "TRANSMISSION";
	mvwaddstr(fenetre_trans,0,col/4-strlen(msg)/2,msg);
	wrefresh(fenetre_trans);


}

int IsListif(char msg[]){
	char temp[200];
	strcpy(temp,msg);
	if(strcmp(strtok(temp," "),"L")!=0) return 0;
	return 1;
}


void* transmit_msg(void* arg){
	char msg [400];
	char msg_titre [200];
	char msg_bis[400];

	int i =1;
	sprintf(msg_titre,"%s %s : ",ptrNick,ptrSpecialite);

	while(strcmp(msg,"quit") != 0 && strcmp(msg,"QUIT") != 0){
		mvwaddstr(fenetre_trans,i,3,msg_titre);
		wrefresh(fenetre_trans);
		mvwgetstr(fenetre_trans,i,strlen(msg_titre)+3,msg);
		i++;
		if(strcmp(msg,"quit") != 0 && strcmp(msg,"QUIT") != 0){

			switch(msg[0]){
			
			
			case 'L':{
				if(!IsListif(msg)) goto standard;
			  //Creation de la requete de listification
			  strcpy(my_data.transaction, msg);
			  break;
			}
			
			case 'T':{
			  memmove(msg, msg+2,strlen(msg));

			  if (strncmp(msg,"PP",2)==0){
			    memmove(msg, msg+3,strlen(msg));
			    sprintf(msg_bis,"T PP %s\n", msg);
			    strcpy(my_data.transaction, msg_bis);
			   }
			   else if (strncmp(msg,"PG",2)==0){
			    memmove(msg, msg+3,strlen(msg));
			    sprintf(msg_bis,"T PG %s\n", msg);
			    strcpy(my_data.transaction, msg_bis);
			   }
			   else goto standard;
 			  break;
			}

			standard:
			default:{
			  //Creation de la requete de transmission
			  sprintf(msg_bis,"T PG %s %s %s\n",ptrNick,ptrSpecialite,msg);
			  strcpy(my_data.transaction, msg_bis);
			  break;

			}
		}
		//Envoi de la requete
    	write(sockfd, &my_data, sizeof(my_data));
    	strcpy(msg," ");
		}
	}

	//Creation de la requete de suppression
	sprintf(msg,"E %s %s %s %s\n",ptrNick,ptrSpecialite,ptrFormation,strExperience);

	//Envoi de la requete
	strcpy(my_data.transaction, msg);
    write(sockfd, &my_data, sizeof(my_data));

	//Liberation des ressource
    close(sockfd);
	free(ptrSpecialite);
	free(ptrNick);
	free(ptrFormation);
	free(strExperience);
	pthread_exit(0);
}

void* receiv_msg(void* arg){
	struct_transac msg_receiv;
	int read_res;
	
	int i=1;
	
	int socket_receiv;
	int len;
	struct sockaddr_un address;
  
	//Création de la socket
  socket_receiv = socket(AF_UNIX, SOCK_STREAM, 0);
  //Identification de la socket
  address.sun_family = AF_UNIX;
  strcpy(address.sun_path, SERVER_NAME_COMMUNICATION);
  len = sizeof(address);
  //Connection de la socket
  if(connect(socket_receiv, (struct sockaddr *)&address, len) == -1) {
  	fprintf(stderr, "Error - connection impossible\n");
    exit(1);
  }
	do{
		read_res = read(socket_receiv, &msg_receiv, sizeof(msg_receiv));
		if (read_res > 0) {
			mvwaddstr(fenetre_recp,i,3,msg_receiv.transaction);
			wrefresh(fenetre_recp);
			i++;
		}
	}while (strcmp(msg_receiv.transaction,"quit")!=0 && strcmp(msg_receiv.transaction,"QUIT")!=0);
	close(socket_receiv);
	pthread_exit(0);
}

//Fonction pour créer la fenetre de reception 
void screen_reception(void){
	char* msg;
	fenetre_recp  = newwin(nb_ligne,col/2,0,col/2);
	box(fenetre_recp,ls,bs);
	scrollok(fenetre_recp,TRUE);

	wattrset(fenetre_recp,COLOR_PAIR(2));
	msg = "RECEPTION";
	mvwaddstr(fenetre_recp,0,col/4-strlen(msg)/2,msg);
	wrefresh(fenetre_recp);
}

//Fonction fermant les fenetres de reception et de transmission
void end_screen(void){
	delwin(fenetre_trans);
	delwin(fenetre_recp);
	endwin();
}
