#include "RifleEnemyHP.h"
#include"../../RifleEnemy/RifleEnemy.h"
#include"../../../../GameObject/Character/Character.h";
#include"../../../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include"../../../../main.h";
void RifleEnemyHP::Update()
{
	std::shared_ptr<RifleEnemy> m_spEnemy = m_wpPearent.lock();
	Math::Matrix			  EnemyMat = Math::Matrix::Identity;
	if (m_spEnemy)
	{
		EnemyMat = m_spEnemy->GetMatrix();
	}

	m_mWorld = m_ScaleMat * m_LocalMat * EnemyMat;
}

void RifleEnemyHP::DrawSprite()
{
	//Math::Vector3 _result = Math::Vector3::Zero;
	//std::shared_ptr<RifleEnemy> m_spEnemy = m_wpPearent.lock();
	//std::shared_ptr<KdCamera> m_spCamera = m_wpCamera.lock();
	//if (m_spCamera)
	//{
	//	m_spCamera->ConvertWorldToScreenDetail(m_spEnemy->GetPos(), _result);
	//	_result.y += 100;
	//}

	//KdShaderManager::Instance().m_spriteShader.DrawTex(m_gageTex, _result.x, _result.y);

	//KdShaderManager::Instance().m_spriteShader.DrawTex(m_flameTex, _result.x, _result.y);

}

void RifleEnemyHP::DrawLit()
{
	if (m_gagePoly)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_gagePoly, m_mWorld);
	}
	if (m_flamePoly)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_flamePoly, m_mWorld);
	}
}



void RifleEnemyHP::Init()
{
	//if (!m_flameTex)
	//{
	//	m_flameTex = std::make_shared<KdTexture>();
	//	m_flameTex->Load("Asset/Textures/Object/UI/EnemyUI/EnemyHP/EnemyHPFlame.png");
	//}
	//if (!m_gageTex)
	//{
	//	m_gageTex = std::make_shared<KdTexture>();
	//	m_gageTex->Load("Asset/Textures/Object/UI/EnemyUI/EnemyHP/EnemyHPGage.png");
	//}

	if (!m_gagePoly)
	{
		m_gagePoly = std::make_shared<KdSquarePolygon>();
		m_gagePoly->SetMaterial("Asset/Textures/Object/UI/EnemyUI/EnemyHP/EnemyHPGage.png");
	}

	if (!m_flamePoly)
	{
		m_flamePoly = std::make_shared<KdSquarePolygon>();
		m_flamePoly->SetMaterial("Asset/Textures/Object/UI/EnemyUI/EnemyHP/EnemyHPFlame.png");
	}

	m_scale = { 30,5,0 };

	m_ScaleMat = Math::Matrix::CreateScale(m_scale);
	m_LocalMat = Math::Matrix::CreateTranslation(0, 50, 0);
}
