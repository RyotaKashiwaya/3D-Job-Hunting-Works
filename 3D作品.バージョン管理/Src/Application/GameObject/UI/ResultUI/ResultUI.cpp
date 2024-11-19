#include "ResultUI.h"
#include"../../../Scene/SceneManager.h"
void ResultUI::Update()
{
	if (!IsScoreDisplay)
	{
		m_TimeRectNum3 = m_RandomGen->GetInt(0, 9);
		m_TimeRectNum2 = m_RandomGen->GetInt(0, 9);
		m_TimeRectNum1 = m_RandomGen->GetInt(0, 9);
	}
	else
	{
		m_TimeRectNum3 = GameScore % 10;
		m_TimeRectNum2 = (GameScore / 10) % 6;
		m_TimeRectNum1 = (GameScore / 60) % 10;
	}

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
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_scoreTimeColonTex, m_timePos.x, m_timePos.y + 8, nullptr, &m_timeColor);
	}


	if (m_scoreTimeTex)
	{
		m_timeRect = { 0 + ((long)(m_scoreTimeTex->GetWidth() / 10) * m_TimeRectNum1),0,(long)(m_scoreTimeTex->GetWidth() / 10) ,(long)m_scoreTimeTex->GetHeight() };
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_scoreTimeTex, m_timePos.x - 40, m_timePos.y, m_timeRect.width, m_timeRect.height, &m_timeRect,&m_timeColor);

		m_timeRect = { 0 + ((long)(m_scoreTimeTex->GetWidth() / 10) * m_TimeRectNum2),0,(long)(m_scoreTimeTex->GetWidth() / 10) ,(long)m_scoreTimeTex->GetHeight()};
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_scoreTimeTex, m_timePos.x + 40, m_timePos.y, m_timeRect.width, m_timeRect.height, &m_timeRect, &m_timeColor);

		m_timeRect = { 0 + ((long)(m_scoreTimeTex->GetWidth() / 10) * m_TimeRectNum3),0,(long)(m_scoreTimeTex->GetWidth() / 10) ,(long)m_scoreTimeTex->GetHeight()};
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_scoreTimeTex, m_timePos.x + 80, m_timePos.y, m_timeRect.width, m_timeRect.height, &m_timeRect, &m_timeColor);
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
	if (!m_scoreTimeTex)
	{
		m_scoreTimeTex = std::make_shared<KdTexture>();
		m_scoreTimeTex->Load("Asset/Textures/Scene/Result/timeNum.png");
	}

}
