#include <string>
#include "AllInclude.h"
#include "scene\SceneManager.h"
#include "scene\GamePlayScene.h"
#include  "scene\TitleScene.h"

#ifndef _GAME
#define _GAME TRUE
#endif /* _GAME */

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	//�E�B���h�E���[�h��
	ChangeWindowMode(TRUE);
	//�w�i�F�ύX

	// ��ʃ��[�h�̃Z�b�g
	SetGraphMode(1024,768,16);
	SetBackgroundColor(0, 0, 0);
	if( DxLib_Init() == -1 )	// �c�w���C�u��������������
	{
		return -1;				// �G���[���N�����璼���ɏI��
	}

	SceneManager sm;
	sm.Add(Scene::GamePlay, std::make_shared<GamePlayScene>());
	sm.Add(Scene::Title, std::make_shared<TitleScene>());
	sm.SetScene(Scene::Title);

	// �`����ʂ𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

	// ���[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//��ʂ���x�폜
		ClearDrawScreen();
		sm.Change();
		sm.Update();
		sm.Draw();

		ScreenFlip();
	}
	sm.End();
	DxLib_End();				// �c�w���C�u�����g�p�̏I������
	return 0;
}