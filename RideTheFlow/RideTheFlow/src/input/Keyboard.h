#pragma once

#include "DxLib.h"
#include <array>

class Keyboard
{
public:
	Keyboard();
	~Keyboard() = default;
	/// <summary>
	/// �w�肳�ꂽ�L�[�����͂��ꂽ�u�Ԃ����ׂ�
	/// </summary>
	bool KeyTriggerDown(int key);
	/// <summary>
	/// �w�肳�ꂽ�L�[�����͂���Ă��邩���ׂ�
	/// </summary>
	bool KeyStateDown(int key);
	/// <summary>
	/// �w�肳�ꂽ�L�[�����ꂽ�u�Ԃ����ׂ�
	/// </summary>
	bool KeyTriggerUp(int key);
	/// <summary>
	/// �w�肳�ꂽ�L�[������Ă��邩���ׂ�
	/// </summary>
	bool KeyStateUp(int key);
	/// <summary>
	/// �����ꂩ�̃L�[�����͂��ꂽ�u�Ԃ����ׂ�
	/// </summary>
	bool AnyTriggerDown();
	/// <summary>
	/// �����ꂩ�̃L�[�����͂���Ă��邩���ׂ�
	/// </summary>
	bool AnyStateDown();
	/// <summary>
	/// �����ꂩ�̃L�[�����ꂽ�u�Ԃ����ׂ�
	/// </summary>
	bool AnyTriggerUp();
	/// <summary>
	/// �����ꂩ�̃L�[������Ă��邩���ׂ�
	/// </summary>
	bool AnyStateUp();

	void Update();
private:
	void UpdateKey(char key, int num);
	char m_keycode[256];
	std::array<int, 256> m_onkey;
	std::array<int, 256> m_offkey;
};