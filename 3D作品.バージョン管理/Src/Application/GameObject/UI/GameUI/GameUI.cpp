#include"GameUI.h"
#include"../../../Scene/SceneManager.h"
#include"../../../main.h"
void GameUI::Update()
{
	//Application::Instance().m_log.AddLog("rectNum = %f \n", m_rectNum);
	Application::Instance().m_log.AddLog("Time = %d \n", m_TimesScoreNum3);

	TimeCount();

	if (!IsNowHit)
	{
		if (m_rectNum == 5)
		{
			SceneManager::Instance().TransferData(m_time);
			SceneManager::Instance().SetNextScene(SceneManager::SceneType::Result);
		}

		if (m_ScoreRect == (m_RemainingGoal * 60) / 100)
		{
			m_rectNum++;
			m_ScoreRect = 0;
		}
		else
		{
			m_ScoreRect++;
		}

		if (m_iconPivotY > 0.55f || m_iconPivotY < 0.45f)
		{
			m_iconMoveDir.y *= -1;
		}

		m_iconPivotY += m_iconMoveDir.y * m_iconMoveSpeed;
	}
	else
	{
		if (StopTimeCnt < StopTimeNum)
		{
			StopTimeCnt++;
		}
		else
		{
			StopTimeCnt = 0;
			IsNowHit = false;
		}
	}
}

void GameUI::DrawSprite()
{
	m_RandomGen = std::make_shared<KdRandomGenerator>();


	if (m_spTimeNumTex)
	{
		m_TimeRect = { 0 + ((long)(m_spTimeNumTex->GetWidth() / 10) * m_TimesScoreNum1),0,(long)(m_spTimeNumTex->GetWidth() / 10),(long)m_spTimeNumTex->GetHeight() };
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTimeNumTex, m_TimeUIPos.x, m_TimeUIPos.y, m_TimeRect.width, m_TimeRect.height,&m_TimeRect);
		m_TimeRect = { 0 + ((long)(m_spTimeNumTex->GetWidth() / 10) * m_TimesScoreNum2),0,(long)(m_spTimeNumTex->GetWidth() / 10),(long)m_spTimeNumTex->GetHeight() };
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTimeNumTex, m_TimeUIPos.x + 50, m_TimeUIPos.y, m_TimeRect.width, m_TimeRect.height, &m_TimeRect);
		m_TimeRect = { 0 + ((long)(m_spTimeNumTex->GetWidth() / 10) * m_TimesScoreNum3),0,(long)(m_spTimeNumTex->GetWidth() / 10),(long)m_spTimeNumTex->GetHeight() };
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTimeNumTex, m_TimeUIPos.x + 90, m_TimeUIPos.y, m_TimeRect.width, m_TimeRect.height, &m_TimeRect);
	}
	if (m_spTimeColonTex)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTimeColonTex, m_TimeUIPos.x + 22, m_TimeUIPos.y+8);
	}
	if (m_spGoalBackTex)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spGoalBackTex, m_ScoreUIPos.x, m_ScoreUIPos.y);
	}
	if (m_spRemainingGoalTex)
	{
		m_RemainingGoalRect = { 0,0,(long)m_spRemainingGoalTex->GetWidth() - (long)(m_spRemainingGoalTex->GetWidth() / 100 * m_rectNum),(long)m_spRemainingGoalTex->GetHeight() };
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spRemainingGoalTex, m_ScoreUIPos.x + (long)m_spRemainingGoalTex->GetWidth()/2, m_ScoreUIPos.y, m_RemainingGoalRect.width, m_RemainingGoalRect.height, &m_RemainingGoalRect,nullptr, { (1.0f),(0.5f) });
	}
	if (m_spGoalBerTex)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spGoalBerTex, m_ScoreUIPos.x, m_ScoreUIPos.y);
	}
	if (m_spGoalTex)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spGoalTex, m_ScoreUIPos.x + 281, m_ScoreUIPos.y + 20);
	}
	if (m_spCarIconTex)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spCarIconTex, m_ScoreUIPos.x+m_spRemainingGoalTex->GetWidth() * -0.5f + (long)(m_spRemainingGoalTex->GetWidth() / 100 * m_rectNum), m_ScoreUIPos.y,nullptr,nullptr,{(0.5f),(m_iconPivotY)});
	}
}

void GameUI::Init()
{
	

	if (!m_spTimeColonTex)
	{
		m_spTimeColonTex = std::make_shared<KdTexture>();
		m_spTimeColonTex->Load("Asset/Textures/Object/UI/GameUI/TimeColon.png");
	}
	if (!m_spTimeNumTex)
	{
		m_spTimeNumTex = std::make_shared<KdTexture>();
		m_spTimeNumTex->Load("Asset/Textures/Object/UI/GameUI/TimeNum.png");
	}
	if (!m_spGoalBerTex)
	{
		m_spGoalBerTex = std::make_shared<KdTexture>();
		m_spGoalBerTex->Load("Asset/Textures/Object/UI/GameUI/GoalBar.png");
	}
	if (!m_spGoalTex)
	{
		m_spGoalTex = std::make_shared<KdTexture>();
		m_spGoalTex->Load("Asset/Textures/Object/UI/GameUI/Goal.png");
	}
	if (!m_spGoalBackTex)
	{
		m_spGoalBackTex = std::make_shared<KdTexture>();
		m_spGoalBackTex->Load("Asset/Textures/Object/UI/GameUI/GoalBack.png");
	}
	if (!m_spRemainingGoalTex)
	{
		m_spRemainingGoalTex = std::make_shared<KdTexture>();
		m_spRemainingGoalTex->Load("Asset/Textures/Object/UI/GameUI/RemainingGoal.png");
	}
	if (!m_spCarIconTex)
	{
		m_spCarIconTex = std::make_shared<KdTexture>();
		m_spCarIconTex->Load("Asset/Textures/Object/UI/GameUI/CarIcon.png");
	}

	m_ScoreUIPos = {-200,300,0};
	m_TimeUIPos = { -600,310,0 };;
}

void GameUI::TimeCount()
{

	m_TimesScoreNum3 = m_time % 10;
	m_TimesScoreNum2 = (m_time / 10) % 6;
	m_TimesScoreNum1 = (m_time / 60) % 10;

	if (m_timeCnt == 60)
	{
		m_timeCnt = 0;
		m_time++;
	}
	else
	{
		m_timeCnt++;
	}

}

void GameUI::TimeStopForHit()
{
	if (IsNowHit)return;
	IsNowHit = true;
	StopTimeNum = m_RandomGen->GetInt(60, 300);
}
