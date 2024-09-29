#include "FPSCamera.h"
#include"../../../GameObject/Weapon/Rifle/Rifle.h"

void FPSCamera::Init()
{
	m_RandomGen = std::make_shared<KdRandomGenerator>();

	// 親クラスの初期化呼び出し
	CameraBase::Init();
}

void FPSCamera::Update()
{

	ShotRecoil = {};

	if (m_wpWeapon.lock()->GetIsFire() == true)
	{
		ShotRecoil = m_RandomGen->GetInt(0,30);
	}

	m_shotLocalPos = { 0,0,ShotRecoil / 1000 };
	m_shotLocalMat = Math::Matrix::CreateTranslation(m_shotLocalPos);
}

void FPSCamera::PostUpdate()
{
	// ターゲットの行列(有効な場合利用する)
	Math::Matrix								_targetMat	= Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject>	_spTarget	= m_wpTarget.lock();	
	if (_spTarget)
	{
		_targetMat = _spTarget->GetMatrix();
	}

	m_mWorld = m_shotLocalMat * _targetMat;

	CameraBase::Update();
}
