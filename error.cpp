/********************************************************/
/* Trivial Poursuit v1.0a By GummiTeam!                 */
/* error.cpp : Contient les méthodes nécessaires à      */
/* l'affichage des erreurs du programme.                */
/********************************************************/

#include "Error.h"


//Affiche une erreur
void Error(HWND hWnd, const char* str_error)
{
	MessageBox(hWnd, str_error, "Trivial Poursuit : Error", MB_ICONERROR | MB_OK);
}

//Enregistre un warning
bool Warning(const char* str_warning, int str_warning_lenght)
{
	FILE *fd;

	if((fd = fopen(WARNING_FILE, "a")) == NULL)
	{
		return FALSE;
	}

	fwrite(str_warning, sizeof(char), str_warning_lenght-1, fd);

	fclose(fd);

	return TRUE;
}