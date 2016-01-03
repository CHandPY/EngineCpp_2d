#include "Vector2f.h"

Vector2f* Vector2f::setX(float m_x) {
	m_x = m_x;
	return this;
}

Vector2f* Vector2f::setY(float m_y) {
	m_y = m_y;
	return this;
}

Vector2f* Vector2f::set(float m_x, float m_y) {
	m_x = m_x;
	m_y = m_y;
	return this;
}


float Vector2f::getX() {
	return m_x;
}

float Vector2f::getY() {
	return m_y;
}

Vector2f Vector2f::operator+ (Vector2f vec) {
	return Vector2f(m_x + vec.m_x, m_y + vec.m_y);
}

/*
* Subtracts a Vector2f with this one.
*/
Vector2f Vector2f::operator- (Vector2f vec) {
	return Vector2f(m_x - vec.m_x, m_y - vec.m_y);
}

/*
* Multiplies this Vector2f with another one.
*/
Vector2f Vector2f::operator* (Vector2f vec) {
	return Vector2f(m_x * vec.m_x, m_y * vec.m_y);
}

/*
* Divides this Vector2f with another one.
*/
Vector2f Vector2f::operator/ (Vector2f vec) {
	return Vector2f(m_x / vec.m_x, m_y / vec.m_y);
}

/*
* Adds a float to all the elements of this Vector2f.
*/
Vector2f Vector2f::operator+ (float f) {
	return Vector2f(m_x + f, m_y + f);
}

/*
* Subtracts a float from all the elements of this Vector2f.
*/
Vector2f Vector2f::operator- (float f) {
	return Vector2f(m_x - f, m_y - f);
}

/*
* Multiplies all the elements of this Vector2f by a float.
*/
Vector2f Vector2f::operator* (float f) {
	return Vector2f(m_x * f, m_y * f);
}

/*
* Divide all the elements of this Vector2f by a float.
*/
Vector2f Vector2f::operator/ (float f) {
	return Vector2f(m_x / f, m_y / f);
}

/*
* Adds a Vector2f to this one.
*/
Vector2f Vector2f::operator+= (Vector2f vec) {
	this->m_x += vec.m_x;
	this->m_y += vec.m_y;
	m_calcLength = true;
	return *this;
}

/*
* Subtracts a Vector2f to this one.
*/
Vector2f Vector2f::operator-= (Vector2f vec) {
	this->m_x -= vec.m_x;
	this->m_y -= vec.m_y;
	m_calcLength = true;
	return *this;
}

/*
* Multiplies this Vector2f by another one.
*/
Vector2f Vector2f::operator*= (Vector2f vec) {
	this->m_x *= vec.m_x;
	this->m_y *= vec.m_y;
	m_calcLength = true;
	return *this;
}

/*
* Divides this Vector2f by another one.
*/
Vector2f Vector2f::operator/= (Vector2f vec) {
	this->m_x /= vec.m_x;
	this->m_y /= vec.m_y;
	m_calcLength = true;
	return *this;
}

/*
* Adds a float to this one.
*/
Vector2f Vector2f::operator+= (float f) {
	this->m_x += f;
	this->m_y += f;
	m_calcLength = true;
	return *this;
}

/*
* Subtracts a float from this one.
*/
Vector2f Vector2f::operator-= (float f) {
	this->m_x -= f;
	this->m_y -= f;
	m_calcLength = true;
	return *this;
}

/*
* Multiplies this Vector2f by a float.
*/
Vector2f Vector2f::operator*= (float f) {
	this->m_x *= f;
	this->m_y *= f;
	m_calcLength = true;
	return *this;
}

/*
* Divides this Vector2f by a float.
*/
Vector2f Vector2f::operator/= (float f) {
	this->m_x /= f;
	this->m_y /= f;
	m_calcLength = true;
	return *this;
}

/*
* Increments each element of this Vector2f.
*/
Vector2f Vector2f::operator++ (void) {
	this->m_x++;
	this->m_y++;
	m_calcLength = true;
	return *this;
}

/*
* Decrements each element of this Vector2f.
*/
Vector2f Vector2f::operator-- (void) {
	this->m_x--;
	this->m_y--;
	m_calcLength = true;
	return *this;
}

/*
* This Vector2f's negation.
*/
Vector2f Vector2f::operator- (void) {
	return Vector2f(-m_x, -m_y);
}

/*
* Checks for equality with this Vector2f.
*/
bool Vector2f::operator== (Vector2f vec) {
	return (m_x == vec.m_x && m_y == vec.m_y);
}

/*
* Strict greater than between this Vector2f and another
*/
bool Vector2f::operator> (Vector2f vec) {
	return m_x > vec.m_x && m_y > vec.m_y;
}

/*
* Strict less than between this Vector2f and another
*/
bool Vector2f::operator< (Vector2f vec) {
	return m_x < vec.m_x && m_y < vec.m_y;
}

/*
* Strict greater than or equal between this Vector2f and another
*/
bool Vector2f::operator>= (Vector2f vec) {
	return m_x >= vec.m_x && m_y >= vec.m_y;
}

/*
* Strict less than between or equal this Vector2f and another
*/
bool Vector2f::operator<= (Vector2f vec) {
	return m_x <= vec.m_x && m_y <= vec.m_y;
}

/*
* the length of a vector before the square root
*/
float Vector2f::lengthSq() {
	return m_x * m_x + m_y * m_y;
}

/*
* returns the stored length of this Vector2f
*/
float Vector2f::length() {
	return m_length;
}