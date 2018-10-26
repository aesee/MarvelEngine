#pragma once
#include "Actor.h"

class RenderableActor : public Actor
{
	Model* m_pModel;
	Texture* m_pTexture;

public:
	virtual bool VDraw() = 0;
};