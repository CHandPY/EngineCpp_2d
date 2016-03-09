#include "Vector2f.h"

Vector2f* Vector2f::normalize() {
	return *this /= length();
	m_hasChanged = 1;
}

Vector2f* Vector2f::setX(float x) {
	m_x = x;
	m_calcLength = 1;
	m_hasChanged = 1;
	return this;
}

Vector2f* Vector2f::setY(float y) {
	m_y = y;
	m_calcLength = 1;
	m_hasChanged = 1;
	return this;
}

Vector2f* Vector2f::set(float x, float y) {
	m_x = x;
	m_y = y;
	m_calcLength = 1;
	m_hasChanged = 1;
	return this;
}

Vector2f* Vector2f::setLength(float length) {
	m_length = length;
	m_calcLength = 0;
	return this;
}

float Vector2f::getX() {
	return m_x;
}

float Vector2f::getY() {
	return m_y;
}
/*
returns the square of the length of this Vector2f
*/
float Vector2f::lengthSq() {
	if (!m_calcLength) {
		return m_length * m_length;
	}
	return m_x * m_x + m_y * m_y;
}

/*
returns the length of this Vector2f
*/
float Vector2f::length() {
	if (m_calcLength) {
		m_length = sqrt((m_x * m_x) + (m_y * m_y));
		m_calcLength = 0;
	}
	return m_length;
}

Vector2f* Vector2f::getNormalized() {
	return *this/m_length;
}

bool Vector2f::hasChanged() {
	if (m_hasChanged) {
		m_hasChanged = false;
		return true;
	}
	return false;
}

Vector2f* Vector2f::operator+ (Vector2f *vec) {
	return new Vector2f(m_x + vec->m_x, m_y + vec->m_y);
}

/*
Subtracts a Vector2f with this one.
*/
Vector2f* Vector2f::operator- (Vector2f *vec) {
	return new Vector2f(m_x - vec->m_x, m_y - vec->m_y);
}

/*
Dot Product
*/
float Vector2f::operator* (Vector2f *vec) {
	return( m_x * vec->m_x) + (m_y * vec->m_y);
}


/*
Adds a float to all the elements of this Vector2f.
*/
Vector2f* Vector2f::operator+ (float f) {
	return new Vector2f(m_x + f, m_y + f);
}

/*
Subtracts a float from all the elements of this Vector2f.
*/
Vector2f* Vector2f::operator- (float f) {
	return new Vector2f(m_x - f, m_y - f);
}

/*
Multiplies all the elements of this Vector2f by a float.
*/
Vector2f* Vector2f::operator* (float f) {
	return new Vector2f(m_x * f, m_y * f);
}

/*
Divide all the elements of this Vector2f by a float.
*/
Vector2f* Vector2f::operator/ (float f) {
	return new Vector2f(m_x / f, m_y / f);
}

/*
Adds a Vector2f to this one.
*/
Vector2f* Vector2f::operator+= (Vector2f *vec) {
	this->m_x += vec->m_x;
	this->m_y += vec->m_y;
	m_calcLength = 1;
	m_hasChanged = 1;
	return this;
}

/*
Subtracts a Vector2f to this one.
*/
Vector2f* Vector2f::operator-= (Vector2f *vec) {
	this->m_x -= vec->m_x;
	this->m_y -= vec->m_y;
	m_calcLength = 1;
	m_hasChanged = 1;
	return this;
}


/*
Adds a float to this one.
*/
Vector2f* Vector2f::operator+= (float f) {
	this->m_x += f;
	this->m_y += f;
	m_calcLength = 1;
	m_hasChanged = 1;
	return this;
}

/*
Subtracts a float from this one.
*/
Vector2f* Vector2f::operator-= (float f) {
	this->m_x -= f;
	this->m_y -= f;
	m_calcLength = 1;
	m_hasChanged = 1;
	return this;
}

/*
Multiplies this Vector2f by a float.
*/
Vector2f* Vector2f::operator*= (float f) {
	this->m_x *= f;
	this->m_y *= f;
	m_length *= f;
	m_hasChanged = 1;
	return this;
}

/*
Divides this Vector2f by a float.
*/
Vector2f* Vector2f::operator/= (float f) {
	this->m_x /= f;
	this->m_y /= f;
	m_length /= f;
	m_hasChanged = 1;
	return this;
}

/*
Increments each element of this Vector2f.
Warning! this does not respect post / pre order, both will result 
in the Incremented vector being returned to avoid a useless copy.
*/
Vector2f* Vector2f::operator++ (void) {
	this->m_x++;
	this->m_y++;
	m_calcLength = 1;
	m_hasChanged = 1;
	return this;
}

/*
Decrements each element of this Vector2f.
Warning! this does not respect post / pre order, both will result
in the Incremented vector being returned to avoid a useless copy.
*/
Vector2f* Vector2f::operator-- (void) {
	this->m_x--;
	this->m_y--;
	m_calcLength = 1;
	m_hasChanged = 1;
	return this;
}

/*
This Vector2f's negation.
*/
Vector2f* Vector2f::operator- (void) {
	return new Vector2f(-m_x, -m_y);
}

/*
Checks for equality with this Vector2f.
*/
bool Vector2f::operator== (Vector2f* vec) {
	return (m_x == vec->m_x && m_y == vec->m_y);
}

/*
Strict greater than between this Vector2f and another
*/
bool Vector2f::operator> (Vector2f* vec) {
	return m_x > vec->m_x && m_y > vec->m_y;
}

/*
Strict less than between this Vector2f and another
*/
bool Vector2f::operator< (Vector2f* vec) {
	return m_x < vec->m_x && m_y < vec->m_y;
}

/*
* Strict greater than or equal between this Vector2f and another
*/
bool Vector2f::operator>= (Vector2f* vec) {
	return m_x >= vec->m_x && m_y >= vec->m_y;
}

/*
Strict less than between or equal this Vector2f and another
*/
bool Vector2f::operator<= (Vector2f* vec) {
	return m_x <= vec->m_x && m_y <= vec->m_y;
}

Vector2f * Vector2f::negate() {
	this->m_x = -m_x;
	this->m_y = -m_y; 
	m_calcLength = 1;
	return this;
}

float *Vector2f::operator[] (int i) {
	return i == 1 ? &m_y : &m_x;
}

float Vector2f::cross(Vector2f* v1, Vector2f* v2) {
	return (v1->m_x * v2->m_y) - (v1->m_y * v2->m_x);
}

string Vector2f::toString() {
	return "(" + str(m_x) + ", " + str(m_y) + ") Length: " + str(m_length);
}