#include "GunUI.h"
#include"Src/Application/main.h"
#include"../../../GameObject/Weapon/WeaponBase.h"
void GunUI::Update()
{
	m_spGun = m_wpGun.lock();

	NowBullet = m_spGun->GetNowBullet();

	if (m_spGun->GetIsReload() == true)
	{
		ColorIntensity -= ColorIntensityNum;
		if (ColorIntensity > 1.1 || ColorIntensity < 0.4)
		{
			ColorIntensityNum *= -1;
		}
	}
	else
	{
		ColorIntensity = 1;
	}

	m_clipTexNum1 = NowBullet / 100;
	m_clipTexNum2 = (NowBullet / 10) % 10;
	m_clipTexNum3 = NowBullet % 10;

	/*Application::Instance().m_log.AddLog("nowBullet %d ", m_clipTexNum1);
	Application::Instance().m_log.AddLog("nowBullet %d ", m_clipTexNum2);
	Application::Instance().m_log.AddLog("nowBullet %d \n", m_clipTexNum3);
	Application::Instance().m_log.AddLog("maxBullet %d \n", MaxBullet);*/

	m_ScaleMat = Math::Matrix::CreateScale(m_Scale);
}

void GunUI::DrawSprite()
{

	m_BulletNunColor = { 1,1,1,ColorIntensity };

	if (m_spGun->GetIsReload() == true)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spReloadTex, -450, 300, nullptr, nullptr);
	}

	 m_rect1 = { 0 + (m_clipTexNum1 * 45),0,(long)m_spBulletNunTex->GetWidth() / 10,(long)m_spBulletNunTex->GetHeight() };
	 KdShaderManager::Instance().m_spriteShader.DrawTex(m_spBulletNunTex, -500, 240, m_rect1.width, m_rect1.height, &m_rect1, &m_BulletNunColor);

	 m_rect2 = { 0 + (m_clipTexNum2 * 45),0,(long)m_spBulletNunTex->GetWidth() / 10,(long)m_spBulletNunTex->GetHeight() };
	 KdShaderManager::Instance().m_spriteShader.DrawTex(m_spBulletNunTex, -450, 240, m_rect2.width, m_rect2.height, &m_rect2, &m_BulletNunColor);

	 m_rect3 = { 0 + (m_clipTexNum3 * 45),0,(long)m_spBulletNunTex->GetWidth() / 10,(long)m_spBulletNunTex->GetHeight() };
	 KdShaderManager::Instance().m_spriteShader.DrawTex(m_spBulletNunTex, -400, 240, m_rect3.width, m_rect3.height, &m_rect3, &m_BulletNunColor);

	 m_TopRect = { 0,0,(long)m_spMagazinTexTop->GetWidth() ,0 + (((long)m_spMagazinTexTop->GetHeight() /MaxBullet)* NowBullet)};
	 KdShaderManager::Instance().m_spriteShader.DrawTex(m_spMagazinTexTop, -570, 330, m_TopRect.width, m_TopRect.height, &m_TopRect, &m_TopColor,{(0.5f),{1.0f}});

	 m_UnderRect = { 0,0,(long)m_spMagazinTexUnder->GetWidth() ,(long)m_spMagazinTexUnder->GetHeight()};
	 KdShaderManager::Instance().m_spriteShader.DrawTex(m_spMagazinTexUnder, -570, 250, m_UnderRect.width, m_UnderRect.height, &m_UnderRect, &m_UnderColor);
}

void GunUI::Init()
{
	m_pos = { -500,-300 };
	MaxBullet = m_wpGun.lock()->GetMaxBullet();

	m_spBulletNunTex = std::make_shared<KdTexture>();
	m_spBulletNunTex->Load("Asset/Textures/Object/UI/GunUI/ClipTex.png");

	m_spReloadTex = std::make_shared<KdTexture>();
	m_spReloadTex->Load("Asset/Textures/Object/UI/GunUI/ReloadTex.png");

	m_spMagazinTexTop = std::make_shared<KdTexture>();
	m_spMagazinTexTop->Load("Asset/Textures/Object/UI/GunUI/MagTex.png");

	m_spMagazinTexUnder = std::make_shared<KdTexture>();
	m_spMagazinTexUnder->Load("Asset/Textures/Object/UI/GunUI/MagTex.png");

	m_Scale = { 1,1,0 };


	ColorIntensity = 1;
	ColorIntensityNum = 0.03f;
}
