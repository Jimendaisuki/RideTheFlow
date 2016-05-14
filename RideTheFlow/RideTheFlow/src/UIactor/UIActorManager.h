#pragma once
#include "../AllInclude.h"

#include "UIActorPtr.h"
#include "../graphic/Model.h"
#include "../graphic/Sprite.h"
#include<list>//�V�[�P���X�R���e�ilist����������
#include <functional>
#include "../actor/ID.h"
class UIActorManager
{
public:
	UIActorManager();
	~UIActorManager();
	void Update();
	void Draw() const;
	void Add(UIActorPtr actor);
	void Clear();
	void Remove();

	//�q������
	void EachActor(std::function<void(UIActor&)> func);
private:
	std::list<UIActorPtr> actorPtr;
};