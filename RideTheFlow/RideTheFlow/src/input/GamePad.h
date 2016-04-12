#pragma once

#include <Dxlib.h>
#include "../math/Vector2.h"
#include <unordered_map>
#include <vector>
#include <array>

class GamePad
{
public:
	GamePad();
	~GamePad() = default;
	///<summary>
	/// �w��̃p�b�h�̎w��̃{�^�������͂��ꂽ�u�Ԃ����ׂ�
	///</summary>
	bool ButtonTriggerDown(int button, int pad = DX_INPUT_PAD1);
	///<summary>
	/// �w��̃p�b�h�̎w��̃{�^�������͂���Ă��邩���ׂ�
	///</summary>
	bool ButtonStateDown(int button, int pad = DX_INPUT_PAD1);
	///<summary>
	/// �w��̃p�b�h�̎w��̃{�^�������ꂽ�u�Ԃ����ׂ�
	///</summary>
	bool ButtonTriggerUp(int button, int pad = DX_INPUT_PAD1);
	///<summary>
	/// �w��̃p�b�h�̎w��̃{�^��������Ă��邩���ׂ�
	///</summary>
	bool ButtonStateUp(int button, int pad = DX_INPUT_PAD1);
	/// <summary>
	/// �����ꂩ�̃{�^�������͂��ꂽ�u�Ԃ����ׂ�
	/// </summary>
	bool AnyTriggerDown(int pad = DX_INPUT_PAD1);
	/// <summary>
	/// �����ꂩ�̃{�^�������͂���Ă��邩���ׂ�
	/// </summary>
	bool AnyStateDown(int pad = DX_INPUT_PAD1);
	/// <summary>
	/// �����ꂩ�̃{�^�������ꂽ�u�Ԃ����ׂ�
	/// </summary>
	bool AnyTriggerUp(int pad = DX_INPUT_PAD1);
	/// <summary>
	/// �����ꂩ�̃{�^��������Ă��邩���ׂ�
	/// </summary>
	bool AnyStateUp(int pad = DX_INPUT_PAD1);
	///<summary>
	/// �w��̃p�b�h��POV�����͂��ꂽ�u�Ԃ̕������󂯎��
	///</summary>
	int POVTriggerDown(int pad = DX_INPUT_PAD1);
	///<summary>
	/// �w��̃p�b�h��POV�����͂��ꂽ�������󂯎��
	///</summary>
	int POVStateDown(int pad = DX_INPUT_PAD1);
	///<summary>
	/// �w��̃p�b�h�̃A�i���O�X�e�B�b�N�̓��͋�𒲂ׂ�
	/// (X = -1.0�`1.0, Y = -1.0�`1.0)
	///</summary>
	Vector2 Stick(int pad = DX_INPUT_PAD1);
	///<summary>
	/// �w��̃p�b�h�̉E�A�i���O�X�e�B�b�N�̓��͋�𒲂ׂ�
	/// (X = -1.0�`1.0, Y = -1.0�`1.0)
	///</summary>
	Vector2 RightStick(int pad = DX_INPUT_PAD1);
	///<summary>
	/// �w��̃p�b�h�̐U�����J�n����
	///</summary>
	void VibrationStart(int power, int time, int pad = DX_INPUT_PAD1);
	///<summary>
	/// �w��̃p�b�h�̐U�����I������
	///</summary>
	void VibrationEnd(int pad = DX_INPUT_PAD1);
	void Update();
private:
	void Exception(int pad, int button);

	//std::unordered_map<int, std::array<int, 50000>> m_currentbutton;// ���݂̃{�^�����
	//std::unordered_map<int, std::array<int, 50000>> m_previosbutton;// 1�t���[���O�̃{�^�����

	//<�p�b�h�ԍ�, <PAD_INPUT_1�Ȃ�, �J�E���^�[>
	std::unordered_map<int, std::unordered_map<int, int>> m_onbuttons;
	std::unordered_map<int, std::unordered_map<int, int>> m_offbuttons;

	std::unordered_map<int, int> m_onpovbuttons;

	std::vector<int> m_inputbuttons;// �{�^�����͔���B
	std::vector<int> m_pads;// �p�b�h�ԍ��B
};