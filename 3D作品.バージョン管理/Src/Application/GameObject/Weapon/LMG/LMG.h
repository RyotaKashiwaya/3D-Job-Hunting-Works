#pragma once 
#include"../WeaponBase.h"

class LMG :public WeaponBase
{
public:
	LMG() {};
	~LMG()override {};

	void Update()override;

	void Init()override;

	void ShotBullet(const bool rayflg = false)override;

	void Reload();
private:

	Math::Vector3		m_scale = {};


	bool IsReload = false;
	bool IsReloadKey = false;;

	int	 ReloadTime = 180;
	int	 ReloadCnt = 0;

};