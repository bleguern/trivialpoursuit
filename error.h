/********************************************************/
/* Trivial Poursuit v1.0a By GummiTeam!                 */
/* error.h : Contient les méthodes nécessaires à        */
/* l'affichage des erreurs du programme.                */
/********************************************************/

#ifndef _ERROR_H_
#define _ERROR_H_


#include "trivial.h"

//Défini le chemin du fichier pour suavegarder les "warning"
#define WARNING_FILE                 "warning.txt"


void Error(HWND, const char*);             //Affiche une erreur
bool Warning(const char*, int);            //Sauvegarde un "warning"



#endif