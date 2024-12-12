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
		if (m_TimeRectNum3 == GameScore % 10)
		{
			m_TimeRectNum3 = GameScore % 10;
		}
		else
		{
			m_TimeRectNum3 = m_RandomGen->GetInt(0, 9);
		}
		if (m_TimeRectNum2 == (GameScore / 10) % 6)
		{
			m_TimeRectNum2 = (GameScore / 10) % 6;
		}
		else
		{
			m_TimeRectNum2 = m_RandomGen->GetInt(0, 9);
		}
		if (m_TimeRectNum1 == (GameScore / 60) % 10)
		{
			m_TimeRectNum1 = (GameScore / 60) % 10;
		}
		else
		{
			m_TimeRectNum1 = m_RandomGen->GetInt(0, 9);
		}
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
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_scoreTimeTex, m_timePos.x - 60, m_timePos.y, m_timeRect.width, m_timeRect.height, &m_timeRect,&m_timeColor);

		m_timeRect = { 0 + ((long)(m_scoreTimeTex->GetWidth() / 10) * m_TimeRectNum2),0,(long)(m_scoreTimeTex->GetWidth() / 10) ,(long)m_scoreTimeTex->GetHeight()};
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_scoreTimeTex, m_timePos.x + 60, m_timePos.y, m_timeRect.width, m_timeRect.height, &m_timeRect, &m_timeColor);

		m_timeRect = { 0 + ((long)(m_scoreTimeTex->GetWidth() / 10) * m_TimeRectNum3),0,(long)(m_scoreTimeTex->GetWidth() / 10) ,(long)m_scoreTimeTex->GetHeight()};
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_scoreTimeTex, m_timePos.x + 120, m_timePos.y, m_timeRect.width, m_timeRect.height, &m_timeRect, &m_timeColor);
	}

	if (rectCnt > 5)
	{
		if (Colintensity < 0.4)
		{
			Colintensity += 0.005;
		}
		else
		{
			Colintensity = 0.4;
		}
		color = { 0.3f,0.3f,0.3f,Colintensity};
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_StrResultTex1, -435, 185, nullptr, &color, { (0.0f),(0.5f) });
	}
	else
	{
		while (1)
		{
			int i = m_RandomGen->GetInt(0, 5);
			if (rectNumEnable[i] == false)
			{
				rectNum[i] = i;
				rectNumEnable[i] = true;
				rectCnt++;
				break;
			}

			int a = rectNum[i];
		}

	
	}
	for (int i = 0; i < 6; i++)
	{
		m_strRect = { 0,0,0 + (long)(m_StrResultTex1->GetWidth() / 6 * rectNum[i]),(long)m_StrResultTex1->GetHeight()};
		color = { 1,1,1,1 };
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_StrResultTex1, -450, 200, m_strRect.width, m_strRect.height, &m_strRect, &color, { (0.0f),(0.5f) });
	}

}

void ResultUI::Init()
{
	m_RandomGen = std::make_shared<KdRandomGenerator>();

	GameScore = SceneManager::Instance().GatData(0);

	if (!m_StrResultTex1)
	{
		m_StrResultTex1 = std::make_shared<KdTexture>();
		m_StrResultTex1->Load("Asset/Textures/Scene/Result/ResultStr1.png");
	}

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
		m_scoreTimeTex->Load("Asset/Textures/Scene/Result/Number.png");
	}

	int n = 0;
	for (auto& i : rectNumEnable)
	{
		i = false;
		rectNum[n] = 0;
		Intensity[n] = 0;
		n++;
	}

}
