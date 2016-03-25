#include "Camera.h"

namespace engine {
	namespace graphics {

		using namespace core;

		Camera::Camera(Transform *transform, Ortho *ortho) : c_transform(transform), c_ortho(ortho) {
			c_viewProjMat = new Matrix3f();
			computeViewProjectionMatrix();
		}

		Camera::~Camera() {
			delete c_transform;
			delete c_ortho;
			delete c_viewProjMat;
		}

		Transform * Camera::transform() {
			return c_transform;
		}

		Matrix3f * Camera::getViewProjectionMatrix() {
			if (c_transform->hasChanged()) {
				computeViewProjectionMatrix();
			}
			return c_viewProjMat;
		}

		void Camera::computeViewProjectionMatrix() {
			delete c_viewProjMat;
			c_viewProjMat = c_ortho->c_projectionMatrix->operator*(c_transform->getModelMatrix());
		}

		Ortho::Ortho(Matrix3f * proj) : c_projectionMatrix(proj) {}

		Ortho * Ortho::square_pix(float pixel_per_tile, int width, int height) {
			Matrix3f *proj = new Matrix3f();
			float tile2 = pixel_per_tile * 2;
			proj->initOrtho(-width / (tile2), width / (tile2), -height / (tile2), height / (tile2));
			return new Ortho(proj);
		}

		Ortho * Ortho::square_num(float tiles_per_height, float aspectratio) {
			Matrix3f *proj = new Matrix3f();
			float tile2 = tiles_per_height / 2;
			float w = aspectratio * tile2;
			proj->initOrtho(-w, w, -tile2, tile2);
			return new Ortho(proj);
		}
	}
}