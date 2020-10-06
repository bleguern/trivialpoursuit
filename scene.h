/********************************************************/
/* Trivial Poursuit v1.0a By GummiTeam!                 */
/* scene.h : Contient les m�thodes n�cessaires �        */
/* la gestion de l'affichage de la sc�ne.               */
/********************************************************/

#ifndef _SCENE_H_
#define _SCENE_H_

#include "config.h"
#include "camera.h"
#include "mouse.h"
#include "error.h"

#include "3Dobject.h"
#include "board.h"


//Le nombre maximal de lettre pour les quesitons et r�ponses
#define MAX_CHARS                   256

//Taille de la police
#define FONT_HEIGHT                 50

//Maximum de questions
#define MAX_QUESTIONS               100

//D�fini les chemins pour les questions et r�ponses
#define ORANGE_QUESTION_FILE_PATH   "data//_qcmz//orange.tri"
#define GREEN_QUESTION_FILE_PATH    "data//_qcmz//green.tri"
#define BROWN_QUESTION_FILE_PATH    "data//_qcmz//brown.tri"
#define PINK_QUESTION_FILE_PATH     "data//_qcmz//pink.tri"
#define YELLOW_QUESTION_FILE_PATH   "data//_qcmz//yellow.tri"
#define BLUE_QUESTION_FILE_PATH     "data//_qcmz//blue.tri"


//D�fini la structure pour les QCM : question et r�ponses
typedef struct
{
	char question[MAX_CHARS];
	char answer[4][MAX_CHARS];
	unsigned int good_answer;
}QCM;


//La classe scene
class Scene
{
	//Handle pour la police
	HFONT hOldFont;

	//Sauvegarde les questions deja pos�es
	bool answered_question[6][MAX_QUESTIONS];

	//Listes d'affichages pour les lettres et les objets
	unsigned int font_list;
	unsigned int display_list;

	//D� (objet textur�)
	TexturedObject die;
	//Autres objets
	Object ground, pawn, camember;

	//Questions
	QCM qcm;

	//Variable pour le compte � rebour
	time_t last_time;
	time_t elapsed_time;

	//D�fini un joueur au hasard
	unsigned int random_player;

	float delta;       //Variable pour le d�placement du d�
	bool die_anim;     //Pour l'animation ou non du d�

public:

	//Plateau
	Board board;

	//Sc�ne charg�e
	bool loaded;

	//Camera
	Camera camera;

	//Constructeur/Destructeur
	Scene():delta(0.0f),die_anim(FALSE),loaded(FALSE),random_player(0) {}
	~Scene() {}

	bool Load(Config&);                                       //Charge la sc�ne
	bool LoadFont(Config&);                                   //Charge les polices
	bool LoadObject(Config&);                                 //Charge les objets

	void Draw(Config&, Mouse&);                               //Dessine la sc�ne
	void DrawBoard(Config&);                                  //Dessine le plateau
	void DrawPawn(Config&);                                   //Dessine les pions
	void DrawCamember(Config&);                               //Dessine les camembers
	void DrawDie(Config&);                                    //Dessine le d�

	void DrawHUD(Config&, Mouse&);                            //Dessine l'affichage
	void glDrawText(Config&, int, int, const char*, ...);     //Dessine du texte

	void DrawHUDDieThrow(Config&, Mouse&);
	void DrawHUDPosition(Config&, Mouse&);
	void DrawHUDQuestion(Config&, Mouse&);
	void DrawHUDAnswer(Config&, Mouse&);
	void DrawHUDChooseQuestionColor(Config&, Mouse&);
	void DrawHUDEnd(Config&, Mouse&);
	void DrawHUDDieAnim(Config&, Mouse&);
	
	int GetSelected(Config&, Mouse&);                         //Retourne l'objet s�lectionn�
	bool SetPos(unsigned int);                                //D�fini la position

	bool GetQuestion(unsigned int);                           //Retourne la question et les r�ponses
};


#endif