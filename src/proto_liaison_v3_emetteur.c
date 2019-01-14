/*********************************************
 * protocole_liaison_02 - côté émetteur      * 
 *                                           *
 *********************************************/

#include <stdio.h>
#include "application.h"
#include "services_liaison.h"
#include "couche_liaison.h"
#include "services_physique.h"

/* =============================== */
/* Programme principal - émetteur  */
/* =============================== */
int main(int argc, char* argv[])
{
	char message[MTU];     /* message de l'application */
	int taille_msg;        /* taille du message */
	int service_liaison;   /* service de la couche liaison invoqué par appli */
	trame_t trame;         /* trame utilisée par le protocole liaison */
	int num_seq_actuelle;  /* numero de sequence en cours de traitement */
	int i;


	init_physique(EMISSION);

	printf("[DL] Initialisation physique : OK.\n");
	printf("[DL] Debut execution protocole liaison.\n");
	taille_msg = 1;
	trame.num_seq = 0; /* init numero sequence */
	while (taille_msg != 0){
		de_application(&service_liaison, message, &taille_msg);
		trame.fcs = generer_controle(trame);
		/* lecture primitive de service */
		if (service_liaison == L_UNIT_DATA_req) {
			for (i = 0; i < taille_msg; i++){
				trame.info[i] = message[i];
			}
			inc(&trame);
			trame.type = DATA;
			trame.lg_info = taille_msg;
			trame.fcs = generer_controle(trame);
			num_seq_actuelle = trame.num_seq;
			while (trame.type != ACK && trame.num_seq == num_seq_actuelle ){
				vers_canal(&trame);
				depart_temporisateur(1,200);
				while( attendre() != 0 ){
					vers_canal(&trame);
					depart_temporisateur(1,200);	
				}
				vers_canal(&trame);


			}


			/*
			de_canal(&trame);

			while (trame.type != ACK || trame.num_seq == ){
				attendre();
				vers_canal(&trame);
			}*/
		}

		else {
			printf("[DL] Service liaison inconnu !\n");
		}

	}
	printf("[DL] Fin execution protocole liaison.\n");
	return 0;
}

