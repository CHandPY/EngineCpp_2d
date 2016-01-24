#pragma once

#include <cmath>

#include "Vector2f.h"
#include "ToString.h"

class Matrix3f : public ToString {




public:
	Matrix3f();

	~Matrix3f();
	Matrix3f* initIdentity();
	Matrix3f* initTranslation(float x, float y);
	Matrix3f* initTransform(Matrix3f* scale, Matrix3f* rotation, Matrix3f* translate);
	Matrix3f* initRotation(float rot);
	Matrix3f* initScale(float x, float y);
	Matrix3f* initOrtho(float left, float right, float bottom, float top);

	//operations
	float* operator[] (int);
	Matrix3f* operator*(Matrix3f*);
	Matrix3f* operator+(Matrix3f*);
	Matrix3f* operator-(Matrix3f*);

	Matrix3f* operator*=(Matrix3f*);
	Matrix3f* operator+=(Matrix3f*);
	Matrix3f* operator-=(Matrix3f*);

	Vector2f* operator*(Vector2f*);

	float *getArray() {
		return m_mat;
	}

	string toString();

private:
	float *m_mat;
};