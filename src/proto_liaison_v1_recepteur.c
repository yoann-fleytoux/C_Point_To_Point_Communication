/*********************************************
 * protocole_liaison_01 - côté récepteur     * 
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
	int taille_msg;         /* taille du message */
	trame_t trame;          /* trame utilisée par le protocole liaison */
	int i, fin;

	init_physique(RECEPTION);

	printf("[DL] Initialisation physique : OK.\n");
	printf("[DL] Debut execution protocole liaison.\n");
	/* récupération d'une trame de la couche physique */
	do {
		de_canal(&trame);
		taille_msg = trame.lg_info;
		for (i = 0; i < trame.lg_info; i++){
			message[i] = trame.info[i];
		}
		fin = vers_application(L_UNIT_DATA_ind, message, trame.lg_info);
	} while (fin == 0);
	printf("[DL] Fin execution protocole liaison.\n");
	return 0;
}

