#pragma once

class GameUI;

class WeaponBase;

class GunUI :public KdGameObject
{
public:

	GunUI(){}
	~GunUI() {}

	void Update()override;

	void DrawSprite()override;

	void Init() override;

	void SetGun(const std::shared_ptr<WeaponBase>& _gun)
	{
		m_wpGun = _gun;
	}

	void SetGameUI(const std::shared_ptr<GameUI>& _ui)
	{
		m_wpUI = _ui;
	}

private:
	std::weak_ptr<WeaponBase>	m_wpGun;
	std::weak_ptr<GameUI>	m_wpUI;


	std::shared_ptr<WeaponBase> m_spGun;
	std::shared_ptr<KdTexture> m_spBulletNunTex;
	std::shared_ptr<KdTexture> m_spReloadText;
	
	int						   m_clipTexNum1 = 0;
	int						   m_clipTexNum2 = 0;
	int						   m_clipTexNum3 = 0;

	Math::Vector2			   m_UIpos = Math::Vector2::Zero;
	Math::Vector3			   m_Scale = Math::Vector3::Zero;
	Math::Matrix			   m_ScaleMat = Math::Matrix::Identity;

	Math::Rectangle				m_rect1;
	Math::Rectangle				m_rect2;
	Math::Rectangle				m_rect3;

	Math::Color		m_BulletNunColor = {};
	float			ColorIntensity = {};
	float			ColorIntensityNum = {};

	int						   OldBullet = 0;
	int						   NowBullet = 0;
	int						   MaxBullet = 0;

	bool					   nowShooting = false;

	std::shared_ptr<KdTexture> m_spMagazinTexTop;
	std::shared_ptr<KdTexture> m_spMagazinTexUnder;

	Math::Rectangle				m_TopRect;
	Math::Rectangle				m_UnderRect;

	Math::Color				   m_TopColor = { 1,1,1,1 };
	Math::Color				   m_UnderColor = { 1,1,1,0.5f };
	Math::Color				   m_ReloadTextColor = { 1,1,1,1 };
};