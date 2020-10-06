/********************************************************/
/* Trivial Poursuit v1.0a By GummiTeam!                 */
/* 3Dobject.h : Contient les méthodes nécessaires à     */
/* la gestion des objets 3D.                            */
/********************************************************/


#ifndef _3D_OBJECT_H_
#define _3D_OBJECT_H_

#include "3Dmath.h"
#include "config.h"


//Défini les chemins des fichiers contenant les informations sur les objets 3D
#define GROUND_DATA_FILE_PATH               "data//_objectz//ground.tri"
#define PAWN_DATA_FILE_PATH                 "data//_objectz//pawn.tri"
#define CAMEMBER_DATA_FILE_PATH             "data//_objectz//camember.tri"

//Pour le dé
#define DIE_DATA_FILE_PATH                  "data//_objectz//die.tri"
#define DIE_TEXTURE_FILE_PATH               "data//_picz//die.bmp"




//La classe objet
class Object
{
protected:
	Vector3*            vertex;               //Stocke les infos sur les sommets (coordonnées)              
	VertexNormal*       vertex_normal;        //Stocke les infos sur les normales de sommets

	Uint3*              face_vertex_id;       //Stocke les infos sur les faces
	Vector3*            face_normal;          //Stocke les infos sur les normales de faces

	unsigned int display_list_id;             //Enregistre des Id pour les listes d'affichage optimisant le programme

	unsigned int nb_vertex;                   //Enregistre le nombre de sommets
	unsigned int nb_face;                     //Enregistre le nombre de face


public:
	//Constructeur/Destructeur
	Object():nb_vertex(0),nb_face(0),vertex(NULL),vertex_normal(NULL),face_vertex_id(NULL),face_normal(NULL) {}
	~Object() {}


	bool Load(Config&, const char*, unsigned int);	    //Charge l'objet
	void Draw();                                    	//Dessine l'objet
};


//La classe pour les objets texturés
class TexturedObject:public Object
{
protected:
	Vector3* vertex_map_coord;                //Stocke les infos sur les coordonnées de mapping
	Uint3* face_map_coord_id;                 //Stocke les infos sur les coordonnées de mapping de face

	unsigned int texture_id;                  //Enregistre un Id pour la texture de l'objet

	unsigned int nb_vertex_map_coord;         //Enregistre le nombre de coordonnées de mapping
	unsigned int nb_face_map_coord;           //Enregistre le nombre de coordonnées de mapping de face

public:
	TexturedObject():vertex_map_coord(NULL),face_map_coord_id(NULL),nb_vertex_map_coord(0),nb_face_map_coord(0) {}
	~TexturedObject() {}

	bool Load(Config&, const char*, const char*, unsigned int);  //Charge l'objet
	bool LoadTexture(unsigned int, const char*);                 //Charge la texture
};


#endif