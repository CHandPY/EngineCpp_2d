#pragma once
#include <iostream>
#include "Math.h"

using namespace std;

class Vector2f {

public:
	Vector2f(float x, float y) : m_x(x), m_y(y), m_calcLength(true) {}
	Vector2f(float x, float y, float length) : m_x(x), m_y(y) ,m_length(length), m_calcLength(false) {}
	Vector2f(float f) : Vector2f(f, f) {}
	Vector2f() : Vector2f(0, 0, 0) {}

	~Vector2f() {}


	/* setters */
	Vector2f setX(float x);
	Vector2f setY(float y);
	Vector2f set(float x, float y);

	/* getters */
	float getX();
	float getY();

	/* basic math operators */
	Vector2f operator+  (Vector2f);
	Vector2f operator-  (Vector2f);
	Vector2f operator*  (Vector2f);
	Vector2f operator/  (Vector2f);
	/* basic math operators with float */
	Vector2f operator+  (float);
	Vector2f operator-  (float);
	Vector2f operator*  (float);
	Vector2f operator/  (float);
	/* self assignment operators */
	Vector2f operator+= (Vector2f);
	Vector2f operator-= (Vector2f);
	Vector2f operator*= (Vector2f);
	Vector2f operator/= (Vector2f);
	/* self assignment operators with float */
	Vector2f operator+= (float);
	Vector2f operator-= (float);
	Vector2f operator*= (float);
	Vector2f operator/= (float);
	/* unary operators */
	Vector2f operator++ (void);
	Vector2f operator-- (void);
	Vector2f operator-  (void);
	/* comparison operators */
	bool operator==     (Vector2f);
	bool operator>      (Vector2f);
	bool operator<      (Vector2f);
	bool operator>=     (Vector2f);
	bool operator<=     (Vector2f);
	/* Array accessor for elements of the vector */
	float operator[] (int index);

	/* dot and cross */
	float dot(Vector2f);
	Vector2f cross(Vector2f);

	/* length functions */
	float length();
	float lengthSQ();

	/* misc functions */
	float max();
	float min();

	//TODO: debug
	void pnt() {
		cout << "(" << m_x << ", " << m_y << ")" << endl;
	}

private:
	float m_x, m_y, m_length;
	bool m_calcLength;

};