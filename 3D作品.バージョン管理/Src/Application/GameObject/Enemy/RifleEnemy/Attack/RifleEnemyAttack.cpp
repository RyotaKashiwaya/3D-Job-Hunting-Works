#include "RifleEnemyAttack.h"
#include"../../../../main.h"
void RifleEnemyAttack::Update()
{
	Application::Instance().m_log.AddLog("m_pos = {%f,%f,%f} \n", m_pos.x, m_pos.y, m_pos.z);

	m_Frame++;

	if ((m_wpTarget.lock()->GetPos() - m_pos).Length() < HitDistance)
	{
		OnHit();
	}

	if (m_Frame == 60)
	{
		m_ExpiredCnt--;
		m_Frame = 0;
	}

	if (m_ExpiredCnt == 0)
	{
		m_isExpired = true;
	}

	m_dir.Normalize();
	m_pos += m_dir * m_speed;
}

void RifleEnemyAttack::PostUpdate()
{
	m_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_ScaleMat = Math::Matrix::CreateScale(10);
	m_mWorld = m_ScaleMat * m_rotMat * m_transMat;
}

void RifleEnemyAttack::DrawLit()
{
	if (m_spBullet)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spBullet,m_mWorld);
	}
}

void RifleEnemyAttack::Init()
{
	

	if (!m_spBullet)
	{
		m_spBullet = std::make_shared<KdModelWork>();
		m_spBullet->SetModelData("Asset/Models/Object/Enemy/RifleEnemy/Bullet.gltf");
	}

	m_speed = 10.0f;
}

void RifleEnemyAttack::Shot(Math::Vector3 _pos, Math::Vector3 _targetpos)
{
	m_RandomGen = std::make_shared<KdRandomGenerator>();

	m_pos = _pos + m_Localpos;
	m_dir = _targetpos - m_pos;

	
	Math::Matrix RandamRot = Math::Matrix::Identity;

	float x = DirectX::XMConvertToRadians(m_RandomGen->GetFloat(-5.0f, 5.0f));
	float y = DirectX::XMConvertToRadians(m_RandomGen->GetFloat(-5.0f, 5.0f));

	RandamRot = Math::Matrix::CreateFromYawPitchRoll(y, x, 0);
	m_dir = Math::Vector3::TransformNormal(m_dir, RandamRot);

	m_dir.Normalize();

	//レティクルへのベクトルと弾への信仰ベクトルから弾の向き(回転行列)を作成

	//①　ベクトルA ・・・弾の現在の進行ベクトル
	Math::Vector3 _vecA = m_mWorld.Backward();
	_vecA.Normalize();

	//②　ベクトルB ・・・照準への進行ベクトル
	Math::Vector3 _vecB = m_dir;
	_vecB.Normalize();

	//①と②のベクトルの内積値から角度を算出
	float _dot = _vecA.Dot(_vecB);				//内積値を算出
	float _angle = acos(_dot);					//内積で取得したcos値から2つのベクトルの角度を算出

	//①と②の外積を利用して、回転するためのベクトル(回転軸)を作成
	Math::Vector3 _rotAxis = _vecA.Cross(_vecB);

	//内積で算出した角度分、外積で算出したベクトル(回転軸)で回転する行列を作成
	//＝弾がレティクルの方向を向く


	m_rotMat = Math::Matrix::CreateFromAxisAngle(_rotAxis, _angle);
}

void RifleEnemyAttack::OnHit()
{
	m_isExpired = true;
}
