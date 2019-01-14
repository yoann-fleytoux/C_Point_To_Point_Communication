/*********************************************
 * protocole_liaison_02 - côté récepteur     * 
 *                                           *
 *********************************************/
 
#include <stdio.h>
#include "application.h"
#include "services_liaison.h"
#include "couche_liaison.h"
#include "services_physique.h"

/* =============================== */ 
/* Programme principal - récepteur */
/* =============================== */
int main(int argc, char* argv[])
{
	char message[MTU];      /* message de l'application */
	char ctrl;				/* somme de controle */
	int taille_msg;         /* taille du message */
	trame_t trame;          /* trame utilisée par le protocole liaison */
	int num_seq_actuelle;	/* numero de sequence en cours de traitement */
	int i, fin;

	init_physique(RECEPTION);
	
	printf("[DL] Initialisation physique : OK.\n");
	printf("[DL] Debut execution protocole liaison.\n");
	/* récupération d'une trame de la couche physique */
	num_seq_actuelle = 1;
	do {
		de_canal(&trame);
		if (verifier_controle(trame)) {
			if (trame.num_seq != num_seq_actuelle) {
				printf("[DL] DUP! \n" );
				trame.num_seq = num_seq_actuelle;
				trame.type = ACK;
				trame.lg_info = 0;
				vers_canal(&trame);
			} else {
				taille_msg = trame.lg_info;
				for (i = 0; i < trame.lg_info; i++){
					message[i] = trame.info[i];
				}
				fin = vers_application(L_UNIT_DATA_ind, message, trame.lg_info);
				trame.type = ACK;
				trame.lg_info = 0;
				inc(&trame);
				vers_canal(&trame);
			}
		} else {
			printf("[DL] error checksum \n");
		}	
	} while (fin == 0);
	printf("[DL] Fin execution protocole liaison.\n");
	return 0;
}
