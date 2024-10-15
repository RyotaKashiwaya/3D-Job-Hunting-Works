#include "RifleCartridge.h"
void RifleCartridge::Update()
{

	if (ExpiredCnt > ExpiredTime)
	{
		m_isExpired = true;
		int Rnd = m_RandomGen->GetInt(0, 2);
		switch (Rnd)
		{
		case 0:
			KdAudioManager::Instance().Play("Asset/Sounds/GameObject/Bullet/Rifle/RifleCartridge1.wav")->SetVolume(0.3f);
			break;
		case 1:
			KdAudioManager::Instance().Play("Asset/Sounds/GameObject/Bullet/Rifle/RifleCartridge2.wav")->SetVolume(0.3f);
			break;
		case 2:
			KdAudioManager::Instance().Play("Asset/Sounds/GameObject/Bullet/Rifle/RifleCartridge3.wav")->SetVolume(0.3f);
			break;
		}

		m_isExpired = true;
	}
	else
	{
		ExpiredCnt++;
	}
	m_dir.Normalize();
	LocalPos += m_dir * m_speed;
	
	LocalPos.y -= m_gravity;
	m_gravity += m_gravityPow;
	m_trans = Math::Matrix::CreateTranslation(LocalPos);
	m_mWorld = m_rotCartridge * m_trans;
}

void RifleCartridge::DrawLit()
{
	if (!m_spModel) return ;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);

}

void RifleCartridge::Init()
{

	Math::Matrix _ejectionportLocalMat = Math::Matrix::CreateTranslation(LocalPos);
	m_mWorld = _ejectionportLocalMat;

	m_RandomGen = std::make_shared<KdRandomGenerator>();

	float _dirX = m_RandomGen->GetInt(1, 3);
	float _dirY = m_RandomGen->GetInt(1, 5);
	float _dirZ = m_RandomGen->GetInt(-10, 10) / 10;
	m_dir += {0, _dirY, _dirZ};
	m_dir.x *= _dirX;
	m_spModel = std::make_shared<KdModelWork>();
	m_spModel->SetModelData("Asset/Models/Object/Weapon/Rifle/RifleCartridge.gltf");
}

void RifleCartridge::Shot(Math::Vector3 _mozlePos, Math::Vector3 _shotDir)
{
	LocalPos = _mozlePos;
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

	//内積で算出した角度分、外積で算出したベクトル(回転軸)で回転する行列を作成
	//＝弾がレティクルの方向を向く


	m_rotCartridge = Math::Matrix::CreateFromAxisAngle(_rotAxis, _angle);
}
