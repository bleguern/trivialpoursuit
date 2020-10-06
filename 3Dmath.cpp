/********************************************************/
/* Trivial Poursuit v1.0a By GummiTeam!                 */
/* 3Dmath.cpp : Contient les fonctions mathématiques    */
/* 3D nécessaires.                                      */
/********************************************************/

#include "3DMath.h"


//Fonctions de la classe Vector3
Vector3::Vector3(float *v)
{
	x = v[0];
	y = v[1];
	z = v[2];
}
Vector3::Vector3(float a, float b, float c)
{
	x = a;
	y = b;
	z = c;
}

Vector3::operator float* ()
{
	return &x;
}
Vector3::operator const float* () const
{
	return &x;
}
float &Vector3::operator [] (unsigned int i)
{
	return *(&x+i);
}
const float &Vector3::operator [] (unsigned int i) const 
{
	return *(&x+i);
}


Vector3& Vector3::operator += (Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;

	return *this;
}
Vector3& Vector3::operator -= (Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;

	return *this;
}
Vector3& Vector3::operator *= (Vector3& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;

	return *this;
}
Vector3& Vector3::operator /= (Vector3& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;

	return *this;
}
Vector3& Vector3::operator *= (float v)
{
	x *= v;
	y *= v;
	z *= v;

	return *this;
}
Vector3& Vector3::operator /= (float v)
{
	x /= v;
	y /= v;
	z /= v;

	return *this;
}

Vector3 Vector3::operator + (Vector3& v)
{
	return Vector3(x+v.x, y+v.y, z+v.z);
}
Vector3 Vector3::operator - (Vector3& v)
{
	return Vector3(x-v.x, y-v.y, z-v.z);
}
Vector3 Vector3::operator * (Vector3& v)
{
	return Vector3(x*v.x, y*v.y, z*v.z);
}
Vector3 Vector3::operator / (Vector3& v)
{
	return Vector3(x/v.x, y/v.y, z/v.z);
}
Vector3 Vector3::operator * (float v)
{
	return Vector3(x*v, y*v, z*v);
}
Vector3 Vector3::operator / (float v)
{
	return Vector3(x/v, y/v, z/v);
}

bool Vector3::operator == (Vector3& v)
{
	return((x == v.x) && (y == v.y) && (z == v.z));
}
bool Vector3::operator != (Vector3& v)
{
	return((x != v.x) || (y != v.y) || (z != v.z));
}


//Fonctions de la classe Vector4
Vector4::Vector4(float *v)
{
	x = v[0];
	y = v[1];
	z = v[2];
	t = v[3];
}
Vector4::Vector4(float a, float b, float c, float d)
{
	x = a;
	y = b;
	z = c;
	t = d;
}


Vector4::operator float* ()
{
	return &x;
}
Vector4::operator const float* () const
{
	return &x;
}
float &Vector4::operator [] (unsigned int i)
{
	return *(&x+i);
}
const float &Vector4::operator [] (unsigned int i) const 
{
	return *(&x+i);
}



Vector4& Vector4::operator += (Vector4& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	t += v.t;

	return *this;
}
Vector4& Vector4::operator -= (Vector4& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	t -= v.t;

	return *this;
}
Vector4& Vector4::operator *= (Vector4& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	t *= v.t;

	return *this;
}
Vector4& Vector4::operator /= (Vector4& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	t /= v.t;

	return *this;
}
Vector4& Vector4::operator *= (float v)
{
	x *= v;
	y *= v;
	z *= v;
	t *= v;

	return *this;
}
Vector4& Vector4::operator /= (float v)
{
	x /= v;
	y /= v;
	z /= v;
	t /= v;

	return *this;
}

Vector4 Vector4::operator + (Vector4& v)
{
	return Vector4(x+v.x, y+v.y, z+v.z, t+v.t);
}
Vector4 Vector4::operator - (Vector4& v)
{
	return Vector4(x-v.x, y-v.y, z-v.z, t-v.t);
}
Vector4 Vector4::operator * (Vector4& v)
{
	return Vector4(x*v.x, y*v.y, z*v.z, t*v.t);
}
Vector4 Vector4::operator / (Vector4& v)
{
	return Vector4(x/v.x, y/v.y, z/v.z, t/v.t);
}
Vector4 Vector4::operator * (float v)
{
	return Vector4(x*v, y*v, z*v, t*v);
}
Vector4 Vector4::operator / (float v)
{
	return Vector4(x/v, y/v, z/v, t/v);
}

bool Vector4::operator == (Vector4& v)
{
	return((x == v.x) && (y == v.y) && (z == v.z) && (t == v.t));
}
bool Vector4::operator != (Vector4& v)
{
	return((x != v.x) || (y != v.y) || (z != v.z) || (t != v.t));
}