/********************************************************/
/* Trivial Poursuit v1.0a By GummiTeam!                 */
/* camera.cpp : Contient les méthodes nécessaires à     */
/* la gestion de la caméra.                             */
/********************************************************/


#include "camera.h"

//Bouge la caméra en fonction de la souris
void Camera::MouseMove(Config& config, Mouse& mouse)
{
	POINT tmp_mouse;
	Vector3 tmp_vector;
	WINDOWPLACEMENT tmp_wnd_pl;

	float delta_x = 0.0f;
	float delta_y = 0.0f;

	GetCursorPos(&tmp_mouse);
	GetWindowPlacement(config.hWnd, &tmp_wnd_pl);

	tmp_mouse.x -= tmp_wnd_pl.rcNormalPosition.left + WINDOW_WIDTH_DELTA;
	tmp_mouse.y -= tmp_wnd_pl.rcNormalPosition.top + WINDOW_HEIGHT_DELTA;

	if((mouse.x == tmp_mouse.x) && (mouse.y == tmp_mouse.y)) 
		return;

	SetCursorPos(tmp_wnd_pl.rcNormalPosition.left + WINDOW_WIDTH_DELTA + mouse.x, 
		tmp_wnd_pl.rcNormalPosition.top + WINDOW_HEIGHT_DELTA + mouse.y);

	delta_x = (float)((tmp_mouse.x - mouse.x)) / 40;
	delta_y = (float)((tmp_mouse.y - mouse.y)) / 40;

	if(delta_x < 0)
	{
		if(z_angle < (360.0f-delta_x))
		{
			z_angle += delta_x;
		}
		else
		{
			z_angle = 0.0f;
		}
	}
	else
	{
		if(z_angle > (-360.0f-delta_x))
		{
			z_angle += delta_x;
		}
		else
		{
			z_angle = 0.0f;
		}
	}

	if(delta_y < 0)
	{
		if(x_angle > (0.0f-delta_y))
		{
			x_angle += delta_y;
		}
		else
		{
			x_angle = 0.0f;
		}
	}
	else
	{
		if(x_angle < (90.0f-delta_y))
		{
			x_angle += delta_y;
		}
		else
		{
			x_angle = 90.0f;
		}
	}
}




//Bouge la caméra
void Camera::Move(unsigned int dir)
{
	switch(dir)
	{
	case ZOOM_OUT:
		distance *= speed;
		break;
	case ZOOM_IN:
		distance /= speed;
		break;
	default:
		break;
	}
}

//Tourne la caméra autour d'un point
void Camera::MoveAround(unsigned int dir)
{
	switch(dir)
	{
	case MOVE_UP:
		if(x_angle < (90.0f-speed))
		{
			x_angle += 2*speed;
		}
		else
		{
			x_angle = 90.0f;
		}
		break;
	case MOVE_DOWN:
		if(x_angle > (0.0f+speed))
		{
			x_angle -= 2*speed;
		}
		else
		{
			x_angle = 0.0f;
		}
		break;
	case MOVE_RIGHT:
		if(z_angle < (360.0f-speed))
		{
			z_angle += 3*speed;
		}
		else
		{
			z_angle = 0.0f;
		}
		break;
	case MOVE_LEFT:
		if(z_angle > (-360.0f+speed))
		{
			z_angle -= 3*speed;
		}
		else
		{
			z_angle = 0.0f;
		}
		break;
	default:
		break;
	}
}
