// 入力管理クラス
#include "Keyboard.h"

/// コンストラクタ
Keyboard::Keyboard()
{
	for (int i = 0; i < 256; i++)
	{
		m_onkey[i] = 0;
		m_offkey[i] = 0;
	}
}

/// キーを押した時のトリガー判定
bool Keyboard::KeyTriggerDown(int key)
{
	if (m_onkey[key] == 1)
	{
		return true;
	}
	return false;
}

/// キーを押した時のステート判定
bool Keyboard::KeyStateDown(int key)
{
	if (m_keycode[key] == 1)
	{
		return true;
	}
	return false;
}

/// キーを離した時のトリガー判定
bool Keyboard::KeyTriggerUp(int key)
{
	if (m_offkey[key] == 1)
	{
		return true;
	}
	return false;
}

/// キーを離した時のステート判定
bool Keyboard::KeyStateUp(int key)
{
	if (m_keycode[key] == 0)
	{
		return true;
	}
	return false;
}

/// いずれかのキーが入力された瞬間か調べる
bool Keyboard::AnyTriggerDown()
{
	for (int i = 0; i < 256; i++)
	{
		if (m_onkey[i] == 1)
		{
			return true;
		}
	}

	return false;
}

/// いずれかのキーが入力されているか調べる
bool Keyboard::AnyStateDown()
{
	for (int i = 0; i < 256; i++)
	{
		if (m_keycode[i] == 1)
		{
			return true;
		}
	}

	return false;
}

/// いずれかのキーが離れた瞬間か調べる
bool Keyboard::AnyTriggerUp()
{
	for (int i = 0; i < 256; i++)
	{
		if (m_offkey[i] == 1)
		{
			return true;
		}
	}

	return false;
}

/// いずれかのキーが離れているか調べる
bool Keyboard::AnyStateUp()
{
	for (int i = 0; i < 256; i++)
	{
		if (m_keycode[i] == 0)
		{
			return true;
		}
	}

	return false;
}

/// 更新処理
void Keyboard::Update()
{
	GetHitKeyStateAll(m_keycode);

	for (int i = 0; i < 256; i++)
	{
		UpdateKey(m_keycode[i], i);
	}
}

void Keyboard::UpdateKey(char key, int num)
{
	// 押されていれば
	if (key != 0)
	{
		m_offkey[num] = 0;
		m_onkey[num]++;
	}
	// 押されていなければ
	else
	{
		m_onkey[num] = 0;
		m_offkey[num]++;
	}
}