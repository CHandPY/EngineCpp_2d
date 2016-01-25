#include "Matrix3f.h"



string Matrix3f::toString() {
	return "\t[" + str(m_mat[0]) + ", " + str(m_mat[1]) + ", " + str(m_mat[2]) + "]\n" + "M =\t[" + str(m_mat[3]) + ", " + str(m_mat[4]) + ", " + str(m_mat[5])+ "]\n" + "\t[" + str(m_mat[6]) + ", " + str(m_mat[7]) + ", " + str(m_mat[8]) + "]\n";
}


Matrix3f::Matrix3f() {
	m_mat = new float[9]();
}

float* Matrix3f::operator[] (int i) {
	return &m_mat[i];
}

Matrix3f* Matrix3f::initIdentity() {
	m_mat[0] = 1;
	m_mat[1] = 0;
	m_mat[2] = 0;
	m_mat[3] = 0;
	m_mat[4] = 1;
	m_mat[5] = 0;
	m_mat[6] = 0;
	m_mat[7] = 0;
	m_mat[8] = 1;
	return this;
}

Matrix3f * Matrix3f::initTranslation(Vector2f *trans) {
	return initTranslation(*(*trans)[0], *(*trans)[1]);
}

Matrix3f* Matrix3f::initScale(float x, float y) {
	m_mat[0] = x;
	m_mat[1] = 0;
	m_mat[2] = 0;
	m_mat[3] = 0;
	m_mat[4] = y;
	m_mat[5] = 0;
	m_mat[6] = 0;
	m_mat[7] = 0;
	m_mat[8] = 1;

	return this;
}

Matrix3f * Matrix3f::initScale(Vector2f *scale) {
	return initScale(*(*scale)[0], *(*scale)[1]);
}

Matrix3f* Matrix3f::initRotation(float rot) {
	m_mat[0] = cos(rot);
	m_mat[1] = -sin(rot);
	m_mat[2] = 0;
	m_mat[3] = sin(rot);
	m_mat[4] = cos(rot);
	m_mat[5] = 0;
	m_mat[6] = 0;
	m_mat[7] = 0;
	m_mat[8] = 1;
	return this;
}

Matrix3f* Matrix3f::initTranslation(float x, float y) {
	m_mat[0] = 1;
	m_mat[1] = 0;
	m_mat[2] = x;
	m_mat[3] = 0;
	m_mat[4] = 1;
	m_mat[5] = y;
	m_mat[6] = 0;
	m_mat[7] = 0;
	m_mat[8] = 1;
	return this;
}

/*
 */
Matrix3f* Matrix3f::initTransform(Matrix3f* scale, Matrix3f* rotation, Matrix3f* translate) {
	initIdentity();
	*this *= translate;
	*this *= scale;
	*this *= rotation;
	return this;
}

Matrix3f* Matrix3f::initOrtho(float left, float right, float bottom, float top) {
	m_mat[0] = 2 / (right - left);
	m_mat[1] = 0;
	m_mat[2] = -(right+left)/(right - left);
	m_mat[3] = 0;
	m_mat[4] = 2/(top - bottom);
	m_mat[5] = -(top+bottom)/(top - bottom);
	m_mat[6] = 0;
	m_mat[7] = 0;
	m_mat[8] = 1;
	return this;
}



Matrix3f* Matrix3f::operator+ (Matrix3f* m2) {
	Matrix3f* m = new Matrix3f();
	m->m_mat[0] = m_mat[0] + m2->m_mat[0];
	m->m_mat[1] = m_mat[1] + m2->m_mat[1];
	m->m_mat[2] = m_mat[2] + m2->m_mat[2];
	m->m_mat[3] = m_mat[3] + m2->m_mat[3];
	m->m_mat[4] = m_mat[4] + m2->m_mat[4];
	m->m_mat[5] = m_mat[5] + m2->m_mat[5];
	m->m_mat[6] = m_mat[6] + m2->m_mat[6];
	m->m_mat[7] = m_mat[7] + m2->m_mat[7];
	m->m_mat[8] = m_mat[8] + m2->m_mat[8];
	return m;
}

Matrix3f* Matrix3f::operator+= (Matrix3f* m2) {
	m_mat[0] += m2->m_mat[0];
	m_mat[1] += m2->m_mat[1];
	m_mat[2] += m2->m_mat[2];
	m_mat[3] += m2->m_mat[3];
	m_mat[4] += m2->m_mat[4];
	m_mat[5] += m2->m_mat[5];
	m_mat[6] += m2->m_mat[6];
	m_mat[7] += m2->m_mat[7];
	m_mat[8] += m2->m_mat[8];
	return this;
}

