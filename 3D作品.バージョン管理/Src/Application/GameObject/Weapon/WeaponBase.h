#pragma once

class EnemyManeger;

class WeaponBase : public KdGameObject
{
public:
	WeaponBase() {}
	virtual ~WeaponBase()override {}

	virtual void Update()override;

	void DrawLit();

	virtual void ShotBullet(bool rayFlg = false) = 0;

	void SetParent(const std::shared_ptr<KdGameObject>& parent)
	{
		m_wpParent = parent;
	}

	int GetNowBullet() { return m_nowBullet; }

	int GetMaxBullet() { return m_maxBullet; }

	bool GetShotFlg() { return m_shotFlg; }

	bool GetIsReload() { return IsReload; }


protected:



	std::shared_ptr<KdRandomGenerator> m_RandomGen;

	//モデル情報
	std::shared_ptr<KdModelWork> m_spModel = nullptr;

	//親(持ち主)の情報
	std::weak_ptr<KdGameObject> m_wpParent;

	//親から武器本体へのローカル行列(相対位置)
	Math::Matrix m_localMat;

	//親から銃口へのローカル行列(相対位置)
	Math::Matrix m_localMuzzleMat;

	Math::Matrix m_localpPortMat;

	//球発射フラグ
	bool m_shotFlg = false;

	//レイ弾フラグ
	bool m_rayBulletFlg = false;

	//レイフラグ
	bool m_rayFlg = false;

	int  m_maxBullet = {};

	int  m_nowBullet = {};

	bool IsFire = false;

	Math::Vector3 m_ReloadMove = Math::Vector3::Zero;
	Math::Matrix m_ReloadMoveMat = Math::Matrix::Identity;

	bool IsReload = false;
	bool IsReloadKey = false;

	int	 ReloadTime = {};
	int	 ReloadCnt = {};

	float ReloadMovePow = -0.005;
	float ReloadMove = ReloadMovePow;

};
