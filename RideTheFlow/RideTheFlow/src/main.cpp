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
	//ウィンドウモードへ
	ChangeWindowMode(TRUE);
	//背景色変更

	// 画面モードのセット
	SetGraphMode(1024,768,16);
	SetBackgroundColor(0, 0, 0);
	if( DxLib_Init() == -1 )	// ＤＸライブラリ初期化処理
	{
		return -1;				// エラーが起きたら直ちに終了
	}

	SceneManager sm;
	sm.Add(Scene::GamePlay, std::make_shared<GamePlayScene>());
	sm.Add(Scene::Title, std::make_shared<TitleScene>());
	sm.SetScene(Scene::Title);

	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	// ループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//画面を一度削除
		ClearDrawScreen();
		sm.Change();
		sm.Update();
		sm.Draw();

		ScreenFlip();
	}
	sm.End();
	DxLib_End();				// ＤＸライブラリ使用の終了処理
	return 0;
}