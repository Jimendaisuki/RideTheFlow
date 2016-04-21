#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <functional>
#include "../math/Vector2.h"
#include "../math/Vector3.h"
#include "../math/Vector4.h"
#include "../math/Matrix4.h"
#include "../actor/ID.h"

class Point;

class Model
{
private:
	Model() = default;
	~Model();

public:
	static Model &GetInstance(){
		static Model m;
		return m;
	}

	///<summary>
	/// ����������
	///</summary>
	void Initialize();

	///<summary>
	/// �R�c���f����ǂݍ��ށi���f��ID�j
	///</summary>
	void Load(const std::string& filename, const MODEL_ID& id, bool async = false, int param = 0, bool collinfo = false, bool reference = false, std::function<void(int)> end = nullptr);
	///<summary>
	/// �Q�c�摜��ǂݍ��ށi���f��ID�j
	///</summary>
	void Load2D(const std::string& filename, const MODEL_ID& id);
	///<summary>
	/// �����Q�c�摜��ǂݍ���(���f��ID�A�������A���Əc�̕������A1�R�}�̑傫��)
	///</summary>
	void Load2D(const std::string& filename, const MODEL_ID& id, int allnum, const Point& splitnum, const Point& size);
	///<summary>
	/// �ǂݍ��񂾃��f���A2D�摜�����ׂč폜����
	///</summary>
	void DeleteAll();

	///<summary>
	/// �R�c���f����`�悷��i���f��ID�A���W�j
	///</summary>
	void Draw(const MODEL_ID& id, const Vector3& position);
	///<summary>
	/// �R�c���f����`�悷��i���f��ID�A���W�A���ߓx�j
	///</summary>
	void Draw(const MODEL_ID& id, const Vector3& position, float alpha);
	///<summary>
	/// �R�c���f����`�悷��i���f��ID�A���W�A��]�ʁj
	///</summary>
	void Draw(const MODEL_ID& id, const Vector3& position, Vector3 rotate);
	///<summary>
	/// �R�c���f����`�悷��i���f��ID�A���W�A��]�ʁA�g�嗦�j
	///</summary>
	void Draw(const MODEL_ID& id, const Vector3& position, Vector3 rotate, const Vector3& scale);
	///<summary>
	/// �R�c���f����`�悷��i���f��ID�A���W�A���ߓx�A��]�ʁj
	///</summary>
	void Draw(const MODEL_ID& id, const Vector3& position, float alpha, Vector3 rotate);
	///<summary>
	/// �R�c���f����`�悷��i���f��ID�A���W�A���ߓx�A��]�ʁA�g�嗦�j
	///</summary>
	void Draw(const MODEL_ID& id, const Vector3& position, float alpha, Vector3 rotate, const Vector3& scale);
	///<summary>
	/// �R�c���f����`�悷��i���f��ID�A���W�A�f�B�t���[�Y�J���[�j
	///</summary>
	void Draw(const MODEL_ID& id, const Vector3& position, const Vector4& diffusecolor);
	///<summary>
	/// �R�c���f����`�悷��i���f��ID�A���W�A�f�B�t���[�Y�J���[�A�X�y�L�����[�J���[�j
	///</summary>
	void Draw(const MODEL_ID& id, const Vector3& position, const Vector4& diffusecolor, const Vector4& specularcolor);
	///<summary>
	/// �R�c���f����`�悷��i���f��ID�A���W�A���ߓx�A��]�ʁA�g�嗦�A�f�B�t���[�Y�J���[�A�X�y�L�����[�J���[�j
	///</summary>
	void Draw(const MODEL_ID& id, const Vector3& position, float alpha, Vector3 rotate, const Vector3& scale, const Vector4& diffusecolor, const Vector4& specularcolor);
	///<summary>
	/// �R�c���f����`�悷��i���f��ID�A���W�A�`��t���O�j
	///</summary>
	void Draw(const MODEL_ID& id, const Vector3& position, bool trans);
	///<summary>
	/// �R�c���f����`�悷��i���f��ID�A���W�A���ߓx�A�`��t���O�j
	///</summary>
	void Draw(const MODEL_ID& id, const Vector3& position, float alpha, bool trans);
	///<summary>
	/// �R�c���f����`�悷��i���f��ID�A���W�A��]�ʁA�`��t���O�j
	///</summary>
	void Draw(const MODEL_ID& id, const Vector3& position, Vector3 rotate, bool trans);
	///<summary>
	/// �R�c���f����`�悷��i���f��ID�A���W�A��]�ʁA�g�嗦�A�`��t���O�j
	///</summary>
	void Draw(const MODEL_ID& id, const Vector3& position, Vector3 rotate, const Vector3& scale, bool trans);
	///<summary>
	/// �R�c���f����`�悷��i���f��ID�A���W�A���ߓx�A��]�ʁA�`��t���O�j
	///</summary>
	void Draw(const MODEL_ID& id, const Vector3& position, float alpha, Vector3 rotate, bool trans);
	///<summary>
	/// �R�c���f����`�悷��i���f��ID�A���W�A���ߓx�A��]�ʁA�g�嗦�A�`��t���O�j
	///</summary>
	void Draw(const MODEL_ID& id, const Vector3& position, float alpha, Vector3 rotate, const Vector3& scale, bool trans);
	///<summary>
	/// �R�c���f����`�悷��i���f��ID�A���W�A�f�B�t���[�Y�J���[�A�`��t���O�j
	///</summary>
	void Draw(const MODEL_ID& id, const Vector3& position, const Vector4& diffusecolor, bool trans);
	///<summary>
	/// �R�c���f����`�悷��i���f��ID�A���W�A�f�B�t���[�Y�J���[�A�X�y�L�����[�J���[�A�`��t���O�j
	///</summary>
	void Draw(const MODEL_ID& id, const Vector3& position, const Vector4& diffusecolor, const Vector4& specularcolor, bool trans);
	///<summary>
	/// �R�c���f����`�悷��i���f��ID�A���W�A���ߓx�A��]�ʁA�g�嗦�A�f�B�t���[�Y�J���[�A�X�y�L�����[�J���[�A�`��t���O�j
	///</summary>
	void Draw(const MODEL_ID& id, const Vector3& position, float alpha, Vector3 rotate, const Vector3& scale, const Vector4& diffusecolor, const Vector4& specularcolor, bool trans);
	///<summary>
	/// �R�c���f����`�悷��i���f��ID�A�}�g���b�N�X�j
	///</summary>
	void Draw(const MODEL_ID& id, const Matrix4& mat);

