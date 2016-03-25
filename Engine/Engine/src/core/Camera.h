#pragma once

#include "Matrix3f.h"
#include "Vector2f.h"
#include "Transform.h"

namespace engine {
	namespace graphics {

		struct Ortho {
			core::Matrix3f *c_projectionMatrix;

			Ortho(core::Matrix3f *proj);

			static Ortho *square_pix(float pixel_per_tile, int width, int height);
			static Ortho *square_num(float tiles_per_height, float aspectratio);
			static Ortho *square_num_width(float tiles_per_width, float aspectratio);
			static Ortho *byValues(float left, float right, float bottom, float top);
		};

		class Camera {

		public:
			Camera(core::Transform *transform, Ortho *ortho);
			~Camera();

			core::Transform * transform();
			core::Matrix3f * getViewProjectionMatrix();

		private:
			core::Transform *c_transform;
			Ortho *c_ortho;
			core::Matrix3f *c_viewProjMat;

			void computeViewProjectionMatrix();

		};
	}
}