#include "Transform.h"

namespace nc {

	void Transform::Update() {

		Matrix22 mxs;
		mxs.Scale(scale);

		Matrix22 mxr;
		mxr.Rotate(rotation);

		matrix = mxs * mxr;

	}
}