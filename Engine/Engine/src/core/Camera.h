#pragma once

#include "Matrix3f.h"
#include "Vector2f.h"
#include "Transform.h"

namespace engine {
	namespace graphics {

		struct Ortho {
			Matrix3f *c_projectionMatrix;

			Ortho(Matrix3f *proj);

			static Ortho *square_pix(float pixel_per_tile, int width, int height);
			static Ortho *square_num(float tiles_per_height, float aspectratio);
			static Ortho *square_num_width(float tiles_per_width, float aspectratio);
			static Ortho *byValues(float left, float right, float bottom, float top);
		};

		class Camera {

		public:
			Camera(Transform *transform, Ortho *ortho);
			~Camera();

			Transform * transform();
			Matrix3f * getViewProjectionMatrix();

		private:
			Transform *c_transform;
			Ortho *c_ortho;
			Matrix3f *c_viewProjMat;

			void computeViewProjectionMatrix();

		};
	}
}