#include "RifleEnemy.h"
#include"../../../Scene/SceneManager.h"
#include"../../../GameObject/Enemy/EnemyManager.h"
#include"../../../GameObject/Character/Character.h"
#include"../../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include"../../../GameObject/Effect/ShotFire/ShotFire.h"
#include"../../../GameObject/Effect/Explosion/Explosion.h"
#include"../../../main.h"
void RifleEnemy::Update()
{
	std::shared_ptr<Character> chara = m_wpChara.lock();

	if (IsDead)
	{
		if (m_wpExp.lock()->IsEnd()==true)
		{
			m_isExpired = true;
		}
	}
	else if (!IsPopDirection)
	{
		if (m_pos.z > m_PopEndPosZ)
		{
			IsPopDirection = true;
			m_IsAttack = true;
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
				if (m_pos.x > 0 && chara->GetPos().x + m_distance > m_pos.x || m_pos.x < 0 && chara->GetPos().x - m_distance < m_pos.x)
				{

					if (m_pos.x >= 0 && chara->GetPos().x < m_pos.x)
					{
						m_speed = 1.7f;
						m_moveDirPowForPop += 0.008f;

					}
					if (m_pos.x <= 0 && chara->GetPos().x > m_pos.x)
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
						bool _flg = false;
						for (auto& enemy : EnemyManeger::Instance().GetEnemyList())
						{
							if ((GetPos() - enemy->GetPos()).Length() < 80)
							{
								_flg = true;
								break;
							}
						}

						if (_flg)
						{
							m_moveDirForPop.x += 0.05;
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

		}

		m_moveDirForPop.Normalize();
		m_pos += m_moveDirForPop * m_speed;
	}

	m_WeaponMazzlePos = (m_WeaponMazzleMat * m_weaponMat).Translation();

	Math::Vector3	_dir = chara->GetPos() - m_WeaponMazzlePos;
	_dir.y = 0;
	_dir.Normalize();

	//m_pDebugWire->AddDebugSphere(m_WeaponMazzlePos, 3, kGreenColor);
	//m_pDebugWire->AddDebugLine(m_WeaponMazzlePos, _dir, 500, kBlueColor);

	if (m_IsAttack)
	{
		Application::Instance().m_log.AddLog("Cnt = %d \n", AttackCnt);
		if (AttackCnt > AttackCntNum)
		{
			AttackCntNum = m_RandomGen->GetInt(3,20);
			AttackCnt = 0;
			std::shared_ptr<ShotFire> _effect = std::make_shared<ShotFire>();
			_effect->SetPos(m_WeaponMazzlePos);
			_effect->SetScale(0.1);
			_effect->SetRotY(180);
			_effect->Shot(m_WeaponMazzlePos, -_dir);
			_effect->Init();
			SceneManager::Instance().AddObject(_effect);

			KdAudioManager::Instance().Play("Asset/Sounds/GameObject/Weapon/Rifle/Shot.wav")->SetVolume(0.05f);

			if (m_RandomGen->GetInt(0, 500) > 450)
			{
				m_wpChara.lock()->OnHit();
			}
		}
		else
		{
			AttackCnt++;
		}

	}
}

void RifleEnemy::PostUpdate()
{
	m_tramsMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = m_rotMat * m_tramsMat;

	WeaponRotate();
	

	m_weaponMat = m_weapomScale * m_weapomRot * m_weapomLocal * m_mWorld;
}

void RifleEnemy::DrawLit()
{
	if (!IsDead)
	{
		if (m_spCarModel)
		{
			KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spCarModel, m_mWorld);
		}
		if (m_spHumanModel)
		{
			KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spHumanModel, m_mWorld);
		}
		if (m_spWeaponModel)
		{
			KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spWeaponModel, m_weaponMat);
		}
	}
}

void RifleEnemy::Init()
{

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	m_RandomGen = std::make_shared<KdRandomGenerator>();

	m_PopEndPosZ = m_RandomGen->GetInt(-300, 800);

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

	if (!m_spWeaponModel)
	{
		m_spWeaponModel = std::make_shared<KdModelWork>();
		m_spWeaponModel->SetModelData("Asset/Models/Object/Enemy/RifleEnemy/Rifle/Rifle.gltf");
		m_weapomScale = Math::Matrix::CreateScale(4);
	}

	m_weapomLocal = Math::Matrix::CreateTranslation({ 4,20,0 });

	const	KdModelWork::Node* _pMuzzleNode = m_spWeaponModel->FindNode("MuzzlePoint");

	if (_pMuzzleNode)
	{
		m_WeaponMazzleMat = _pMuzzleNode->m_worldTransform ;
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

	if ( m_life == 0 && !IsDead)
	{
		if (m_life > 0)
		{
			m_life = 0;
		}

		IsDead = true;

		std::shared_ptr<Explotion> _exp = std::make_shared<Explotion>();
		Math::Vector3 _dir = m_wpChara.lock()->GetPos() - m_pos;

		m_wpExp = _exp;

		_exp->SetRotY(180);
		_exp->Rotate(m_pos, _dir);
		_exp->SetScale(200);
		_exp->Init();
		SceneManager::Instance().AddObject(_exp);

		KdAudioManager::Instance().Play("Asset/Sounds/GameObject/Effect/Explosion/Explosion.wav")->SetVolume(0.1f);

	}
	else
	{
		m_life--;
	}
}

void RifleEnemy::WeaponRotate()
{

	std::shared_ptr<Character> _spChara = m_wpChara.lock();
	
	Math::Vector3	_dir = _spChara->GetPos() - m_pos;

	_dir.y = 0;

	_dir.Normalize();


	//レティクルへのベクトルと弾への信仰ベクトルから弾の向き(回転行列)を作成

	//①　ベクトルA ・・・現在の進行ベクトル

	Math::Vector3 _vecA = m_mWorld.Backward();
	_vecA.Normalize();


	//②　ベクトルB ・・・照準への進行ベクトル
	Math::Vector3 _vecB = _dir;
	_vecB.Normalize();

	//m_pDebugWire->AddDebugLine(m_pos, _dir, 50, kRedColor);

	//①と②のベクトルの内積値から角度を算出
	float _dot = _vecA.Dot(_vecB);				//内積値を算出
	float _angle = acos(_dot);					//内積で取得したcos値から2つのベクトルの角度を算出

	//①と②の外積を利用して、回転するためのベクトル(回転軸)を作成
	Math::Vector3 _rotAxis = _vecA.Cross(_vecB);

	//内積で算出した角度分、外積で算出したベクトル(回転軸)で回転する行列を作成
	//＝弾がレティクルの方向を向く

	if (_vecA != _vecB)
	{
		m_weapomRot = Math::Matrix::CreateFromAxisAngle(_rotAxis, _angle);
	}

}
