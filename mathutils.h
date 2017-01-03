#pragma once

#include <d3dx9.h>

struct Vec3D
{
	float x;
	float y;
	float z;

	Vec3D operator -() const
	{
		return { -this->x, -this->y, -this->z };
	}

	Vec3D operator -(const Vec3D& vec) const
	{
		return { this->x - vec.x, this->y - vec.y, this->z - vec.z };
	}
};

class Math
{
public:
	static float Distance(const Vec3D& a, const Vec3D& b);
	static float DotProduct(const Vec3D& a, const Vec3D& b);
	static bool WorldToScreen(Vec3D& pos, Vec3D& camPos, Vec3D& camFwd, Vec3D& camUp, Vec3D& camRight, float fovX, unsigned int width, unsigned int height, D3DXVECTOR2& screenPos);
};