#include "stdafx.h"
#include "Utilities.h"

inline float Vec3::Length()
{
	return D3DXVec3Length(this);
}

inline Vec3* Vec3::Normalize()
{
	return static_cast<Vec3*>(D3DXVec3Normalize(this, this));
}

inline float Vec3::Dot(const Vec3 &anotherVector)
{
	return D3DXVec3Dot(this, &anotherVector);
}

inline Vec3 Vec3::Cross(const Vec3 &anotherVector) const
{
	Vec3 out;
	D3DXVec3Cross(&out, this, &anotherVector);
	return out;
}

Vec3::Vec3(D3DXVECTOR3 &anotherVector)
{
	x = anotherVector.x;
	y = anotherVector.y;
	z = anotherVector.z;
}

Vec3::Vec3(const float _x, const float _y, const float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

inline Vec3::Vec3(const class Vec4 &anotherVector)
{
	x = anotherVector.x;
	y = anotherVector.y;
	z = anotherVector.z;
}