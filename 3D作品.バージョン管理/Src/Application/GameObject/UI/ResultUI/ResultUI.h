﻿#pragma once

class ResultUI :public KdGameObject
{
public:
	ResultUI(){}
	~ResultUI()override{}

	void Update()override;

	void DrawSprite()override;

	void Init()override;



private:

	// 乱数生成器
	std::shared_ptr<KdRandomGenerator> m_RandomGen;

	Math::Rectangle			   m_scoreRect = {};
	Math::Rectangle			   m_timeRect = {};

	Math::Color				   m_scoreColor = {};
	Math::Color				   m_timeColor = {};

	int						   m_TimeRectNum1 = 0;
	int						   m_TimeRectNum2 = 0;
	int						   m_TimeRectNum3 = 0;

	std::shared_ptr<KdTexture> m_StrResultTex1 = nullptr;
	Math::Rectangle			   m_strRect = {};

	std::shared_ptr<KdTexture> m_scoreTimeTex = nullptr;

	std::shared_ptr<KdTexture> m_scoreTimeColonTex = nullptr;

	std::shared_ptr<KdTexture> m_scoreRankTex = nullptr;

	std::shared_ptr<KdTexture> m_backTex = nullptr;

	int GameScore = {};

	int ScoreDisplayTime = 120;
	bool IsScoreDisplay = false;

	Math::Vector3			   m_scorePos = {};
	Math::Vector3			   m_timePos = {};

	bool					resultTextDraw[7];
	bool					DrawEnd = false;
	int						Cnt = 0;
	int						CntNum = 0;


	Math::Color color = { };
	float Colintensity = 0;
};