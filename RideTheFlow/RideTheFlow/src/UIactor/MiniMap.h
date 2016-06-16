#pragma once
#include "UIActor.h"
#include "../actor/Player.h"

class MiniMap : public UIActor
{
public:
	MiniMap(IWorld& world_);
	~MiniMap();
	virtual void Update() override;
	virtual void Draw() const override;
	
private:
	// �v���C���[�Q�ƃ|�C���^
	Player*	player;
};