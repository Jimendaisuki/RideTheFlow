#include "IScene.h"
#include "ISceneMediator.h"
#include "../world/World.h"
#include "../graphic/Movie.h"
#include <vector>
#include <array>

class  PVScene :public IScene{
public:
	//�R���X�g���N�^ 
	PVScene();
	//�f�X�g���N�^
	~PVScene();

	//�X�V�O������
	virtual void Initialize() override;
	//�X�V����
	virtual void Update()override;
	//�`�揈��
	virtual void Draw() const override;
	//�I�����Ă��邩�H
	virtual bool IsEnd() const override;
	//���̃V�[����Ԃ�
	virtual Scene Next() const override;
	//�I��������
	virtual void End()override;


private:
	bool	mIsEnd;
	World	wa;

	Movie	movie;
	const float PV_END_TIME = 94.0f;
	int MovieHandle;
};