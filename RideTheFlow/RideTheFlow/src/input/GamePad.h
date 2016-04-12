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
	/// 指定のパッドの指定のボタンが入力された瞬間か調べる
	///</summary>
	bool ButtonTriggerDown(int button, int pad = DX_INPUT_PAD1);
	///<summary>
	/// 指定のパッドの指定のボタンが入力されているか調べる
	///</summary>
	bool ButtonStateDown(int button, int pad = DX_INPUT_PAD1);
	///<summary>
	/// 指定のパッドの指定のボタンが離れた瞬間か調べる
	///</summary>
	bool ButtonTriggerUp(int button, int pad = DX_INPUT_PAD1);
	///<summary>
	/// 指定のパッドの指定のボタンが離れているか調べる
	///</summary>
	bool ButtonStateUp(int button, int pad = DX_INPUT_PAD1);
	/// <summary>
	/// いずれかのボタンが入力された瞬間か調べる
	/// </summary>
	bool AnyTriggerDown(int pad = DX_INPUT_PAD1);
	/// <summary>
	/// いずれかのボタンが入力されているか調べる
	/// </summary>
	bool AnyStateDown(int pad = DX_INPUT_PAD1);
	/// <summary>
	/// いずれかのボタンが離れた瞬間か調べる
	/// </summary>
	bool AnyTriggerUp(int pad = DX_INPUT_PAD1);
	/// <summary>
	/// いずれかのボタンが離れているか調べる
	/// </summary>
	bool AnyStateUp(int pad = DX_INPUT_PAD1);
	///<summary>
	/// 指定のパッドのPOVが入力された瞬間の方向を受け取る
	///</summary>
	int POVTriggerDown(int pad = DX_INPUT_PAD1);
	///<summary>
	/// 指定のパッドのPOVが入力された方向を受け取る
	///</summary>
	int POVStateDown(int pad = DX_INPUT_PAD1);
	///<summary>
	/// 指定のパッドのアナログスティックの入力具合を調べる
	/// (X = -1.0～1.0, Y = -1.0～1.0)
	///</summary>
	Vector2 Stick(int pad = DX_INPUT_PAD1);
	///<summary>
	/// 指定のパッドの右アナログスティックの入力具合を調べる
	/// (X = -1.0～1.0, Y = -1.0～1.0)
	///</summary>
	Vector2 RightStick(int pad = DX_INPUT_PAD1);
	///<summary>
	/// 指定のパッドの振動を開始する
	///</summary>
	void VibrationStart(int power, int time, int pad = DX_INPUT_PAD1);
	///<summary>
	/// 指定のパッドの振動を終了する
	///</summary>
	void VibrationEnd(int pad = DX_INPUT_PAD1);
	void Update();
private:
	void Exception(int pad, int button);

	//std::unordered_map<int, std::array<int, 50000>> m_currentbutton;// 現在のボタン状態
	//std::unordered_map<int, std::array<int, 50000>> m_previosbutton;// 1フレーム前のボタン状態

	//<パッド番号, <PAD_INPUT_1など, カウンター>
	std::unordered_map<int, std::unordered_map<int, int>> m_onbuttons;
	std::unordered_map<int, std::unordered_map<int, int>> m_offbuttons;

	std::unordered_map<int, int> m_onpovbuttons;

	std::vector<int> m_inputbuttons;// ボタン入力判定達
	std::vector<int> m_pads;// パッド番号達
};