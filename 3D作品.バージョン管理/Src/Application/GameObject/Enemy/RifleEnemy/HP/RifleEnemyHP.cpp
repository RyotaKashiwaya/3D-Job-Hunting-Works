#include "RifleEnemyHP.h"
#include"../../RifleEnemy/RifleEnemy.h"
#include"../../../../GameObject/Character/Character.h";
#include"../../../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include"../../../../main.h";
void RifleEnemyHP::Update()
{
	std::shared_ptr<RifleEnemy> m_spEnemy = m_wpPearent.lock();

	if (!m_spEnemy)
	{
		m_isExpired = true;
		return;
	}
	Rotate();

	Math::Vector3 m_pos = m_spEnemy->GetPos() + m_LocalPos;
	Math::Matrix m_TransMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = m_ScaleMat * m_RotMat * m_TransMat;
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
		m_gagePoly->SetMaterial("Asset/Textures/Object/UI/EnemyUI/EnemyHP/EnemyHPGage1.png");
	}

	if (!m_flamePoly)
	{
		m_flamePoly = std::make_shared<KdSquarePolygon>();
		m_flamePoly->SetMaterial("Asset/Textures/Object/UI/EnemyUI/EnemyHP/EnemyHPFlame.png");
	}

	m_scale = { 60,5,0 };

	m_ScaleMat = Math::Matrix::CreateScale(m_scale);
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
