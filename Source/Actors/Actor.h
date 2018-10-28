#pragma once
#include "../Utilities.h"
#include <map>

// Stubs
#define ComponentId int
#define StrongActorComponentPtr int*

class Actor
{
	friend class ActorFactory;
	typedef std::map<ComponentId, StrongActorComponentPtr> ActorComponents;

	ActorId m_id;
	ActorComponents m_components;

protected:
	//StrongActorPtr m_pOwner;
	Vec3 m_position;

public:
	explicit Actor(ActorId id);
	~Actor();

	//bool Init(TiXmlElement* data);
	void PosInit();
	void Destroy();

	virtual ComponentId VGetComponentId() const = 0;

	const Vec3& GetPosition() const 
	{
		return m_position;
	}

	const ActorId GetId()
	{
		return m_id;
	}

private:
	//void SetOwner(StrongActorPtr pOwner) { m_pOwner = pOwner; }
};