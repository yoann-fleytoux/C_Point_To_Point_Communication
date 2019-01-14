#include <stdio.h>
#include "couche_liaison.h"
#include "services_physique.h"


/* Ajouter ici des fonctions utilitaires
 * (generer_controle, verifier_controle, connexion,...)
 */
 

 char generer_controle(trame_t trame) {
	char XOR;
	int i;

	XOR = trame.type ^ trame.num_seq ^ trame.lg_info;

	for (i = 0; i < trame.lg_info; ++i){
		XOR ^= trame.info[i];
	}

	return (XOR);
}



int verifier_controle(trame_t trame) {
	return (generer_controle(trame) == trame.fcs);
}


void inc(trame_t *trame){
	trame->num_seq = ((++trame->num_seq) % 2);
}