#pragma once

#define Model int
#define Texture int

#include <d3d10_1.h>
#include <D3DX10math.h>

typedef unsigned long ActorId;

struct Vec3 : public D3DXVECTOR3
{
public:
	inline float Length();
	inline Vec3 *Normalize();
	inline float Dot(const Vec3 &anotherVector);
	inline Vec3 Cross(const Vec3 &anotherVector) const;

	Vec3(D3DXVECTOR3 &anotherVector);
	Vec3() : D3DXVECTOR3() {}
	Vec3(const float _x, const float _y, const float _z);
	inline Vec3(const class Vec4 &anotherVector);
};

class Vec4 : public D3DXVECTOR4
{
	// Don't need a while
};