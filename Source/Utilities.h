#pragma once

#define Model int
#define Texture int

typedef unsigned long ActorId;

struct Vec3
{
	float X, Y, Z;

	inline Vec3(void) {}
	inline Vec3(const float x, const float y, const float z)
	{
		X = x; Y = y; Z = z;
	}

	inline Vec3 operator + (const Vec3& A) const
	{
		return Vec3(X + A.X, Y + A.Y, Z + A.Z);
	}

	inline Vec3 operator + (const float A) const
	{
		return Vec3(X + A, Y + A, Z + A);
	}

	inline float Dot(const Vec3& A) const
	{
		return A.X*X + A.Y*Y + A.Z*Z;
	}
};