#pragma once
#include "../math/Vector2.h"
#include "../math/Vector3.h"

class EnemyHP
{
public:
	explicit EnemyHP();
	void Initialize(const float& hp, const Vector3& position, const bool draw = true);
	void Update(const float& nowHp, const Vector3& position);
	void Draw() const;
private:
	bool	isDraw_;
	float	maxHP_;
	float	nowHP_;
	float	prevHP_;
	float	alpha_;
	Vector3	position_;
};