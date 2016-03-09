#pragma once

#include <iostream>
#include <cmath>

#include "ToString.h"

using namespace std;

class Vector2f : public ToString {

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

	/*
	Has a virtual contract with the user that states that this method
	can only be called once per frame and subsequent calling in the same 
	frame will not return a correct value. 
	*/
	bool hasChanged();

	/* basic math operators */
	Vector2f* operator+  (Vector2f*);
	Vector2f* operator-  (Vector2f*);
	float operator*      (Vector2f*);
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

	/* negates this vector and applies to self */
	Vector2f * negate();

	/* dot and cross */

	float cross(Vector2f*, Vector2f*);

	string toString();

	Vector2f* normalize(void);

private:
	float m_x, m_y, m_length;
	bool m_calcLength, m_hasChanged;

};