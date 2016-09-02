#pragma once

#include "IScene.h"
#include "ISceneMediator.h"
#include "../world/World.h"
#include "../UIactor/menuPanel/MenuPanel.h"

class MenuScene :public IScene
{
enum MENU_STATUS
{
	BEGIN = 0,
	STANBAY = 1,
	END = 2
};

public:
	//コンストラクタ 
	MenuScene();
	//デストラクタ
	~MenuScene();

	//更新前初期化
	virtual void Initialize() override;
	//更新処理
	virtual void Update()override;
	//描画処理
	virtual void Draw() const override;
	//終了しているか？
	virtual bool IsEnd() const override;
	//次のシーンを返す
	virtual Scene Next() const override;
	//現在のシーンを返す
	virtual Scene GetCurrentScene() const override;
	//終了時処理
	virtual void End()override;

private:

private:
	bool mIsEnd;
	World wo;
	MENU_STATUS	status;

	MenuPanel	menu{ Scene::Menu };
};