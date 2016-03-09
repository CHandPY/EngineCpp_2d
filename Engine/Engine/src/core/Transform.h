#pragma once

#include "Matrix3f.h"
#include "Vector2f.h"

class Transform {

public:
	Transform(Vector2f *pos = new Vector2f(0, 0), float rot = 0, Vector2f *scale = new Vector2f(1, 1), bool invert_pos = false);
	Transform(Vector2f *pos, Vector2f *scale);
	~Transform();

	Vector2f * getPos();
	Vector2f * getScale();
	float getRotation();

	Matrix3f * getModelMatrix();
	bool hasChanged();

	Transform * negated_pos();

	void setPos(Vector2f *pos);
	void setScale(Vector2f *scale);
	void setRotation(float rotation);

private:
	Matrix3f* t_modelMatrix;
	Vector2f* t_position, *t_scale;
	float t_rotation;
	bool t_hasCanged, t_invertPos;

	void computeModelMatrix();

};