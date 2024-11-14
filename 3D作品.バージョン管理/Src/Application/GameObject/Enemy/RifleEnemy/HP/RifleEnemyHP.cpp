#include "RifleEnemyHP.h"
#include"../../RifleEnemy/RifleEnemy.h"
#include"../../../../GameObject/Character/Character.h";
#include"../../../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include"../../../../main.h";
void RifleEnemyHP::Update()
{
	Application::Instance().m_log.AddLog("oldlif =  %d \n", oldLife);


	std::shared_ptr<RifleEnemy> m_spEnemy = m_wpPearent.lock();

	if (!m_spEnemy)
	{
		m_isExpired = true;
		return;
	}

	if (m_spEnemy->GetLife() != oldLife)
	{
		IsHit = true;
	}

	oldLife = m_spEnemy->GetLife();

	if (IsHit)
	{
		if(HpDrawCnt < HpDrawCntNum)
		{
			HpDrawCnt++;
		}
		else
		{
			IsHit = false;
			HpDrawCnt = 0;
		}
	}

	Rotate();

	Math::Vector3 m_pos = m_spEnemy->GetPos() + m_LocalPos;
	Math::Matrix m_TransMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = m_ScaleMat *   m_RotMat * m_TransMat;
}

void RifleEnemyHP::DrawLit()
{

	//if (IsHit)
	//{
	//	if (m_gageUnderPoly)
	//	{
	//		m_rect = { 0,0, (long)m_polyTex->GetWidth(),(long)m_polyTex->GetHeight()};
	//		m_gageUnderPoly->SetUVRect(m_rect);
	//		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_gageUnderPoly, m_mWorld);
	//	}

	//	if (m_gagePoly)
	//	{
	//		m_rect = { 0,0,(long)m_polyTex->GetWidth() - (((long)m_polyTex->GetWidth() / maxlife) * oldLife), (long)m_polyTex->GetHeight() };
	//		m_gagePoly->SetUVRect(m_rect);
	//		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_gagePoly, m_mWorld);
	//	}
	//	if (m_flamePoly)
	//	{
	//		m_rect = { 0,0, (long)m_polyTex->GetWidth(),(long)m_polyTex->GetHeight()};
	//		m_flamePoly->SetUVRect(m_rect);
	//		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_flamePoly, m_mWorld);
	//	}
	//}

}

void RifleEnemyHP::DrawSprite()
{


	Math::Vector3 _result = Math::Vector3::Zero;
	std::shared_ptr<KdCamera> _cam = m_wpCam.lock();

	if (_cam)
	{
		_cam->ConvertWorldToScreenDetail(GetPos(), _result);
		_result.y += 100;
	}

	if (m_gageUnderTex)
	{
		KdShaderManager::Instance().m_spriteShader.SetMatrix(Math::Matrix::CreateScale(0.5));
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_gageUnderTex, 0, 100);
		KdShaderManager::Instance().m_spriteShader.SetMatrix(Math::Matrix::CreateScale(1));
	}

	if (m_gageTex)
	{
		m_rect = { 0 + ((long)m_gageTex->GetWidth() / maxlife) * (maxlife - oldLife) ,0,(long)m_gageTex->GetWidth()  ,(long)m_gageTex->GetHeight() };
		KdShaderManager::Instance().m_spriteShader.SetMatrix(Math::Matrix::CreateScale(0.5));
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_gageTex, 0,100,m_gageTex->GetWidth(),m_gageTex->GetHeight(), & m_rect);
		KdShaderManager::Instance().m_spriteShader.SetMatrix(Math::Matrix::CreateScale(1));
	}

	if (!m_flameTex)
	{
		KdShaderManager::Instance().m_spriteShader.SetMatrix(Math::Matrix::CreateScale(0.5));
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_flameTex, 0, 100);
		KdShaderManager::Instance().m_spriteShader.SetMatrix(Math::Matrix::CreateScale(1));
	}


	Application::Instance().m_log.AddLog("x = %d ,y = %d,w = %d,h = %d \n", m_rect.x, m_rect.y, m_rect.width, m_rect.height);
}


void RifleEnemyHP::Init()
{

	oldLife = m_wpPearent.lock()->GetLife();

	//if (!m_gageUnderPoly)
	//{
	//	m_gageUnderPoly = std::make_shared<KdSquarePolygon>();
	//	m_gageUnderPoly->SetMaterial("Asset/Textures/Object/UI/EnemyUI/EnemyHP/EnemyHPGageUnder.png");
	//	m_gageUnderPoly->SetScale(m_scale);
	//}

	//if (!m_gagePoly)
	//{
	//	m_gagePoly = std::make_shared<KdSquarePolygon>();
	//	m_gagePoly->SetMaterial("Asset/Textures/Object/UI/EnemyUI/EnemyHP/EnemyHPGage1.png");
	//	m_gagePoly->SetScale(m_scale);
	//}

	//if (!m_polyTex)
	//{
	//	m_polyTex = std::make_shared<KdTexture>();
	//	m_polyTex->Load("Asset/Textures/Object/UI/EnemyUI/EnemyHP/EnemyHPGage1.png");
	//	
	//}

	//if (!m_flamePoly)
	//{
	//	m_flamePoly = std::make_shared<KdSquarePolygon>();
	//	m_flamePoly->SetMaterial("Asset/Textures/Object/UI/EnemyUI/EnemyHP/EnemyHPFlame.png");
	//	m_flamePoly->SetScale(m_scale);
	//}
	if (!m_flameTex)
	{
		m_flameTex = std::make_shared<KdTexture>();
		m_flameTex->Load("Asset/Textures/Object/UI/EnemyUI/EnemyHP/EnemyHPFlame.png");
	}
		
	if (!m_gageTex)
	{
		m_gageTex = std::make_shared<KdTexture>();
		m_gageTex->Load("Asset/Textures/Object/UI/EnemyUI/EnemyHP/EnemyHPGage.png");
	}

	if (!m_gageUnderTex)
	{
		m_gageUnderTex = std::make_shared<KdTexture>();
		m_gageUnderTex->Load("Asset/Textures/Object/UI/EnemyUI/EnemyHP/EnemyHPGageUnder.png");
	}


	maxlife = m_wpPearent.lock()->GetMaxLife();


	m_ScaleMat = Math::Matrix::CreateScale(1);

	m_LocalPos = { 0,50,10 };
}

void RifleEnemyHP::Rotate()
{
	std::shared_ptr<Character> m_spChara = m_wpChara.lock();
	if (!m_spChara)return;
	

	Math::Vector3	_dir = m_spChara->GetPos() - GetPos();

	_dir.y = 0;

	_dir.Normalize();

	//レティクルへのベクトルと弾への信仰ベクトルから弾の向き(回転行列)を作成

	//①　ベクトルA ・・・現在の進行ベクトル

	Math::Vector3 _vecA = { 0,0,-1 };
	_vecA.Normalize();


	//②　ベクトルB ・・・照準への進行ベクトル
	Math::Vector3 _vecB = _dir;
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
		m_RotMat = Math::Matrix::CreateFromAxisAngle(_rotAxis, _angle);
	}
}

