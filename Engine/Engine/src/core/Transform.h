#pragma once

#include "Matrix3f.h"
#include "Vector2f.h"

class Transform {

public:
	Transform(Vector2f pos = Vector2f(0, 0), float rot = 0, Vector2f scale = Vector2f(1, 1));
	Transform(Vector2f pos, Vector2f scale);
	~Transform();

	/*
	Getters do not return a pointer to prevent an untracked change
	in the value of one of the components. This could result in
	the model matrix not being recalculated and the transformation
	being void.
	*/
	Vector2f getPos();
	Vector2f getScale();
	float getRotation();

	Matrix3f getmodelMatrix();

	void setPos(Vector2f pos);
	void setScale(Vector2f scale);
	void setRotation(float rotation);

private:
	Matrix3f t_modelMatrix;
	Vector2f t_position, t_scale;
	float t_rotation;
	bool t_hasCanged;

	void computeModelMatrix();

};