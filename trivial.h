/********************************************************/
/* Trivial Poursuit v1.0a By GummiTeam!                 */
/* trivial.h : Inclut les .h principaux et les m�thodes */
/* principales du programme.                            */
/********************************************************/

#ifndef _TRIVIAL_H_
#define _TRIVIAL_H_

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glaux.lib")


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>

#include "resource.h"


//D�fini les constantes TRUE et FALSE
#define TRUE                          1
#define FALSE                         0


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);       //Fonction principale
WPARAM MainLoop();                                          //Boucle de jeu
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);       //Proc�dure de programme
LRESULT CALLBACK InitProc(HWND, UINT, WPARAM, LPARAM);      //Proc�dure de la boite de dialogue initiale
void SetupPixelFormat(HDC);                                 //D�fini le format de pixel

#endif