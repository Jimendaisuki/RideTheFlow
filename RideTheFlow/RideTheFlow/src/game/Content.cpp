#include "Content.h"
#include "../game/WorkFolder.h"
#include "../graphic/Model.h"
#include "../graphic/Sprite.h"
#include "../sound/Sound.h"
#include "../Def.h"
#include "../math/Math.h"

// �摜��ǂݍ���
void Content::LoadSprite(Sprite& sprite, Model& model)
{
	WorkFolder::SetWorkFolder("res/Sprite/");
	sprite.Load("body.png");
	sprite.Load("images.png");
	//sprite.Load("title.png");
	//model.Load2D("particleSprite.png");
}

// �R�c���f����ǂݍ���
void Content::LoadModel(Model& model, bool async)
{
	WorkFolder::SetWorkFolder("Resources/Model/");

	//model.Load("m1.pmx", async);
	//model.Load("m2.x", async);
	//model.Load("m3.pmd", async);
}

// ���y��ǂݍ���
void Content::LoadSound(Sound& sound)
{
	WorkFolder::SetWorkFolder("res/Sound/");

	//sound.LoadBGM("title.mp3");

	//sound.LoadSE("se.wav", 0.9f);

	sound.SetAllBGMVolume(BGMVOLUME);
	sound.SetAllSEVolume(SEVOLUME);
}

void Content::EnableASync()
{
	SetUseASyncLoadFlag(TRUE);
}
void Content::DisableASync()
{
	SetUseASyncLoadFlag(FALSE);
}

template <typename T>
int Content::GetASyncLoadCount(T& content)
{
	return (content.GetCount() - GetASyncLoadNum() + 1);
}
template <>
int Content::GetASyncLoadCount(Sound& content)
{
	return ((content.GetCountBGM() + content.GetCountSE()) - GetASyncLoadNum() + 1);
}
int Content::GetASyncLoadAllCount(Model& model, Sprite& sprite, Sound& sound)
{
	auto count = model.GetCount() + sprite.GetCount() + sound.GetCountBGM() + sound.GetCountSE();
	return (count - GetASyncLoadNum() + 1);
}
bool Content::IsASync()
{
	return GetASyncLoadNum() > 0;
}