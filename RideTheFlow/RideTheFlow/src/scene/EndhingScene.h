#include "IScene.h"
#include "ISceneMediator.h"
#include "../world/World.h"

class  EndhingScene :public IScene{
public:
	//�R���X�g���N�^ 
	EndhingScene();
	//�f�X�g���N�^
	~EndhingScene();

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
	bool mIsEnd;
	World wa;
	int timeTest;
};