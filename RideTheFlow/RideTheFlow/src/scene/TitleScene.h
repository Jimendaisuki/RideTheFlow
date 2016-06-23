#pragma once

#include "IScene.h"
#include "ISceneMediator.h"
#include "../world/World.h"

class  TitleScene :public IScene
{
enum TITLE_STATUS
{
	TITLE_BEGIN,
	TITLE_DRAGON_IN,
	TITLE_TEXTURE_IN,
	TITLE_STANDBY,
	TITLE_END
};

public:
	//コンストラクタ 
	TitleScene();
	//デストラクタ
	~TitleScene();

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
	//終了時処理
	virtual void End()override;

private:
	void TornadoCalculation();
	void VertexMove(VERTEX2D vertexs_[], int count_, float time_);
	bool IsStatusBegEnd() const;

private:
	float timer;
	bool mIsEnd;
	World wo,wo2;

	// タイトルステータス
	TITLE_STATUS status;

	/* 竜巻ポリゴン用データ */
	int			texhandle;
	int			stormAlpha;
	int			count_1;
	int			count_2;
	float		stormAlphaTime;
	float		amount_1;
	float		amount_2;
	VERTEX2D	Vertex2D_1[6];
	VERTEX2D	Vertex2D_2[6];

	/* タイトルテキスト用データ */
	float titleAlpha;
	float pressTextAlpha;
	float pressTextBackAlpha;
	float pressAlphaTime;
	float pressScale;

	/* 別スクリーン */
	int		screenHandle;
	int		screenPos;
	float	slideTime;
};