#pragma once

#include "Matrix3f.h"
#include "Vector2f.h"
#include "Transform.h"

class Camera {

public:
	Camera(Transform transform, Matrix3f projection);
	~Camera();

	Transform * transform();
	Matrix3f getViewProjectionMatrix();

private:
	Transform *c_trnsform;
	Matrix3f c_viewProjMat, c_projectionMatrix;

	void computeViewProjectionMatrix();

};