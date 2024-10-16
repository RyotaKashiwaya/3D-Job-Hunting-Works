#include "ResultUI.h"
#include"../../../Scene/SceneManager.h"
void ResultUI::Update()
{
	if (ScoreDisplayTime > 0)
	{
		ScoreDisplayTime--;
	}
	else
	{
		IsScoreDisplay = true;
		ScoreDisplayTime = 0;
	}
}

void ResultUI::DrawSprite()
{
	if (m_scoreRankTex)
	{
		m_scoreColor = { 1,1,1,1 };
		m_scoreRect = { 0,0,(long)m_scoreRankTex->GetWidth(),(long)m_scoreRankTex->GetHeight() };
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_scoreRankTex, m_scorePos.x, m_scorePos.y, m_scoreRect.x, m_scoreRect.y, &m_scoreRect, &m_scoreColor);
	}

	m_timeColor = { 1,1,1,1 };
	if (m_scoreTimeColonTex)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_scoreTimeColonTex, m_timePos.x, m_timePos.y, nullptr, &m_timeColor);
	}

}

void ResultUI::Init()
{
	m_RandomGen = std::make_shared<KdRandomGenerator>();

	GameScore = SceneManager::Instance().GatData(0);

	if (!m_scoreRankTex)
	{
		m_scoreRankTex = std::make_shared<KdTexture>();
		m_scoreRankTex->Load("Asset/Textures/Scene/Result/scoreRank.png");
	}

	if (!m_scoreTimeColonTex)
	{
		m_scoreTimeColonTex = std::make_shared<KdTexture>();
		m_scoreTimeColonTex->Load("Asset/Textures/Scene/Result/timeColon.png");
	}
	if (!m_scoreTimeTex1)
	{
		m_scoreTimeTex1 = std::make_shared<KdTexture>();
		m_scoreTimeTex1->Load("Asset/Textures/Scene/Result/timeNum.png");
	}
	if (!m_scoreTimeTex2)
	{
		m_scoreTimeTex2 = std::make_shared<KdTexture>();
		m_scoreTimeTex2->Load("Asset/Textures/Scene/Result/timeNum.png");
	}
	if (!m_scoreTimeTex3)
	{
		m_scoreTimeTex3 = std::make_shared<KdTexture>();
		m_scoreTimeTex3->Load("Asset/Textures/Scene/Result/timeNum.png");
	}
}
