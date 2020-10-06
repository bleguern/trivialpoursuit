/********************************************************/
/* Trivial Poursuit v1.0a By GummiTeam!                 */
/* camera.h : Contient les m�thodes n�cessaires �       */
/* la gestion de la cam�ra.                             */
/********************************************************/


#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <math.h>
#include "3Dmath.h"
#include "mouse.h"
#include "config.h"


//Constantes de mouvement
#define ZOOM_IN      0
#define ZOOM_OUT     1

#define MOVE_UP      0
#define MOVE_DOWN    1
#define MOVE_RIGHT   2
#define MOVE_LEFT    3


class Camera
{
	GLfloat speed;            //Vitesse de mouvement

public:
	Vector3 position;         //D�fini la position de la cam�ra

	GLfloat x_angle;          //D�fini l'angle de rotation sur l'axe de x
	GLfloat z_angle;          //D�fini l'angle de rotation sur l'axe de z

	GLfloat distance;         //D�fini la distance par rapport au point fix� (centre du plateau)

	//Constructeur/Destructeur
	Camera():position(0.0f, 0.1f, 0.0f),x_angle(30.0f),z_angle(0.0f),distance(199.9f),speed(1.05f) {}
	~Camera() {}


	void Move(unsigned int);        	//Bouge la cam�ra
	void MoveAround(unsigned int);      //Effectue un rotaion de la cam�ra

	void MouseMove(Config&, Mouse&);    //Bouge la cam�ra avec la souris
};



#endif