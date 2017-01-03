#include <math.h>
#include "mathutils.h"
#include "logger.h"

float Math::Distance(const Vec3D& a, const Vec3D& b)
{
	float diffX = (a.x - b.x);
	float diffY = (a.y - b.y);
	float diffZ = (a.z - b.z);
	return sqrtf(diffX*diffX + diffY*diffY + diffZ*diffZ);
}

float Math::DotProduct(const Vec3D& a, const Vec3D& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

bool Math::WorldToScreen(Vec3D& pos, Vec3D& camPos, Vec3D& camFwd, Vec3D& camUp, Vec3D& camRight, float fovX, unsigned int width, unsigned int height, D3DXVECTOR2& screenPos)
{
	float fovY = fovX / ((float) width / height);
	Vec3D local = pos - camPos;
	Vec3D transformed;

	transformed.x = Math::DotProduct(local, -camRight);
	transformed.y = Math::DotProduct(local, camUp);
	transformed.z = Math::DotProduct(local, camFwd);

	float centerX = width / 2.0f;
	float centerY = height / 2.0f;

	if (transformed.z < 0.01f)
	{
		return false;
	}
	else
	{
		screenPos.x = centerX * (1 - (transformed.x / fovX / transformed.z));
		screenPos.y = centerY * (1 - (transformed.y / fovY / transformed.z));
		return true;
	}
}
