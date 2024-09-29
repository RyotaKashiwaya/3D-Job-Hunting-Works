#pragma once
#include "../CameraBase.h"


class Rifle;

class FPSCamera : public CameraBase
{
public:
	FPSCamera()							{}
	~FPSCamera()			override	{}

	void Init()				override;
	void Update()			override;
	void PostUpdate()		override;

	void SetWeapon(const std::shared_ptr<Rifle>& _ptr)
	{
		m_wpWeapon = _ptr;
	}

private:
	std::shared_ptr<KdRandomGenerator> m_RandomGen;

	std::weak_ptr<Rifle> m_wpWeapon;

	Math::Matrix			  m_shotLocalMat = Math::Matrix::Identity;
	Math::Vector3			  m_shotLocalPos = Math::Vector3::Zero;

	float ShotRecoil = {};
};