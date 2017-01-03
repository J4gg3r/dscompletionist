#pragma once

#include "mathutils.h"

#define BOX_SIZE 0.25f

class Box
{
public:
	Vec3D vertices[8];

	void InitWithCenter(const Vec3D& center)
	{
		float topLeftX = center.x + BOX_SIZE;
		float topLeftY = center.y + BOX_SIZE;
		float topLeftZ = center.z + BOX_SIZE;
		float bottomRightX = center.x - BOX_SIZE;
		float bottomRightY = center.y - BOX_SIZE;
		float bottomRightZ = center.z - BOX_SIZE;

		vertices[0].x = topLeftX;
		vertices[0].y = topLeftY;
		vertices[0].z = topLeftZ;
		
		vertices[1].x = bottomRightX;
		vertices[1].y = topLeftY;
		vertices[1].z = topLeftZ;
		
		vertices[2].x = bottomRightX;
		vertices[2].y = bottomRightY;
		vertices[2].z = topLeftZ;

		vertices[3].x = topLeftX;
		vertices[3].y = bottomRightY;
		vertices[3].z = topLeftZ;

		vertices[4].x = topLeftX;
		vertices[4].y = topLeftY;
		vertices[4].z = bottomRightZ;

		vertices[5].x = bottomRightX;
		vertices[5].y = topLeftY;
		vertices[5].z = bottomRightZ;

		vertices[6].x = bottomRightX;
		vertices[6].y = bottomRightY;
		vertices[6].z = bottomRightZ;

		vertices[7].x = topLeftX;
		vertices[7].y = bottomRightY;
		vertices[7].z = bottomRightZ;
	}
};