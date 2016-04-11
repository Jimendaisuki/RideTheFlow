#include "WorldActor.h"
#include<algorithm>
#include "../actor/ActorID.h"

WorldActor::WorldActor(){
	for (int i = ACTOR_ID::BEGIN; i <= ACTOR_ID::END; ++i)
		managers.emplace(ACTOR_ID(i), std::make_shared<ActorManager>());
}
WorldActor::~WorldActor(){

}
void WorldActor::Update(){
	//�S�L�����A�b�v�f�[�g
	std::for_each(managers.begin(), managers.end(),
		[](ActorManagerPair pair){pair.second->Update(); });
	
	managers[ACTOR_ID::PLAYER]->Collide(*managers[ACTOR_ID::ENEMY]);

	//����ł���̂�����
	std::for_each(managers.begin(), managers.end(),
		[](ActorManagerPair pair){pair.second->Remove(); });
}
void WorldActor::Draw() const{
	//�S�L�����`��
	std::for_each(managers.begin(), managers.end(),
		[](ActorManagerPair pair){pair.second->Draw(); });
}
void WorldActor::Add(ACTOR_ID id, ActorPtr actor){
	managers[id]->Add(actor);
}
void WorldActor::Clear(){
	//�S�L�����N���A
	std::for_each(managers.begin(), managers.end(),
		[](ActorManagerPair pair){pair.second->Clear(); });
}