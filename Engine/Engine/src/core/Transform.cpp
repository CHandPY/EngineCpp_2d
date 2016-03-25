#include "Transform.h"

namespace engine {
	namespace core {

		Transform::Transform(Vector2f *pos, float rot, Vector2f *scale, bool inver_pos) :
			t_position(pos),
			t_rotation(rot),
			t_scale(scale),
			t_invertPos(inver_pos) {
			t_modelMatrix = new Matrix3f();
			t_hasCanged = true;
		}

		Transform::Transform(Vector2f *pos, Vector2f *scale) : Transform(pos, 0, scale) {}

		Transform::~Transform() {
			delete t_modelMatrix;
			delete t_position;
			delete t_scale;
		}

		Vector2f * Transform::getPos() {
			return t_position;
		}

		Vector2f * Transform::getScale() {
			return t_scale;
		}

		float Transform::getRotation() {
			return t_rotation;
		}

		Matrix3f * Transform::getModelMatrix() {
			if (hasChanged()) {
				computeModelMatrix();
				t_hasCanged = false;
			}
			return t_modelMatrix;
		}

		bool Transform::hasChanged() {
			return (t_hasCanged = t_hasCanged || t_position->hasChanged() || t_scale->hasChanged());
		}

		Transform * Transform::negated_pos() {
			return new Transform(t_position->operator-(), t_rotation, t_scale);
		}

		void Transform::setPos(Vector2f *pos) {
			t_hasCanged = true;
			this->t_position = pos;
		}

		void Transform::setScale(Vector2f *scale) {
			t_hasCanged = true;
			this->t_scale = scale;
		}

		void Transform::setRotation(float rotation) {
			t_hasCanged = true;
			this->t_rotation = rotation;
		}

		void Transform::computeModelMatrix() {
			Matrix3f *mat_p = new Matrix3f(), *mat_r = new Matrix3f(), *mat_s = new Matrix3f();
			mat_p->initTranslation(t_position);
			mat_s->initScale(t_scale);
			mat_r->initRotation(t_rotation);
			t_modelMatrix->initTransform(mat_s, mat_r, mat_p);
			delete mat_p;
			delete mat_s;
			delete mat_r;
		}
	}
}
