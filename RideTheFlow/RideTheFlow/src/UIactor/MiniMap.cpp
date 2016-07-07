#include "MiniMap.h"
#include "FlowRoot.h"
#include "PlayerArrow.h"
#include "MiniMapParameter.h"
#include "../math/Math.h"
#include "../world/IWorld.h"

#include "../graphic/Model.h"

MiniMap::MiniMap(IWorld& world_) :
UIActor(world_)
{
	parameter.id = UI_ID::MINIMAP_UI;
	parameter.isDead = false;

	// プレイヤー取得 プレイヤークラスでAddも可
	player = static_cast<Player*>(world.GetPlayer().get());
	world.UIAdd(UI_ID::PLAYER_ARROW_UI, std::make_shared<PlayerArrow>(world, player));
}

MiniMap::~MiniMap()
{
	player = nullptr;
}

void MiniMap::Update()
{

}

void MiniMap::Draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::MINIMAP_SPRITE, MAP_DRAW_POSITION, Vector2(256, 256), 1.0f, MINI_MAP_SCALE, 0, true, false);
}
