#pragma once 
#include"../WeaponBase.h"

class RifleBullet;

class Rifle :public WeaponBase
{
public:
	Rifle() {};
	~Rifle()override {};

	void Update()override;

	void PostUpdate()override;

	void Init()override;

	void ShotBullet(const bool rayflg = false)override;

	void Reload();

	bool GetIsFire(){return IsFire;}

	std::vector<std::shared_ptr<RifleBullet>>GetBulletList() { return bulletList; }

private:

	Math::Vector3		m_scale = {};

	std::vector<std::shared_ptr<RifleBullet>> bulletList;
};