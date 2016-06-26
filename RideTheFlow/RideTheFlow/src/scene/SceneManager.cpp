#define NOMINMAX
#include"SceneManager.h"
#include"IScene.h"
#include <algorithm>
#include "../UIactor/fadePanel/FadePanel.h"

const int SceneManager::MaxStageCount = 7;

//コンストラクタ
SceneManager::SceneManager() :
	mStageCount(1){
}

//更新前初期化
void SceneManager::Initialize(){
	End();
	mScenes.clear();
}

//更新
void SceneManager::Update(){
	mCurrentScene->Update();
	FadePanel::GetInstance().Update();
}

//描画
void SceneManager::Draw() const{
	mCurrentScene->Draw();
	FadePanel::GetInstance().Draw();
}

//終了
void SceneManager::End(){
	mCurrentScene->End();
}

void SceneManager::Change()
{
	if (mCurrentScene->IsEnd())
	{
		Change(mCurrentScene->Next());
	}
}

//シーンの追加
void SceneManager::Add(Scene name, const IScenePtr& scene){
	mScenes[name] = scene;
}

void SceneManager::SetScene(Scene name){
	FadePanel::GetInstance().Initialize();
	mCurrentScene = mScenes[name];
	mCurrentScene->Initialize();
	FadePanel::GetInstance().FadeIn();
}

//シーンの変更
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

	FadePanel::GetInstance().FadeIn();
}

// 初期化を指定する
void SceneManager::Init(Scene name)
{
	mScenes.at(name)->Initialize();
}

// 終了処理を指定する
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