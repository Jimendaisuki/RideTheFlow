#include "game\Game1.h"
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
	Game1 game;

	try
	{
		game.Run();
	}
	catch (const std::string& error)
	{
		MessageBox(nullptr, error.c_str(), "�G���[", MB_OK);
		game.Finalize();
		DxLib_End();
	}
	catch (std::runtime_error& e) /* ���������O���f����Ă����� */
	{
		MessageBox(nullptr, e.what(), "�G���[", MB_OK);
		game.Finalize();
		DxLib_End();
	}
	return 0;
}