#include "Rifle.h"

#include"Src/Application/Scene/SceneManager.h"
#include"Src/Application/GameObject/Bullet/Rifle/RifleBullet.h"
#include"../../../GameObject/Effect/ShotFire/ShotFire.h"
#include"../../../GameObject/Bullet/Rifle/RifleCartridge.h"

void Rifle::Update()
{


	IsFire = false;

	//親(プレイヤー)の行列を取得
	Math::Matrix _parentMat = Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject> _spParent = m_wpParent.lock();
	if (_spParent)
	{
		//親の行列を取得
		_parentMat = _spParent->GetMatrix();
	}

	//銃口位置をデバック表示
	Math::Vector3 _mzzlePos = (m_localMuzzleMat * _parentMat).Translation();
	//m_pDebugWire->AddDebugSphere(_mzzlePos, 0.05f, kBlueColor);
	Math::Vector3 _portPos = ( m_localpPortMat * _parentMat).Translation();

	if (m_nowBullet > 0)
	{
		if (!IsReload)
		{
			//球発射
			if (m_shotFlg)
			{

				Math::Vector3 ShotDir = m_mWorld.Backward();
				Math::Matrix RandamRot;

				float x = DirectX::XMConvertToRadians(m_RandomGen->GetFloat(-0.5f, 0.5f));
				float y = DirectX::XMConvertToRadians(m_RandomGen->GetFloat(-0.5f, 0.5f));

				RandamRot = Math::Matrix::CreateFromYawPitchRoll({y, x, 0});

				ShotDir = Math::Vector3::TransformNormal(ShotDir, RandamRot);

				m_nowBullet--;

				std::shared_ptr<RifleBullet> _bullet = std::make_shared<RifleBullet>();
				_bullet->Init();
				_bullet->Shot(_mzzlePos, ShotDir);

				KdAudioManager::Instance().Play("Asset/Sounds/GameObject/Weapon/Rifle/Shot.wav")->SetVolume(0.05f);

				IsFire = true;

				std::shared_ptr<ShotFire> _fireEffect = std::make_shared<ShotFire>();
				_fireEffect->SetPos(_mzzlePos);
				_fireEffect->SetScale();
				_fireEffect->SetRotY();
				_fireEffect->Shot(_mzzlePos, ShotDir);
				_fireEffect->Init();

				std::shared_ptr<RifleCartridge> _rifleCartridge = std::make_shared<RifleCartridge>();
				_rifleCartridge->SetPos(GetPos());
				_rifleCartridge->SetDir(m_mWorld.Right());
				_rifleCartridge->Shot(_portPos, ShotDir);
				_rifleCartridge->Init();

				SceneManager::Instance().AddObject(_bullet);
				SceneManager::Instance().AddObject(_fireEffect);
				SceneManager::Instance().AddObject(_rifleCartridge);

				bulletList.push_back(_bullet);

				m_shotFlg = false;
			}
		}
	}
	else if(!IsReload)
	{
		KdAudioManager::Instance().Play("Asset/Sounds/GameObject/Weapon/Rifle/Reload.wav")->SetVolume(0.2f);
		IsReload = true;
		ReloadMove = ReloadMovePow;
	}

	if (!IsReloadKey)
	{
		if (m_nowBullet != m_maxBullet)
		{
			if (!IsReload)
			{
				if (GetAsyncKeyState('R') & 0x8000)
				{
					KdAudioManager::Instance().Play("Asset/Sounds/GameObject/Weapon/Rifle/Reload.wav")->SetVolume(0.2f);
					IsReloadKey = true;
					IsReload = true;
					ReloadMove = ReloadMovePow;
				}
			}
		}
	}


	Reload();
	

	//基底クラスの更新処理(ワールド行列作成)
	WeaponBase::Update();

}

void Rifle::PostUpdate()
{
	std::vector<std::shared_ptr<RifleBullet>>::iterator it = bulletList.begin();

	for (auto& bullet : bulletList)
	{
		if (bullet->IsExpired() == true)
		{
			bulletList.erase(it);
			break;
		}
		else
		{
			it++;
		}
	}
}

void Rifle::Init()
{
	m_RandomGen = std::make_shared<KdRandomGenerator>();

	ReloadTime = 100;
	m_maxBullet = 30;
	m_nowBullet = m_maxBullet;
	ReloadCnt = ReloadTime;

	//親(プレイヤー)の行列を取得
	Math::Matrix _parentMat = Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject> _spParent = m_wpParent.lock();
	if (_spParent)
	{
		//親の行列を取得
		_parentMat = _spParent->GetMatrix();
	}

	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Models/Object/Weapon/Rifle/Rifle.gltf");
	}

	//親から武器本体へのローカル行列(相対位置)
	m_localMat = Math::Matrix::CreateTranslation(0.35f, -0.3f, 0.15f);

	if (m_spModel)
	{
		//blenderで作成したNULLポイントノードを探して取得
		const	KdModelWork::Node* _pMuzzleNode = m_spModel->FindNode("MuzzlePoint");

		//指定ノードが取得出来たら
		if (_pMuzzleNode)
		{
			m_localMuzzleMat = _pMuzzleNode->m_worldTransform * m_localMat;
		}

		//blenderで作成したNULLポイントノードを探して取得
		const	KdModelWork::Node* _pPortNode = m_spModel->FindNode("CartridgePoint");

		//指定ノードが取得出来たら
		if (_pPortNode)
		{
			m_localpPortMat = _pPortNode->m_worldTransform * m_localMat;
		}
	}

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Rifle::ShotBullet(const bool rayflg)
{
	//弾フラグON
	m_shotFlg = true;
	//弾 = 弾とするか?
	m_rayFlg = rayflg;
}

void Rifle::Reload()
{
	if (!IsReload) { return; }


	if (ReloadCnt == 0)
	{
		m_ReloadMove = {};
		m_nowBullet = m_maxBullet;
		ReloadCnt = ReloadTime;
		IsReload = false;
		m_shotFlg = false;
		IsReloadKey = false;
	}
	else
	{
		ReloadCnt--;
	}

	if (ReloadCnt == (ReloadTime / 2))
	{
		ReloadMove *= -1;
	}

	m_ReloadMove.z += ReloadMove;

	m_ReloadMoveMat = Math::Matrix::CreateTranslation(m_ReloadMove);
}

