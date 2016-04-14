#pragma once

#include "DxLib.h"
#include <array>

class Keyboard
{
private:
	Keyboard();
	~Keyboard() = default;

public:
	static Keyboard &GetInstance(){
		static Keyboard k;
		return k;
	}

	/// <summary>
	/// 指定されたキーが入力された瞬間か調べる
	/// </summary>
	bool KeyTriggerDown(int key);
	/// <summary>
	/// 指定されたキーが入力されているか調べる
	/// </summary>
	bool KeyStateDown(int key);
	/// <summary>
	/// 指定されたキーが離れた瞬間か調べる
	/// </summary>
	bool KeyTriggerUp(int key);
	/// <summary>
	/// 指定されたキーが離れているか調べる
	/// </summary>
	bool KeyStateUp(int key);
	/// <summary>
	/// いずれかのキーが入力された瞬間か調べる
	/// </summary>
	bool AnyTriggerDown();
	/// <summary>
	/// いずれかのキーが入力されているか調べる
	/// </summary>
	bool AnyStateDown();
	/// <summary>
	/// いずれかのキーが離れた瞬間か調べる
	/// </summary>
	bool AnyTriggerUp();
	/// <summary>
	/// いずれかのキーが離れているか調べる
	/// </summary>
	bool AnyStateUp();

	void Update();
private:
	void UpdateKey(char key, int num);
	char m_keycode[256];
	std::array<int, 256> m_onkey;
	std::array<int, 256> m_offkey;
};