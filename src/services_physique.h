/************************************************************
 *      Simulation d'une couche PHYSIQUE                    * 
 *                                                          *
 * (v 1.3)                                                  *
 * P. Torguet & E. Lavinal                                  *
 * Université de Toulouse III - Paul Sabatier               *
 ************************************************************/

#ifndef __PHYSIQUE_H__
#define __PHYSIQUE_H__

#include "couche_liaison.h" /* trame_t */

/* pour init_physique() */
#define EMISSION  0
#define RECEPTION 1

/* pour attendre() */
#define TRAME_RECUE 0

/* ============================== */
/* Initialisation couche physique */
/* ============================== */

/************************************************************ 
 * Initialisation de le couche physique. Le paramètre rôle  *
 * doit être égal à 1 pour la réception, 0 pour l'émission. * 
 ************************************************************/
void init_physique(int role);

/************************************************************************
 * Initialisation de le couche physique en mode "réparti".              *
 * (c'est-à-dire, emetteur et recepteur sur machines distinctes)        *
 * Paramètres :                                                         *
 *    rôle : doit être égal à 1 pour la réception, 0 pour l'émission.   *
 *    port_local : port "transport" local                               *
 *    hote_distant : @ IP du destinataire (l'emetteur ou le récepteur)  *
 *    port_distant : port "transport" du destinataire (idem E ou R)     *
 ************************************************************************/
void init_physique_mode_reparti(int role, unsigned short port_local,
	char* hote_distant, unsigned short port_distant);


/* ============================================================= */
/* Primitives de service pour émission et réception sur le canal */
/* ============================================================= */

/**********************************************************
 * Remet une trame à la couche physique pour émission     *
 * sur le support de communication.                       *
 **********************************************************/
void vers_canal(trame_t *trame);

/*************************************************************
 * Prélève une trame de la couche physique (N.B. : fonction  *
 * bloquante tant qu'une trame n'est pas reçue).             *
 *************************************************************/
void de_canal(trame_t *trame);

/* =============================================== */
/* Fonctions utilitaires pour la gestion de timers */
/* =============================================== */

/***************************************************************
 * Démarre le timer numero n (0 < n < 100) qui s'arrête après  *
 * ms millisecondes (ms doit être un multiple de 100)          *
 ***************************************************************/
void depart_temporisateur(int n, int ms);

/*******************************************
 * Arrête le timer numéro n (0 < n < 100)  *
 *******************************************/
void arreter_temporisateur(int n);


/**********************************************************
 * Test si le timer numéro n (0 < n < 100) est en marche  *
 * Renvoie :  1 si le timer numéro n est en route         *
 *            0 sinon                                     *
 **********************************************************/
int test_temporisateur(int n);


/*********************************************************************
 * Fonction qui attend un évènement (trame reçue ou timeout).        *
 * (N.B. : fonction bloquante)                                       *
 * Renvoie :  0 si une trame reçue est disponible,                   *
 *            un numéro de timer (1-100) si un timeout a été généré  *
 *********************************************************************/
int attendre();

#endif
