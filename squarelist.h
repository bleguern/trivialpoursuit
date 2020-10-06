/********************************************************/
/* Trivial Poursuit v1.0a By GummiTeam!                 */
/* squarelist.h : Contient les méthodes nécessaires à   */
/* la gestion du plateau.                               */
/********************************************************/

#ifndef _SQUARELIST_H_
#define _SQUARELIST_H_

#include "config.h"

//Le nombre maximum de possitions possibles
#define MAX_POSSIBLE_POSITIONS           7


//Les différents types de case
#define TYPE_NORMAL_SQUARE               0
#define TYPE_CENTER                      1
#define TYPE_REPLAY                      2
#define TYPE_CAMEMBER                    3

//Résultat : cases possibles
typedef struct
{
	unsigned int *result;
	unsigned int nb;
}SquareResult;

//Case
class Square
{
public:
	unsigned int id;           //Id : numéro

	unsigned int type;         //Type de case
	unsigned int color;        //Couleur de la case

	Square* link[6];           //Liens (liste chainee)

	//Constructeur/Destructeur
	Square():id(0),type(TYPE_NORMAL_SQUARE),color(NULL)
	{
		unsigned int i;

		for(i = 0; i < 6; i++)
		{
			link[i] = NULL;
		}
	}
	~Square() {}

	//Initialise une case
	void Set(unsigned int Id,
		     Square *link0 = NULL,
		     Square *link1 = NULL,
		     Square *link2 = NULL,
		     Square *link3 = NULL,
		     Square *link4 = NULL,
		     Square *link5 = NULL)
	{
		id = Id;
		link[0] = link0;
		link[1] = link1;
		link[2] = link2;
		link[3] = link3;
		link[4] = link4;
		link[5] = link5;
	}
};



//Plateau : liste chainée de cases
class SquareList
{
	Square* square;                    //Ensemble des cases

public:
	//Constructeur/Destructeur
	SquareList():square(NULL) {}
	~SquareList() {}

	SquareResult GetLinkId(unsigned int);
	bool GetNextLinkId(SquareResult&, SquareResult&);

	bool Load();                                   //Charge la liste
	SquareResult GetPossibleSquare(Config&);       //Retourne les cases possibles
	unsigned int GetSquareType(unsigned int);      //Retourne le type de case
	unsigned int GetSquareColor(unsigned int);     //Retourne la couleur de la case
};

#endif