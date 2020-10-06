/********************************************************/
/* Trivial Poursuit v1.0a By GummiTeam!                 */
/* board.h : Contient les méthodes nécessaires à        */
/* la gestion du plateau du trivial.                    */
/********************************************************/

#ifndef _BOARD_H_
#define _BOARD_H_

#include "3Dobject.h"
//#include "Error.h"
#include "config.h"
#include "squarelist.h"


//Défini les chemins des fichiers utiles au plateau
#define BOARD_DATA_FILE_PATH             "data//_objectz//board.tri"
#define BOARD_TEXTURE_FILE_PATH          "data//_picz//board.bmp"





//La classe du plateau
class Board:public TexturedObject
{
	SquareList square_list;                      //La liste chainée des cases du plateau
	SquareResult possible_square;                //Stocke les cases possibles

	unsigned int virtual_list_id;                //Stocke les Ids des faces du plateau virtuel

public:
	int selected_square;                         //Case sélectionnée

	//Constructeur/Destructeur
	Board():selected_square(-1)
	{
		square_list.Load();                      //Charge les cases
	}
	~Board() {}

	bool Load(Config&, unsigned int);            //Charge le plateau
	bool LoadVirtual();                          //Charge le plateau virtuel (pour la selection)

	void DrawVirtual();                          //Dessine le plateau virtuel

	void DrawPossibleSquare();                   //Dessine les cases possibles
	void DrawSelectedSquare();                   //Dessine la case sélectionnée

	bool GetPossibleSquare(Config&);             //Retourne les cases possibles
	unsigned int GetSquareType(unsigned int);    //Retourne le type de la case
	unsigned int GetSquareColor(unsigned int);   //Retourne la couleur de la case

};



#endif