#pragma once

class GameUI :public KdGameObject
{
public:
	GameUI() {};
	~GameUI()override {};

	void Update()override;

	void DrawSprite()override;

	void Init()override;

	void TimeCount();

	void TimeStopForHit();

	bool GetGameEnd() { return IsGameEnd; }


private:
	std::shared_ptr<KdRandomGenerator>	m_RandomGen;

	std::shared_ptr<KdTexture>  m_spTimeNumTex = nullptr;
	std::shared_ptr<KdTexture>  m_spTimeColonTex = nullptr;

	std::shared_ptr<KdTexture> m_spGoalBerTex = nullptr;
	std::shared_ptr<KdTexture> m_spGoalBackTex = nullptr;
	std::shared_ptr<KdTexture> m_spRemainingGoalTex = nullptr;
	std::shared_ptr<KdTexture> m_spGoalTex = nullptr;
	std::shared_ptr<KdTexture> m_spCarIconTex = nullptr;

	Math::Vector3			   m_ScoreUIPos = {};
	Math::Vector3			   m_TimeUIPos = {};
	Math::Rectangle			   m_RemainingGoalRect = {};

	const float				   m_RemainingGoal = 100;
	float 					   m_ScoreRect = {};
	float					   m_rectNum = {};

	float					   m_iconPivotY = 0.5f;
	Math::Vector3			   m_iconMoveDir = {0,1,0};
	float					   m_iconMoveSpeed = 0.005f;


	Math::Rectangle			   m_TimeRect = {};
	int						   m_time = {};
	int						   m_timeCnt = {};
	int						   m_TimesScoreNum1 = {};
	int						   m_TimesScoreNum2 = {};
	int						   m_TimesScoreNum3 = {};

	bool					   IsNowHit = false;
	int						   StopTimeCnt = 0;
	int						   StopTimeNum = 0;

	bool					   IsGameEnd = false;

	float					   intensity = 0;

public:

	static GameUI& Instance()
	{
		static GameUI instance;
		return instance;
	}

};