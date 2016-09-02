#include "IScene.h"
#include "ISceneMediator.h"
#include "../world/World.h"
#include <vector>
#include <array>

class  EndhingScene :public IScene{
public:
	enum ENDING_STATUS
	{
		ENDING_DRAGON_OUT	= 1,
		ENDING_CLEAR		= 2,
		ENDING_END			= 3,
	};

public:
		//コンストラクタ 
	EndhingScene();
	//デストラクタ
	~EndhingScene();

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
	void TornadoCalculation();
	void VertexMove(VERTEX2D vertexs_[], int count_, float time_);

private:
	bool mIsEnd;
	World wa;
	ENDING_STATUS	status;

	float		length;
	float		seVol;
	float		angle;
	float		currentFog;
	Vector3		cameraPos;
	Vector3		targetPos;
	Vector3		velocity;

	/* 竜巻ポリゴン用データ */
	int			texhandle;
	int			stormAlpha;
	int			count_1;
	int			count_2;
	float		stormAlphaTime;
	float		amount_1;
	float		amount_2;
	std::array<VERTEX2D, 6>	Vertex2D_1;
	std::array<VERTEX2D, 6>	Vertex2D_2;

	/* タイトルテキスト用データ */
	float	titleAlpha;
	bool	isTitle;
	bool	isPass;
};