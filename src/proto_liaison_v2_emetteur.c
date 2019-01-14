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
	int i;

	init_physique(EMISSION);

	printf("[DL] Initialisation physique : OK.\n");
	printf("[DL] Debut execution protocole liaison.\n");
	taille_msg = 1;
	while (taille_msg != 0){
		de_application(&service_liaison, message, &taille_msg);
			
		/* lecture primitive de service */
		if (service_liaison == L_UNIT_DATA_req) {
			for (i = 0; i < taille_msg; i++){
				trame.info[i] = message[i];
			}
			trame.lg_info = taille_msg;
			vers_canal(&trame);
			de_canal(&trame);
			while (trame.type != ACK){
				attendre();
				vers_canal(&trame);
			}
		}
		else {
			printf("[DL] Service liaison inconnu !\n");
		}
	}
	printf("[DL] Fin execution protocole liaison.\n");
	return 0;
}

