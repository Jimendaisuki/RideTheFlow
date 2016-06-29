#include "IScene.h"
#include "ISceneMediator.h"
#include "../world/World.h"
#include <vector>

class  EndhingScene :public IScene{
public:
	enum ENDING_STATUS
	{
		ENDING_BEGIN = 0,

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

	float		angle;
	Vector3		cameraPos;
	Vector3		targetPos;
};