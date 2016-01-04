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

	Vector2f* operator*(Vector2f);

	Matrix3f* toTransform(Matrix3f*, Matrix3f*, Matrix3f*);



private:
	float *m_mat;
};