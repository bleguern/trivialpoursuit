/********************************************************/
/* Trivial Poursuit v1.0a By GummiTeam!                 */
/* mouse.h : Contient la classe nécessaire à la gestion */
/* de la souris.                                        */
/********************************************************/


#ifndef _MOUSE_H_
#define _MOUSE_H_

#include "trivial.h"

//Classe pour la gestion de la souris
class Mouse
{
public:
	int x, y;                  //Position sur les x et y
	bool r_click, l_click;     //Clic droit et gauche
};

#endif