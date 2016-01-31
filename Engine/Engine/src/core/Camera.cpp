#include "Camera.h"

Camera::Camera(Transform transform, Matrix3f projection) : c_trnsform(&transform), c_projectionMatrix(projection) {
	c_viewProjMat = Matrix3f();
}

Camera::~Camera() {
}

Transform * Camera::transform() {
	return c_trnsform;
}

Matrix3f Camera::getViewProjectionMatrix() {
	//if (c_trnsform->hasChanged()) {
		computeViewProjectionMatrix();
	//}
	return c_viewProjMat;
}

void Camera::computeViewProjectionMatrix() {
	cout << c_trnsform->getModelMatrix()[0] << endl;
	//c_viewProjMat = *(c_projectionMatrix * &(c_trnsform->getModelMatrix()));
}
