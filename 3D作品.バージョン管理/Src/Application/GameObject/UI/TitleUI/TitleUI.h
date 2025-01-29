#pragma once

class TitleUI :public KdGameObject
{
public:

	TitleUI() {};
	~TitleUI() {};

	void Init()override;

	void Update()override;

	void DrawSprite()override;

private:

	Math::Matrix m_scale;
	Math::Matrix m_scaleN;

	std::shared_ptr<KdTexture> m_titleback = nullptr;

	std::shared_ptr<KdTexture> m_titletexTop = nullptr;
	std::shared_ptr<KdTexture> m_titletexUnder = nullptr;

	std::shared_ptr<KdTexture> m_titleStartTex = nullptr;
	Math::Color StartColor = {};

	Math::Color TopColor = {};
	Math::Color UnderColor = {};

	Math::Vector2 TopPos = { 0,0 };
	Math::Vector2 UnderPos = { TopPos.x + 10,TopPos.y - 10 };

	float Topintensity = 0;
	float Underintensity = 0;
	float IntensityNum = 0.01;

	bool firstDraw = false;
	float startIntensity = 0;
	float startIntensityNum = 0.01;

	bool DrawEnd = false;
};