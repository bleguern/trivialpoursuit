/********************************************************/
/* Trivial Poursuit v1.0a By GummiTeam!                 */
/* config.h : Contient les méthodes nécessaires à       */
/* la configuration du programme.                       */
/********************************************************/

#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "error.h"
#include "player.h"
#include "3Dmath.h"

//Défini le chemin du fichier de config
#define CONFIG_FILE                         "config.ini"

//Status de jeu
#define GAME_STATUS_DIE_THROW	            0
#define GAME_STATUS_POSITION                1
#define GAME_STATUS_QUESTION                2
#define GAME_STATUS_ANSWER                  3
#define GAME_STATUS_CHOOSE_QUESTION_COLOR   4
#define GAME_STATUS_END                     5
#define GAME_STATUS_DIE_ANIM                6

//Pour la gestion de la fenêtre
#define WINDOW_HEIGHT_DELTA                31
#define WINDOW_WIDTH_DELTA                  5

//Les différentes couleurs
#define ORANGE                              1
#define GREEN                               2
#define BROWN                               3
#define PINK                                4
#define YELLOW                              5
#define BLUE                                6

//Classe de configuration du programme
class Config
{
public:

	//Variables pour les graphismes
	unsigned int screen_width;
	unsigned int screen_height;
	unsigned int screen_bpp;
	bool fullscreen;

	float coef_x;
	float coef_y;

	bool gouraud_shading;

	GLfloat view_depth;

	//Variables pour les joueurs
	unsigned int nb_players;
	Player players[MAX_PLAYERS];

	//Variables de jeu
	unsigned int active_player;
	unsigned int game_status;
	unsigned int sec_to_answer;

	HWND hWnd;
	HDC hDC;
	HGLRC hRC;
	HINSTANCE hInstance;
	MSG uMsg;
	WNDCLASSEX hWC;
	DWORD dwStyle;
	int nCmdShow;

	//Constructeur/Destructeur
	Config():screen_width(640),screen_height(480),screen_bpp(16),fullscreen(FALSE),
		gouraud_shading(TRUE),
		nb_players(2),active_player(0),game_status(GAME_STATUS_DIE_THROW),sec_to_answer(30),view_depth(10000.0f),
		hWnd(NULL),hDC(NULL),hRC(NULL),hInstance(NULL),dwStyle(NULL) {}
	~Config() {}

	void LoadDefault();        //Charge les options par défaut
	
	bool Init();               //Initialise la config
	
	bool Launch();             //Lance le jeu
	
	bool Save();               //Sauvegarde la config
	
	void Quit();               //Quitte le programme

	bool Init_GL();            //Initialise l'affichage
	void SizeOpenGLScreen();   //Initialise la fenêtre
	bool ChangeToFullScreen(); //Change pour un mode plein écran
};



#endif