#include "IScene.h"
#include "ISceneMediator.h"
#include "../world/World.h"
#include "../graphic/Movie.h"
#include <vector>
#include <array>

class  PVScene :public IScene{
public:
	//コンストラクタ 
	PVScene();
	//デストラクタ
	~PVScene();

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
	bool	mIsEnd;
	World	wa;

	Movie	movie;
	const float PV_END_TIME = 94.0f;
	int MovieHandle;
};