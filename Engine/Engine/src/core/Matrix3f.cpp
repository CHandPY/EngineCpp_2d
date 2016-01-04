#include "Matrix3f.h"

Matrix3f::Matrix3f() {
	m_mat = new float[9]();
}

float* Matrix3f::operator[] (int i) {
	return &m_mat[i];
}

Matrix3f* Matrix3f::initIdentity() {
	m_mat[0] = 1;
	m_mat[4] = 1;
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

Matrix3f* Matrix3f::operator*(Vector2f) {
	
}

Matrix3f* Matrix3f::operator*=(Matrix3f*) {

}

Matrix3f* Matrix3f::operator*(Matrix3f*) {

}

Matrix3f::~Matrix3f() {
	delete[] m_mat;
}