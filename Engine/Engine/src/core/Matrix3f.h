#pragma once

#include <Math.h>
#include "Vector2f.h"

class Matrix3f {








public:
	Matrix3f();

	~Matrix3f();
	Matrix3f* initIdentity();

	//operations
	float* operator[] (int);
	Matrix3f* operator*(Matrix3f*);
	Matrix3f* operator+(Matrix3f*);
	Matrix3f* operator-(Matrix3f*);

	Matrix3f* operator*=(Matrix3f*);
	Matrix3f* operator+=(Matrix3f*);
	Matrix3f* operator-=(Matrix3f*);

	Matrix3f* operator*(Vector2f);



private:
	float *m_mat;
};