#pragma once
#include <iostream>
#include <Math.h>
#include "ToString.h"

using namespace std;

class Vector2f : ToString {

public:
	Vector2f(float x, float y) : m_x(x), m_y(y), m_calcLength(true), m_length(0) {}
	Vector2f(float x, float y, float length) : m_x(x), m_y(y), m_length(length), m_calcLength(false) {}
	Vector2f(float f) : Vector2f(f, f) {}
	Vector2f() : Vector2f(0, 0, 0) {}

	~Vector2f() {}


	/* setters */
	Vector2f* setX(float x);
	Vector2f* setY(float y);
	Vector2f* set(float x, float y);
	Vector2f* setLength(float length);

	/* getters */
	float getX();
	float getY();
	float length();
	float lengthSq();
	Vector2f* getNormalized(void);

	/* basic math operators */
	Vector2f* operator+  (Vector2f*);
	Vector2f* operator-  (Vector2f*);
	float operator*  (Vector2f*);
	/* basic math operators with float */
	Vector2f* operator+  (float);
	Vector2f* operator-  (float);
	Vector2f* operator*  (float);
	Vector2f* operator/  (float);
	/* self assignment operators */
	Vector2f* operator+= (Vector2f*);
	Vector2f* operator-= (Vector2f*);
	/* self assignment operators with float */
	Vector2f* operator+= (float);
	Vector2f* operator-= (float);
	Vector2f* operator*= (float);
	Vector2f* operator/= (float);
	/* unary operators */
	Vector2f* operator++ (void);
	Vector2f* operator-- (void);
	Vector2f* operator-  (void);

	float *operator[] (int);
	/* comparison operators */
	bool operator==     (Vector2f*);
	bool operator>      (Vector2f*);
	bool operator<      (Vector2f*);
	bool operator>=     (Vector2f*);
	bool operator<=     (Vector2f*);

	/* dot and cross */

	float cross(Vector2f*, Vector2f*);

	string toString();

	Vector2f* normalize(void);

private:
	float m_x, m_y, m_length;
	bool m_calcLength;

};