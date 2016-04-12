#pragma once

#include "../math/Vector3.h"

class Camera
{
public:
	Camera();
	~Camera() = default;

	///<summary>
	/// �J�����̕`�拗����ݒ肷��i��O�����A�������j
	///</summary>
	void SetRange(float Near, float Far);

	///<summary>
	/// �J�����̎��_���W�֌W
	///</summary>
	class CPosition
	{
	public:
		Vector3 m_position;

		Vector3 get() const { return m_position; }
		void set(Vector3 position){ m_position = position; }
	};

	///<summary>
	/// �J�����̒����_���W�֌W
	///</summary>
	class CTarget
	{
	public:
		Vector3 m_target;

		Vector3 get() const { return m_target; }
		void set(Vector3 target){ m_target = target; }
	};

	///<summary>
	/// �J�����̏�����֌W
	///</summary>
	class CUp
	{
	public:
		Vector3 m_up;

		Vector3 get() const { return m_up; }
		void set(Vector3 up){ m_up = up; }
	};

	///<summary>
	/// �J�����̉�]�p�x��ݒ肷��i���W�A������]�p�x�E������]�p�x�E�P���]�p�x�j
	///</summary>
	void SetRotation(Vector3 rotate);

	///<summary>
	/// �J�����̍X�V����
	///</summary>
	void Update();

	///<summary>
	/// �w�肵�����W���J�����̎��E�ɓ����Ă��邩�ۂ�
	///</summary>
	int IsCheckView(Vector3 position);

public:
	CPosition Position;// ���_�̍��W
	CTarget Target;	// �����_�̍��W
	CUp Up;			// �����

};