Matrix3f* Matrix3f::operator- (Matrix3f* m2) {
	Matrix3f* m = new Matrix3f();
	m->m_mat[0] = m_mat[0] - m2->m_mat[0];
	m->m_mat[1] = m_mat[1] - m2->m_mat[1];
	m->m_mat[2] = m_mat[2] - m2->m_mat[2];
	m->m_mat[3] = m_mat[3] - m2->m_mat[3];
	m->m_mat[4] = m_mat[4] - m2->m_mat[4];
	m->m_mat[5] = m_mat[5] - m2->m_mat[5];
	m->m_mat[6] = m_mat[6] - m2->m_mat[6];
	m->m_mat[7] = m_mat[7] - m2->m_mat[7];
	m->m_mat[8] = m_mat[8] - m2->m_mat[8];
	return m;
}

Matrix3f* Matrix3f::operator-= (Matrix3f* m2) {
	m_mat[0] -= m2->m_mat[0];
	m_mat[1] -= m2->m_mat[1];
	m_mat[2] -= m2->m_mat[2];
	m_mat[3] -= m2->m_mat[3];
	m_mat[4] -= m2->m_mat[4];
	m_mat[5] -= m2->m_mat[5];
	m_mat[6] -= m2->m_mat[6];
	m_mat[7] -= m2->m_mat[7];
	m_mat[8] -= m2->m_mat[8];
	return this;
}

Vector2f* Matrix3f::operator*(Vector2f* v) {
	return  new Vector2f((*(*v)[0] * m_mat[0]) + (*(*v)[1] * m_mat[1]) + (m_mat[2]), (*(*v)[0] * m_mat[3]) + (*(*v)[1] * m_mat[4]) + (m_mat[5]));
}

Matrix3f* Matrix3f::operator*=(Matrix3f* m) {
	float newdata[9];
	newdata[0] = (m_mat[0] * m->m_mat[0]) + (m_mat[1] * m->m_mat[3]) + (m_mat[2] * m->m_mat[6]);
	newdata[1] = (m_mat[0] * m->m_mat[1]) + (m_mat[1] * m->m_mat[4]) + (m_mat[2] * m->m_mat[7]);
	newdata[2] = (m_mat[0] * m->m_mat[2]) + (m_mat[1] * m->m_mat[5]) + (m_mat[2] * m->m_mat[8]);

	newdata[3] = (m_mat[3] * m->m_mat[0]) + (m_mat[4] * m->m_mat[3]) + (m_mat[5] * m->m_mat[6]);
	newdata[4] = (m_mat[3] * m->m_mat[1]) + (m_mat[4] * m->m_mat[4]) + (m_mat[5] * m->m_mat[7]);
	newdata[5] = (m_mat[3] * m->m_mat[2]) + (m_mat[4] * m->m_mat[5]) + (m_mat[5] * m->m_mat[8]);

	newdata[6] = (m_mat[6] * m->m_mat[0]) + (m_mat[7] * m->m_mat[3]) + (m_mat[8] * m->m_mat[6]);
	newdata[7] = (m_mat[6] * m->m_mat[1]) + (m_mat[7] * m->m_mat[4]) + (m_mat[8] * m->m_mat[7]);
	newdata[8] = (m_mat[6] * m->m_mat[2]) + (m_mat[7] * m->m_mat[5]) + (m_mat[8] * m->m_mat[8]);
	for (int i = 0; i < 9; i++) {
		m_mat[i] = newdata[i];
	}
	return this;
}

Matrix3f* Matrix3f::operator*(Matrix3f* m) {
	Matrix3f* m2 = new Matrix3f();
	m2->m_mat[0] = (m_mat[0] * m->m_mat[0]) + (m_mat[1] * m->m_mat[3]) + (m_mat[2] * m->m_mat[6]);
	m2->m_mat[1] = (m_mat[0] * m->m_mat[1]) + (m_mat[1] * m->m_mat[4]) + (m_mat[2] * m->m_mat[7]);
	m2->m_mat[2] = (m_mat[0] * m->m_mat[2]) + (m_mat[1] * m->m_mat[5]) + (m_mat[2] * m->m_mat[8]);

	m2->m_mat[3] = (m_mat[3] * m->m_mat[0]) + (m_mat[4] * m->m_mat[3]) + (m_mat[5] * m->m_mat[6]);
	m2->m_mat[4] = (m_mat[3] * m->m_mat[1]) + (m_mat[4] * m->m_mat[4]) + (m_mat[5] * m->m_mat[7]);
	m2->m_mat[5] = (m_mat[3] * m->m_mat[2]) + (m_mat[4] * m->m_mat[5]) + (m_mat[5] * m->m_mat[8]);

	m2->m_mat[6] = (m_mat[6] * m->m_mat[0]) + (m_mat[7] * m->m_mat[3]) + (m_mat[8] * m->m_mat[6]);
	m2->m_mat[7] = (m_mat[6] * m->m_mat[1]) + (m_mat[7] * m->m_mat[4]) + (m_mat[8] * m->m_mat[7]);
	m2->m_mat[8] = (m_mat[6] * m->m_mat[2]) + (m_mat[7] * m->m_mat[5]) + (m_mat[8] * m->m_mat[8]);
	return m2;
}

Matrix3f::~Matrix3f() {
	//delete[] m_mat;
}