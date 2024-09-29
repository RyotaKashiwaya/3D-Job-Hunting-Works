#include "ShotFire.h"
#include "../../../GameObject/Weapon/WeaponBase.h"

void ShotFire::Update()
{
	if (m_spAnimator->IsAnimationEnd())
	{
		m_isExpired = true;
	}
	
	m_spAnimator->AdvanceTime(m_spModel->WorkNodes());
	m_spModel->CalcNodeMatrices();

	m_mWorld = m_scaleMat *m_rotMat * m_rotBulletMat  * m_tramsMat;
}


void ShotFire::DrawUnLit()
{
	if (!m_spModel) return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void ShotFire::DrawBright()
{
	if (!m_spModel) return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void ShotFire::Init()
{
	m_RandomGen = std::make_shared<KdRandomGenerator>();

	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Models/Object/Effect/MuzzleFlash/scene.gltf");

		//書記のアニメーションをセットする
		m_spAnimator = std::make_shared<KdAnimator>();
		m_spAnimator->SetAnimation(m_spModel->GetData()->GetAnimation("scene"));
	}

	m_tramsMat = Math::Matrix::CreateTranslation(m_pos);
	m_scaleMat = Math::Matrix::CreateScale(m_Scele);
	int _rot = m_RandomGen->GetInt(0, 360);
	m_rotMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(_rot));

	m_mWorld = m_scaleMat * m_rotBulletMat * m_tramsMat;

}

void ShotFire::Shot(Math::Vector3 _mozlePos, Math::Vector3 _shotDir)
{
	m_pos = _mozlePos;
	m_moveDir = _shotDir;
	m_moveDir.Normalize();

	//レティクルへのベクトルと弾への信仰ベクトルから弾の向き(回転行列)を作成

	//①　ベクトルA ・・・弾の現在の進行ベクトル
	Math::Vector3 _vecA = m_mWorld.Backward();
	_vecA.Normalize();

	//②　ベクトルB ・・・照準への進行ベクトル
	Math::Vector3 _vecB = m_moveDir;
	_vecB.Normalize();

	//①と②のベクトルの内積値から角度を算出
	float _dot = _vecA.Dot(_vecB);				//内積値を算出
	float _angle = acos(_dot);					//内積で取得したcos値から2つのベクトルの角度を算出

	//①と②の外積を利用して、回転するためのベクトル(回転軸)を作成
	Math::Vector3 _rotAxis = _vecA.Cross(_vecB);

	m_rotBulletMat = Math::Matrix::CreateFromAxisAngle(_rotAxis, _angle);
}
