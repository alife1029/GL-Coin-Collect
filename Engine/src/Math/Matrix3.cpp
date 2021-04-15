#include "Engine/Math/Matrix3.h"
#include <cmath>

namespace engine {

	Matrix3::Matrix3()
	{
		for (int i = 0; i < 9; i++)
			this->operator[](i) = 0.0f;
	}
	Matrix3 Matrix3::Identity()
	{
		/*
			1, 0, 0,
			0, 1, 0,
			0, 0, 1
		*/

		Matrix3 temp;

		temp[0 + 0 * 3] = 1.0f;
		temp[1 + 1 * 3] = 1.0f;
		temp[2 + 2 * 3] = 1.0f;

		return temp;
	}

	Matrix3 Matrix3::Scale(const Vector2& scale)
	{
		/*
			x, 0, 0,
			0, y, 0,
			0, 0, 1
		*/

		Matrix3 temp;

		temp[0 + 0 * 3] = scale.x;
		temp[1 + 1 * 3] = scale.y;
		temp[2 + 2 * 3] = 1.0f;

		return temp;
	}
	Matrix3 Matrix3::Rotate(float angle)
	{
		/*
			cos, -sin, 0,
			sin,  cos, 0,
			0,    0,   1
		*/

		angle = (angle * PI) / 180.0f;

		float cos = std::cos(angle);
		float sin = std::sin(angle);

		Matrix3 temp;

		temp[0 + 0 * 3] = cos;
		temp[1 + 0 * 3] = -sin;
		temp[0 + 1 * 3] = sin;
		temp[1 + 1 * 3] = cos;
		temp[2 + 2 * 3] = 1.0f;

		return temp;
	}
	Matrix3 Matrix3::Translate(const Vector2& position)
	{
		/*
			1, 0, x,
			0, 1, y,
			0, 0, 1
		*/

		Matrix3 temp = Identity();

		temp[2 + 0 * 3] = position.x;
		temp[2 + 1 * 3] = position.y;

		return temp;
	}

	Matrix3 Matrix3::operator* (const Matrix3& mat)
	{
		Matrix3 temp;

		for (size_t y = 0; y < 3; y++)
		{
			for (size_t x = 0; x < 3; x++)
			{
				float sum = 0.0f;

				for (size_t i = 0; i < 3; i++)
				{
					sum += this->operator[](i + y * 3) * mat[x + i * 3];
				}

				temp[x + y * 3] = sum;
			}
		}

		return temp;
	}

	Matrix3 Matrix3::operator*= (const Matrix3& mat)
	{
		Matrix3 temp = this->operator* (mat);

		for (size_t i = 0; i < 9; i++)
		{
			this->operator[](i) = temp[i];
		}

		return temp;
	}

}