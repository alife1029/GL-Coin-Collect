#pragma once

#include <array>
#include "Vector2.h"

#define PI 3.141592f

namespace engine {

	struct ENGINE_API Matrix3 : public std::array<float, 9>
	{
		Matrix3();
		static Matrix3 Identity();

		// Transform
		static Matrix3 Scale(const Vector2& scale);
		static Matrix3 Rotate(float angle);
		static Matrix3 Translate(const Vector2& position);

		// Operators
		Matrix3 operator* (const Matrix3& mat);
		Matrix3 operator*= (const Matrix3& mat);
	};

}