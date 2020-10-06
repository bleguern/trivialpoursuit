/********************************************************/
/* Trivial Poursuit v1.0a By GummiTeam!                 */
/* 3Dmath.h : Contient les fonctions mathématiques      */
/* 3D nécessaires.                                      */
/********************************************************/

#ifndef _3DMATH_H_
#define _3DMATH_H_

#include "trivial.h"



//Classe Vector3 permet des opérations sur 3 variables de type float
class Vector3
{
public:

	GLfloat x, y, z;

	//Constructeurs
	Vector3() {};
	Vector3(float *);
	Vector3(float, float, float);

	//Surdéfinition de l'opérateur d'indexation
	operator float* ();
	operator const float* () const;

	float &operator [] (unsigned int);
	const float &operator [] (unsigned int) const;


	Vector3& operator += (Vector3&);
	Vector3& operator -= (Vector3&);

	Vector3& operator *= (Vector3&);
	Vector3& operator /= (Vector3&);
	
	Vector3& operator *= (float);
	Vector3& operator /= (float);

	
	Vector3 operator + (Vector3&);
	Vector3 operator - (Vector3&);

	Vector3 operator * (Vector3&);
	Vector3 operator / (Vector3&);
	
	Vector3 operator * (float);
	Vector3 operator / (float);


	bool operator == (Vector3&);
	bool operator != (Vector3&);
};


//Classe Vector4 permet des opérations sur 4 variables de type float
class Vector4
{
public:

	GLfloat x, y, z, t;

	Vector4() {};
	Vector4(float *);
	Vector4(float, float, float, float);

	operator float* ();
	operator const float* () const;

	float &operator [] (unsigned int);
	const float &operator [] (unsigned int) const;


	Vector4& operator += (Vector4&);
	Vector4& operator -= (Vector4&);

	Vector4& operator *= (Vector4&);
	Vector4& operator /= (Vector4&);
	
	Vector4& operator *= (float);
	Vector4& operator /= (float);


	Vector4 operator + (Vector4&);
	Vector4 operator - (Vector4&);

	Vector4 operator * (Vector4&);
	Vector4 operator / (Vector4&);
	
	Vector4 operator * (float);
	Vector4 operator / (float);


	bool operator == (Vector4&);
	bool operator != (Vector4&);
};


//Structure VertexNormal permet de stocker les informations sur les normales de sommet (Pour les objets 3D)
typedef struct
{
	Vector3 Vertex[3];
}VertexNormal;

//Struture de type 3*unsigned int
typedef struct
{
	unsigned int Num[3];
}Uint3;


#endif