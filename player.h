/********************************************************/
/* Trivial Poursuit v1.0a By GummiTeam!                 */
/* player.h : Contient les méthodes nécessaires à       */
/* la gestion des joueurs.                              */
/********************************************************/

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "trivial.h"
#include "3Dmath.h"


#define MAX_NAME_LENGTH     20         //Taille maximum des noms
#define MAX_CAMEMBERS        6         //Maximum de camembers
#define MAX_PLAYERS          6         //Maximum de joueur


//Défini la classe pour la gestion des joueurs
class Player
{
public:
	unsigned int hit;                    //Coup effectué
	unsigned int square_pos;             //Position sur le plateau
	char name[MAX_NAME_LENGTH];          //Nom du joueur
	
	bool camember[MAX_CAMEMBERS];        //Camembers en possession
	unsigned int choice;                 //Choix de la response
	bool answer;                         //Bonne ou mauvaise réponse

	//Constructeur/Destructeur
	Player():hit(0),square_pos(1),choice(0),answer(FALSE)
	{
		int i;
		strcpy(name,"Noname");
		
		for(i = 0; i < 6; i++)
		{
			camember[i] = FALSE;
		}
	}
	~Player() {}

	void LaunchTheDie();                 //Lance le dé
};


#endif