	///<summary>
	/// �R�c��ԂɂQ�c�摜��`�悷��i���f��ID�A���W�A�\���R�}�ԍ��A���̃T�C�Y�j
	///</summary>
	void Draw2D(const MODEL_ID& id, const Vector3& position, int frame, float size);
	///<summary>
	/// �R�c��ԂɂQ�c�摜��`�悷��i���f��ID�A���W�A�\���R�}�ԍ��A���̃T�C�Y�A���S���W�j
	///</summary>
	void Draw2D(const MODEL_ID& id, const Vector3& position, int frame, float size, const Vector2& origin);
	///<summary>
	/// �R�c��ԂɂQ�c�摜��`�悷��i���f��ID�A���W�A�\���R�}�ԍ��A���̃T�C�Y�A���S���W�A��]�ʁj
	///</summary>
	void Draw2D(const MODEL_ID& id, const Vector3& position, int frame, float size, const Vector2& origin, float angle);
	///<summary>
	/// �R�c��ԂɂQ�c�摜��`�悷��i���f��ID�A���W�A�\���R�}�ԍ��A���̃T�C�Y�A���S���W�A��]�ʁA���ߓx�j
	///</summary>
	void Draw2D(const MODEL_ID& id, const Vector3& position, int frame, float size, const Vector2& origin, float angle, float alpha);
	///<summary>
	/// �R�c��ԂɂQ�c�摜��`�悷��i���f��ID�A���W�A�\���R�}�ԍ��A���̃T�C�Y�A���S���W�A��]�ʁA���ߓx�A�`��t���O�j
	///</summary>
	void Draw2D(const MODEL_ID& id, const Vector3& position, int frame, float size, const Vector2& origin, float angle, float alpha, bool trans);
	///<summary>
	/// �R�c��ԂɂQ�c�摜��`�悷��i���f��ID�A���W�A�\���R�}�ԍ��A���̃T�C�Y�A���S���W�A��]�ʁA���ߓx�A�`��t���O�A���]�j
	///</summary>
	void Draw2D(const MODEL_ID& id, const Vector3& position, int frame, float size, const Vector2& origin, float angle, float alpha, bool trans, bool turn);
	///<summary>
	/// ���f���n���h�����󂯎��
	///</summary>
	int GetHandle(const MODEL_ID& id);
	///<summary>
	/// �R�c���f���̕������Z���[�h���Z�b�g����
	///</summary>
	void SetPhysics(int mode);

	bool CollisionLine(const MODEL_ID& id, const Vector3& start, const Vector3& end, Vector3* normal = nullptr, Vector3* position = nullptr);
	bool CollisionSphere(const MODEL_ID& id, const Vector3& center, float radius, Vector3* position = nullptr, Vector3* normal = nullptr);
	bool RefreshInfo(const MODEL_ID& id, const Vector3& p, const Vector3& s);
	/* �񓯊����̃��[�h�`�F�b�N */
	bool CheckASyncModel();
	bool CheckASyncBillboard();
	bool IsASyncLoad(const MODEL_ID& id);

	int GetCount();

	VECTOR GetMin(const MODEL_ID& id, int index  = 0);
	VECTOR GetMax(const MODEL_ID& id, int index = 0);

private:
	std::string Split(std::string filename);
	
	///<summary>
	/// �摜�ɃA���t�@�u�����h�������{��
	///</summary>
	void AlphaBlend(float alpha);

	///<summary>
	/// �摜�̃u�����h�������f�t�H���g�ɂ���
	///</summary>
	void DefaultBlend();

	class ModelHandle
	{
	public:
		ModelHandle(int cmp);
		~ModelHandle();
		ModelHandle(const ModelHandle&) = delete;
		ModelHandle& operator = (const ModelHandle&) = delete;
		ModelHandle(ModelHandle&&) = delete;
		ModelHandle& operator = (ModelHandle&&) = delete;

		/* �ǂݍ��� */
		void Load(const std::string& filename, bool async = false, bool collinfo = false, bool reference = false, std::function<void(int)> end = nullptr);
		/* �`�� */
		void Draw();
		/* �폜 */
		void Delete();
		/* �񓯊����ɐݒ肵�����̂�ݒ肷�� */
		void Enable();
		/* �n���h���擾 */
		int GetHangle()
		{
			return handle;
		}

		bool CheckASync();

		void End()
		{
			isInit = true;
		}

	private:
		const int param;
		int handle;
		bool isInit;
		bool isCol;
		bool isRef;
		std::function<void(int)> endcallback;
	};

	using HandlePtr = std::shared_ptr < ModelHandle > ;
	using HandlePair = std::pair < MODEL_ID, HandlePtr >;
	std::unordered_map<MODEL_ID, HandlePtr> m_models;
	
	std::unordered_map<MODEL_ID, std::vector<int>> m_sprites;
};