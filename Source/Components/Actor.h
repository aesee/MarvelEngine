// Just stubs for now
#include "../Utilities.h"

class Actor
{
	ActorId m_id;

protected:
	Vec3 m_position;

public:
	const Vec3& GetPosition() const 
	{
		return m_position;
	}

	const ActorId GetId()
	{
		return m_id;
	}
};