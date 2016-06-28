#ifndef FLOATINGLSLAND2_H_
#define FLOATINGLSLAND2_H_
#include "../Actor.h"
#include "../../math/Vector3.h"
#include <memory>

class Froatinglsland2 : public Actor, public std::enable_shared_from_this<Froatinglsland2>
{
public:
	Froatinglsland2(IWorld& world, Vector3 position, Vector3 rotate, Vector3 scale,bool isGameFlag);
	~Froatinglsland2();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	float timer;
	bool isCol;

};


#endif