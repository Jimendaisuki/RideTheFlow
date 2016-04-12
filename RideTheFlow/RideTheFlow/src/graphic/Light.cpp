#include "Light.h"
#include "../math/Math.h"
#include <Dxlib.h>

// コンストラクタ（標準ライトを使用するか否か）
Light::Light()
: Light(false){}
Light::Light(bool value)
{
	SetLightEnable(value);
	m_lights.clear();
}

Light::~Light()
{
	DeleteLightHandleAll();
}

// 初期化処理
void Light::Initialize()
{
	for (auto& i : m_lights)
	{
		DeleteLight(i.first);
	}
}

// 通常ライトを使用するか否か
void Light::UseStandardLight(bool value)
{
	SetLightEnable(value);
}

///<summary>
/// ライティング計算処理を使用するか否か
///</summary>
void Light::UseLighting(bool value)
{
	SetUseLighting(value);
}

// ディレクショナルライトをセットする（ハンドル名、ベクトル）
void Light::SetDirectionalLight(const std::string& handlename, Vector3& vector)
{
	AlreadyGrow(handlename);
	m_lights[handlename] = CreateDirLightHandle(VGet(vector.x, vector.y, vector.z));
}

// ポイントライトをセットする（ハンドル名、座標、範囲、減衰値０、減衰値１、減衰値２）
void Light::SetPointLight(const std::string& handlename, Vector3& position, float range, float atten0, float atten1, float atten2)
{
	AlreadyGrow(handlename);
	m_lights[handlename] = CreatePointLightHandle(VGet(position.x, position.y, position.z), range, atten0, atten1, atten2);
}

// スポットライトをセットする（ハンドル名、座標、ベクトル、ライトコーンの外側の角度、ライトコーンの内側の角度、範囲、減衰値０、減衰値１、減衰値２）
void Light::SetSpotLight(const std::string& handlename, Vector3& position, Vector3& vector, float cone_outangle, float cone_inangle, float range, float atten0, float atten1, float atten2)
{
	AlreadyGrow(handlename);
	m_lights[handlename] = CreateSpotLightHandle(VGet(position.x, position.y, position.z), VGet(vector.x, vector.y, vector.z),
		Math::Radian(cone_outangle), Math::Radian(cone_inangle), range, atten0, atten1, atten2);
}

// セットしたライトを消去する
void Light::DeleteLight(const std::string& handlename)
{
	NoneGrow(handlename);
	DeleteLightHandle(m_lights[handlename]);
	m_lights.erase(handlename);
}

// ライトの向きを設定する
void Light::SetDirection(const std::string& handlename, Vector3& vector)
{
	NoneGrow(handlename);
	SetLightDirectionHandle(m_lights[handlename], VGet(vector.x, vector.y, vector.z));
}

// ライトの位置を設定する
void Light::SetPosition(const std::string& handlename, Vector3& position)
{
	NoneGrow(handlename);
	SetLightPositionHandle(m_lights[handlename], VGet(position.x, position.y, position.z));
}

// ライトのディフューズカラーを設定する
void Light::SetDiffuseColor(const std::string& handlename, Vector4& color)
{
	NoneGrow(handlename);
	SetLightDifColorHandle(m_lights[handlename], GetColorF(color.x, color.y, color.z, color.w));
}

// ライトのスペキュラーカラーを設定する
void Light::SetSpecularColor(const std::string& handlename, Vector4& color)
{
	NoneGrow(handlename);
	SetLightSpcColorHandle(m_lights[handlename], GetColorF(color.x, color.y, color.z, color.w));
}

// ライトのアンビエントカラーを設定する
void Light::SetAmbientColor(const std::string& handlename, Vector4& color)
{
	NoneGrow(handlename);
	SetLightAmbColorHandle(m_lights[handlename], GetColorF(color.x, color.y, color.z, color.w));
}

// ライトのディフューズカラーを受け取る
Vector4 Light::GetDiffuseColor(const std::string& handlename)
{
	COLOR_F lib_color = GetLightDifColorHandle(m_lights[handlename]);
	return Vector4(lib_color.r, lib_color.g, lib_color.b, lib_color.a);
}

// ライトのスペキュラーカラーを受け取る
Vector4 Light::GetSpecularColor(const std::string& handlename)
{
	COLOR_F lib_color = GetLightSpcColorHandle(m_lights[handlename]);
	return Vector4(lib_color.r, lib_color.g, lib_color.b, lib_color.a);
}

// ライトのアンビエントカラーを受け取る
Vector4 Light::GetAmbientColor(const std::string& handlename)
{
	COLOR_F lib_color = GetLightAmbColorHandle(m_lights[handlename]);
	return Vector4(lib_color.r, lib_color.g, lib_color.b, lib_color.a);
}

// セットしたライトを有効にするか無効にするか設定する
void Light::LightEnable(const std::string& handlename, bool value)
{
	NoneGrow(handlename);
	SetLightEnableHandle(m_lights[handlename], value);
}

// セットされているライトの数を取得する
int Light::IsLightNumber()
{
	return GetEnableLightHandleNum();
}

bool Light::IsEnable(const std::string& name) const
{
	auto it = m_lights.find(name);
	return it != m_lights.end() && GetLightEnableHandle(it->second) == TRUE;
}

// 既に指定のライトが存在していたら、スローする
void Light::AlreadyGrow(const std::string& handlename)
{
	if (m_lights.find(handlename) != m_lights.end())
	{
		throw std::string(handlename + "ライトをもうひとつ生成しようとしました");
	}
}

// 指定のライトが存在していなければ、スローする
void Light::NoneGrow(const std::string& handlename)
{
	if (m_lights.find(handlename) == m_lights.end())
	{
		throw std::string(handlename + "ライトは存在していません");
	}
}