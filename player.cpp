/********************************************************/
/* Trivial Poursuit v1.0a By GummiTeam!                 */
/* player.cpp : Contient les m�thodes n�cessaires �     */
/* la gestion des joueurs.                              */
/********************************************************/

#include "player.h"



//Retourne le r�sultat d'un lanc� de d�
void Player::LaunchTheDie()
{
	hit = 1 + (rand()%6);
}
