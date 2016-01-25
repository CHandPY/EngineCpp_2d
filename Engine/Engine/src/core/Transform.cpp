#include "Transform.h"

Transform::Transform(Vector2f pos, float rot, Vector2f scale) : t_position(pos), t_rotation(rot), t_scale(scale) {
	t_modelMatrix = Matrix3f();
	t_hasCanged = true;
}

Transform::Transform(Vector2f pos, Vector2f scale) : Transform(pos, 0, scale) {
}

Transform::~Transform() {
}

Vector2f Transform::getPos() {
	return t_position;
}

Vector2f Transform::getScale() {
	return t_scale;
}

float Transform::getRotation() {
	return t_rotation;
}

Matrix3f Transform::getmodelMatrix() {
	if (t_hasCanged) {
		computeModelMatrix();
		t_hasCanged = false;
	}
	return t_modelMatrix;
}

void Transform::setPos(Vector2f pos) {
	t_hasCanged = true;
	this->t_position = pos;
}

void Transform::setScale(Vector2f scale) {
	t_hasCanged = true;
	this->t_scale = scale;
}

void Transform::setRotation(float rotation) {
	t_hasCanged = true;
	this->t_rotation = rotation;
}

void Transform::computeModelMatrix() {
	Matrix3f mat_p = Matrix3f(), mat_r = Matrix3f(), mat_s = Matrix3f();
	mat_p.initTranslation(&t_position);
	mat_s.initScale(&t_scale);
	mat_r.initRotation(t_rotation);
	t_modelMatrix.initTransform(&mat_s, &mat_r, &mat_p);
	printf("%s\n", t_modelMatrix.toString().c_str());
}
