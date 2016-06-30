#include "IScene.h"
#include "ISceneMediator.h"
#include "../world/World.h"
#include <vector>

class  EndhingScene :public IScene{
public:
	enum ENDING_STATUS
	{
		ENDING_BEGIN = 0,
		ENDING_FADEOUT = 1,
		ENDING_DRAGON_OUT = 2,
		ENDING_CLEAR = 3,
		ENDING_END = 4
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
	//終了時処理
	virtual void End()override;

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
};