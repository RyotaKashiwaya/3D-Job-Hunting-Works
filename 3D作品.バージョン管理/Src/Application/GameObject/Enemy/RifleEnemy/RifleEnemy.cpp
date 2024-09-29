#include "RifleEnemy.h"
#include"../../../Scene/SceneManager.h"
#include"../../../GameObject/Enemy/EnemyManager.h"
#include"../../../GameObject/Character/Character.h"
#include"../../../main.h"
void RifleEnemy::Update()
{
	//Application::Instance().m_log.AddLog("DirX %d\n", m_moveDirForPop.x);

	if (!IsPopDirection)
	{
		if (m_pos.z > m_PopEndPosZ)
		{
			IsPopDirection = true;
		}
		else
		{
			if (!m_IsAvoidance)
			{
				if (m_pos.z > -400)
				{
					m_IsAvoidance = true;
				}
			}

			if (m_IsAvoidance)
			{
				if (m_pos.x > 0 && m_wpChara.lock()->GetPos().x + m_distance > m_pos.x || m_pos.x < 0 && m_wpChara.lock()->GetPos().x - m_distance < m_pos.x)
				{

					if (m_pos.x >= 0 && m_wpChara.lock()->GetPos().x + m_distance > m_pos.x)
					{
						m_speed = 1.7f;
						m_moveDirPowForPop += 0.008f;
					
					}
					if (m_pos.x <= 0 && m_wpChara.lock()->GetPos().x - m_distance < m_pos.x)
					{
						m_speed = 1.7f;
						m_moveDirPowForPop -= 0.008f;
					
					}

					m_RotDir = m_moveDirForPop;
					m_moveDirForPop.x += m_moveDirPowForPop;
					CarRotate();
				}
				else
				{
		
					m_moveDirPowForPop = 0;

					if (abs(m_moveDirForPop.x) > 0.1f)
					{
						if (m_moveDirForPop.x > 0)
						{
							m_moveDirForPop.x -= 0.05f;
						}

						if (m_moveDirForPop.x < 0)
						{
							m_moveDirForPop.x += 0.05f;
						}
						CarRotate();
					}
					else
					{
						m_speed = 4.5f;
						m_moveDirForPop.x = 0;
						m_mWorld = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(0));
					}
					
					
					
				}
			}

		}

		m_moveDirForPop.Normalize();
		m_pos += m_moveDirForPop * m_speed;
	}
	

}

void RifleEnemy::PostUpdate()
{
	m_tramsMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = m_rotMat * m_tramsMat;
}

void RifleEnemy::DrawLit()
{
	if (m_spCarModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spCarModel, m_mWorld);
	}
	if (m_spHumanModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spHumanModel, m_mWorld);
	}
}

void RifleEnemy::Init()
{
	m_RandomGen = std::make_shared<KdRandomGenerator>();

	m_PopEndPosZ = m_RandomGen->GetInt(100, 800);

	if (!m_spCarModel) 
	{
		m_spCarModel = std::make_shared<KdModelWork>();
		m_spCarModel->SetModelData("Asset/Models/Object/Enemy/EnemyCar.gltf");
	}

	if (!m_spHumanModel)
	{
		m_spHumanModel = std::make_shared<KdModelWork>();
		m_spHumanModel->SetModelData("Asset/Models/Object/Enemy/Enemy.gltf");
	}

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Enemy", m_spHumanModel, KdCollider::TypeDamage);
	m_pCollider->RegisterCollisionShape("Car", m_spCarModel, KdCollider::TypeGround);

	float _posX = (m_RandomGen->GetInt(0, 1) * 2 - 1) * m_RandomGen->GetInt(1, 20) * 10;

	m_pos.x = _posX;
	m_moveDirForPop = { 0,0,1 };
	m_speed = 4.5f;

	m_mWorld = Math::Matrix::CreateTranslation(m_pos);
}

void RifleEnemy::CarRotate()
{
	m_moveDirForPop.Normalize();

	//レティクルへのベクトルと弾への信仰ベクトルから弾の向き(回転行列)を作成

	//①　ベクトルA ・・・現在の進行ベクトル

	Math::Vector3 _vecA = m_mWorld.Backward();
	_vecA.Normalize();


	//②　ベクトルB ・・・照準への進行ベクトル
	Math::Vector3 _vecB = m_moveDirForPop;
	_vecB.Normalize();

	//①と②のベクトルの内積値から角度を算出
	float _dot = _vecA.Dot(_vecB);				//内積値を算出
	float _angle = acos(_dot);					//内積で取得したcos値から2つのベクトルの角度を算出

	//①と②の外積を利用して、回転するためのベクトル(回転軸)を作成
	Math::Vector3 _rotAxis = _vecA.Cross(_vecB);

	//内積で算出した角度分、外積で算出したベクトル(回転軸)で回転する行列を作成
	//＝弾がレティクルの方向を向く

	if (_vecA != _vecB)
	{
		m_rotMat = Math::Matrix::CreateFromAxisAngle(_rotAxis, _angle);
	}

}

void RifleEnemy::OnHit()
{
	m_isExpired = true;
}
