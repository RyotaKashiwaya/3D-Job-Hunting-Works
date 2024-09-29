#include "LMG.h"
#include"Src/Application/Scene/SceneManager.h"
#include"../../../GameObject/Bullet/LMG/LMGBullet.h"
void LMG::Update()
{
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
	m_pDebugWire->AddDebugSphere(_mzzlePos, 0.05f, kBlueColor);

	if (m_nowBullet > 0)
	{

		//球発射
		if (m_shotFlg)
		{
			//レイ判定用バラメーター
			KdCollider::RayInfo _rayinfo;

			_rayinfo.m_pos = _spParent->GetPos();
			_rayinfo.m_dir = _parentMat.Backward();
			_rayinfo.m_range = 1000.0f;
			_rayinfo.m_type = KdCollider::TypeDamage;

			std::list < KdCollider::CollisionResult> _resultList;

			for (auto& obj : SceneManager::Instance().GetObjList())
			{
				obj->Intersects(_rayinfo, &_resultList);
			}

			//衝突情報リストから一番遠いオブジェクトを検出
			bool _isHit = false;
			float maxOverlap = 0.0f;
			Math::Vector3 _hitPos = Math::Vector3::Zero;

			//レイを飛ばす場合

			for (auto& _ray : _resultList)
			{
				if (maxOverlap < _ray.m_overlapDistance)
				{
					maxOverlap = _ray.m_overlapDistance;
					_hitPos = _ray.m_hitPos;
					_isHit = true;
				}
			}
			//レイの着弾点を利用して弾を飛ばすベクトルを算出
			Math::Vector3 ShotDir = _hitPos - _mzzlePos;

			m_nowBullet--;

			std::shared_ptr<LMGBullet> _bullet = std::make_shared<LMGBullet>();
			_bullet->Init();
			_bullet->Shot(_mzzlePos, ShotDir);
			SceneManager::Instance().AddObject(_bullet);
			m_shotFlg = false;
		}
	}
	else
	{
		IsReload = true;
	}

	if (!IsReloadKey)
	{
		if (GetAsyncKeyState('R') & 0x8000)
		{
			IsReloadKey = true;
			IsReload = true;
		}
	}
	else
	{
		IsReloadKey = false;
	}

	Reload();


	//基底クラスの更新処理(ワールド行列作成)
	WeaponBase::Update();
}

void LMG::Init()
{
	m_maxBullet = 200;
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

	//親から銃口へのローカル行列(相対位置)
	//親から武器本体への相対位置を混ぜて「親から銃口へのローカル行列」
	m_localMuzzleMat = Math::Matrix::CreateTranslation(0.0f, 0.16f, 1.5f);
	m_localMuzzleMat *= m_localMat;

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void LMG::ShotBullet(const bool rayflg)
{
	//弾フラグON
	m_shotFlg = true;
	//弾 = 弾とするか?
	m_rayFlg = rayflg;
}

void LMG::Reload()
{
	if (!IsReload) { return; }

	if (ReloadCnt == 0)
	{
		m_nowBullet = m_maxBullet;
		ReloadCnt = ReloadTime;
		IsReload = false;
		m_shotFlg = false;
	}
	else
	{
		ReloadCnt--;
	}
}
