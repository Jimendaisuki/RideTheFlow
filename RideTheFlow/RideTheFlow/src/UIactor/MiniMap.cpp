#include "MiniMap.h"
#include "FlowRoot.h"
#include "PlayerArrow.h"
#include "../math/Math.h"
#include "../world/IWorld.h"

#include "../graphic/Model.h"

const float Scale = 0.6f;
const Vector2 MAP_POSITION = Vector2(WINDOW_WIDTH, WINDOW_HEIGHT) - Vector2(256) * Scale;
const Vector2 StageSize = Vector2(3000, 3000);
const float ReSIZE = 256.0f / StageSize.x * Scale;

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
	Sprite::GetInstance().Draw(SPRITE_ID::MINIMAP_SPRITE, MAP_POSITION, Vector2(256, 256), 1.0f, Scale, 0, true, false);
}
