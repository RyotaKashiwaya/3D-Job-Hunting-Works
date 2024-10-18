#include "Explosion.h"

void Explotion::Update()
{
	if (animetionNum == animetionEnd)
	{
		std::shared_ptr<KdGameObject> _ptr = m_wpPearent.lock();
		if (_ptr)
		{
			_ptr->OnHit();
		}

		m_isExpired = true;

	}
	else
	{
		animetionNum++;
	}

	m_spPoly->SetUVRect(animetionNum);
}

void Explotion::DrawUnLit()
{
	if (m_spPoly)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
	}
}

void Explotion::DrawBright()
{
	if (m_spPoly)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
	}
}

void Explotion::Init()
{
	if (!m_spPoly)
	{
		m_spPoly = std::make_shared<KdSquarePolygon>();
		m_spPoly->SetMaterial("Asset/Textures/Object/Effect/Explosion/explosion.png");

		m_spPoly->SetSplit(5, 10);
	}

	m_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_scaleMat = Math::Matrix::CreateScale(m_Scele);
	m_mWorld = m_scaleMat * m_rotMat * m_transMat;
}

void Explotion::Rotate(Math::Vector3 _mozlePos, Math::Vector3 _shotDir)
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

	m_rotMat = Math::Matrix::CreateFromAxisAngle(_rotAxis, _angle);
}
