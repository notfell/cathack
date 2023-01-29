#pragma once

struct position
{
	float x;
	float y;

	position() : x(0.0f), y(0.0f) {}
	position(float _x, float _y) : x(_x), y(_y) {}
};

struct size
{
	float w;
	float h;

	size() : w(0.0f), h(0.0f) {}
	size(float _w, float _h) : w(_w), h(_h) {}
};

struct color
{
	int r;
	int g;
	int b;
	int a;

	color() : r(0), g(0), b(0), a(255) {}
	color(int _r, int _g, int _b, int _a = 255) : r(_r), g(_g), b(_b), a(_a) {}
};

struct vector3
{
	float x;
	float y;
	float z;

	vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

	friend vector3 operator - (vector3 _leftValue, vector3 _rightValue)
	{
		vector3 result;

		result.x = _leftValue.x;
		result.y = _leftValue.y;
		result.z = _leftValue.z;

		result.x -= _rightValue.x;
		result.y -= _rightValue.y;
		result.z -= _rightValue.z;

		return result;
	}

	float length() const { return sqrtf(x * x + y * y + z * z); }
};

struct quaternion
{
	float x;
	float y;
	float z;
	float w;

	quaternion() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
	quaternion(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
};

struct viewMatrix
{
	float matrix[16];
};