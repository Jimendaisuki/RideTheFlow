#include "Game1.h"
#include "../AllInclude.h"
#include "../scene/SceneManager.h"
#include "../scene/TitleScene.h"
#include "../scene/GamePlayScene.h"
#include "../Def.h"
#include <thread>

Game1::Game1() :
mKeyboard(), 
mGamepad(),
effectTime(0.0f),
mAnime(mModel),
mPixelShader(-1), 
mRenderTarget(-1),
mIsLoaded(false)
{

}

void Game1::Initialize()
{
	mIsLoaded = false;
	mModel.Initialize();
	mSprite.Initialize();
	mSound.Initialize();

	// �t�@�C���̓ǂݍ���
	mContent.LoadSprite(mSprite, mModel);
	//mContent.LoadSound(mSound);
	//mContent.LoadModel(mModel,false);

	mSceneManager.Add(Scene::GamePlay, std::make_shared<GamePlayScene>());
	mSceneManager.Add(Scene::Title, std::make_shared<TitleScene>());
	mSceneManager.SetScene(Scene::Title);
}

void Game1::Update()
{
	// ���Ԃ��X�V
	mTime.Update();

	// ���͂̍X�V
	mKeyboard.Update();
	mGamepad.Update();
	// Esc�L�[���͂ŋ����I��
	if (mKeyboard.KeyTriggerDown(KEY_INPUT_ESCAPE) ||
		(mGamepad.ButtonStateDown(PAD_INPUT_9) && mGamepad.ButtonStateDown(PAD_INPUT_10)))
	{
		GameFrame::GameEnd();
		return;
	}

	// �V�[�����ύX����Ă��邩���m�F
	mSceneManager.Change();
	// �V�[�����X�V
	mSceneManager.Update();
}

void Game1::Draw()
{
	// �V�[����`��
	mSceneManager.Draw();
}

void Game1::Finalize()
{
	mSceneManager.End();
	DeleteShader(mPixelShader);
	DeleteGraph(mRenderTarget);
}