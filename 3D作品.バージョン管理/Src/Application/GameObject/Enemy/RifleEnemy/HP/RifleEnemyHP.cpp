#include "RifleEnemyHP.h"
#include"../../RifleEnemy/RifleEnemy.h"
#include"../../../../GameObject/Character/Character.h";
#include"../../../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include"../../../../main.h";
void RifleEnemyHP::Update()
{
	Application::Instance().m_log.AddLog("oldlif =  %d \n", oldLife);


	std::shared_ptr<RifleEnemy> m_spEnemy = m_wpPearent.lock();

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

	m_mWorld = m_ScaleMat *  m_RotMat * m_TransMat;
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

	if (IsHit)
	{

		KdShaderManager::Instance().m_spriteShader.SetMatrix(Math::Matrix::CreateScale(0.3));
		if (m_gageUnderTex)
		{
			KdShaderManager::Instance().m_spriteShader.DrawTex(m_gageUnderTex, _result.x, _result.y);
		}

		if (oldLife > 6)
		{
			if (m_gageTex1)
			{
				m_rect = { 0 + ((long)m_gageTex1->GetWidth() / maxlife) * (maxlife - oldLife) ,0,(long)m_gageTex1->GetWidth()  ,(long)m_gageTex1->GetHeight() };
				KdShaderManager::Instance().m_spriteShader.DrawTex(m_gageTex1, _result.x, _result.y, m_gageTex1->GetWidth(), m_gageTex1->GetHeight(), &m_rect);
			}
		}
		else if(oldLife > 3)
		{
			if (m_gageTex2)
			{
				m_rect = { 0 + ((long)m_gageTex2->GetWidth() / maxlife) * (maxlife - oldLife) ,0,(long)m_gageTex2->GetWidth()  ,(long)m_gageTex2->GetHeight() };
				KdShaderManager::Instance().m_spriteShader.DrawTex(m_gageTex2, _result.x, _result.y, m_gageTex2->GetWidth(), m_gageTex2->GetHeight(), &m_rect);
			}
		}
		else
		{
			if (m_gageTex3)
			{
				m_rect = { 0 + ((long)m_gageTex3->GetWidth() / maxlife) * (maxlife - oldLife) ,0,(long)m_gageTex3->GetWidth()  ,(long)m_gageTex3->GetHeight() };
				KdShaderManager::Instance().m_spriteShader.DrawTex(m_gageTex3, _result.x, _result.y, m_gageTex3->GetWidth(), m_gageTex3->GetHeight(), &m_rect);
			}
		}
		if (m_flameTex)
		{
			KdShaderManager::Instance().m_spriteShader.DrawTex(m_flameTex, _result.x, _result.y);
		}

		KdShaderManager::Instance().m_spriteShader.SetMatrix(Math::Matrix::CreateScale(1));
	}

	Application::Instance().m_log.AddLog("x = %d ,y = %d,w = %d,h = %d \n", m_rect.x, m_rect.y, m_rect.width, m_rect.height);
}


void RifleEnemyHP::Init()
{

	oldLife = m_wpPearent.lock()->GetLife();

	if (!m_flameTex)
	{
		m_flameTex = std::make_shared<KdTexture>();
		m_flameTex->Load("Asset/Textures/Object/UI/EnemyUI/EnemyHP/EnemyHPFlame.png");
	}
		
	if (!m_gageTex1)
	{
		m_gageTex1 = std::make_shared<KdTexture>();
		m_gageTex1->Load("Asset/Textures/Object/UI/EnemyUI/EnemyHP/EnemyHPGage1.png");
	}
	if (!m_gageTex2)
	{
		m_gageTex2 = std::make_shared<KdTexture>();
		m_gageTex2->Load("Asset/Textures/Object/UI/EnemyUI/EnemyHP/EnemyHPGage2.png");
	}
	if (!m_gageTex3)
	{
		m_gageTex3 = std::make_shared<KdTexture>();
		m_gageTex3->Load("Asset/Textures/Object/UI/EnemyUI/EnemyHP/EnemyHPGage3.png");
	}

	if (!m_gageUnderTex)
	{
		m_gageUnderTex = std::make_shared<KdTexture>();
		m_gageUnderTex->Load("Asset/Textures/Object/UI/EnemyUI/EnemyHP/EnemyHPGageUnder.png");
	}


	maxlife = m_wpPearent.lock()->GetMaxLife();


	m_ScaleMat = Math::Matrix::CreateScale(0.5);

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

