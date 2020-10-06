/********************************************************/
/* Trivial Poursuit v1.0a By GummiTeam!                 */
/* player.cpp : Contient les méthodes nécessaires à     */
/* la gestion des joueurs.                              */
/********************************************************/

#include "player.h"



//Retourne le résultat d'un lancé de dé
void Player::LaunchTheDie()
{
	hit = 1 + (rand()%6);
}
