#define NOMINMAX
#include"SceneManager.h"
#include"IScene.h"
#include <algorithm>
#include "../UIactor/fadePanel/FadePanel.h"
#include "../time/Time.h"
#include "../input/GamePad.h"
#include "../input/Keyboard.h"

const int SceneManager::MaxStageCount = 7;

//�R���X�g���N�^
SceneManager::SceneManager() :
mStageCount(1),
timer_(0.0f),
resetFalg(false)
{
}

//�X�V�O������
void SceneManager::Initialize(){
	End();
	resetFalg = false;
	mScenes.clear();
}

//�X�V
void SceneManager::Update(){
	mCurrentScene->Update();
	timer_ += Time::DeltaTime;
	if (Keyboard::GetInstance().AnyTriggerDown() ||
		GamePad::GetInstance().AnyTriggerDown())
	{
		timer_ = 0.0f;
	}
	FadePanel::GetInstance().Update();
}

//�`��
void SceneManager::Draw() const{
	mCurrentScene->Draw();
	FadePanel::GetInstance().Draw();
}

//�I��
void SceneManager::End(){
	mCurrentScene->End();
}

void SceneManager::Change()
{
	if (GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM7)&&
		GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM8) &&
		mCurrentScene->GetCurrentScene()!=Scene::Title)
	{
		resetFalg = true;
	}

	if (timer_ >= SCENE_END_TIME||resetFalg)
	{
		if (FadePanel::GetInstance().IsFullBlack())
		{
			Change(Scene::Title);
			return;
		}
		if (!FadePanel::GetInstance().IsAction())
		{
			FadePanel::GetInstance().SetOutTime(0.5f);
			FadePanel::GetInstance().FadeOut();
			return;
		}
	}

	

	if (mCurrentScene->IsEnd())
	{
		Change(mCurrentScene->Next());
	}
}

//�V�[���̒ǉ�
void SceneManager::Add(Scene name, const IScenePtr& scene){
	mScenes[name] = scene;
}

void SceneManager::SetScene(Scene name){
	FadePanel::GetInstance().Initialize();
	mCurrentScene = mScenes[name];
	mCurrentScene->Initialize();
	FadePanel::GetInstance().FadeIn();
}

//�V�[���̕ύX
void SceneManager::Change(Scene name){
	Scene now = Scene::None;
	for (auto& i : mScenes)
	{
		if (mCurrentScene == i.second)
			now = i.first;
	}
	if (name == now)
		return;
	
	End();
	FadePanel::GetInstance().Initialize();

	mCurrentScene = mScenes[name];
	mCurrentScene->Initialize();
	timer_ = 0.0f;
	resetFalg = false;
	FadePanel::GetInstance().FadeIn();
}

// ���������w�肷��
void SceneManager::Init(Scene name)
{
	mScenes.at(name)->Initialize();
}

// �I���������w�肷��
void SceneManager::Final(Scene name)
{
	mScenes.at(name)->End();
}

static int _Clamp(int t, int min, int max)
{
	return std::min(max, std::max(t, min));
}

void SceneManager::SetStageCount(int n)
{
	mStageCount = _Clamp(n, 0, SceneManager::MaxStageCount);
}