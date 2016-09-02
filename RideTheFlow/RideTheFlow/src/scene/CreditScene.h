#pragma once

#include "IScene.h"
#include "ISceneMediator.h"
#include "../world/World.h"

class  CreditScene :public IScene{
public:
	//コンストラクタ 
	CreditScene();
	//デストラクタ
	~CreditScene();

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
	bool mIsEnd;
	World wa;
	int timeTest;
	Vector3 position;

	Vector2 leftstick;
	Vector2 rightstick;
	std::vector<bool>buttons;

	float armyCreateTimer;
	int armyCount;
};