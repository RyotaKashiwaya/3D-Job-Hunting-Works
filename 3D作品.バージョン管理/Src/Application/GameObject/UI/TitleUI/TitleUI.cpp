#include "TitleUI.h"
#include"../../../Scene/SceneManager.h"
void TitleUI::Init()
{
	KdAudioManager::Instance().Play("Asset/Sounds/Scene/TitleScene/titlebgm.wav")->SetVolume(0.25);

	if (!m_titleback)
	{
		m_titleback = std::make_shared<KdTexture>();
		m_titleback->Load("Asset/Textures/Scene/Title/back.png");
	}
	if (!m_titleStartTex)
	{
		m_titleStartTex = std::make_shared<KdTexture>();
		m_titleStartTex->Load("Asset/Textures/Scene/Title/start.png");
	}
	if (!m_titletexTop)
	{
		m_titletexTop = std::make_shared<KdTexture>();
		m_titletexTop->Load("Asset/Textures/Scene/Title/TitleTexTop.png");
	}
	if (!m_titletexUnder)
	{
		m_titletexUnder = std::make_shared<KdTexture>();
		m_titletexUnder->Load("Asset/Textures/Scene/Title/TitleTexUnder.png");
	}

	m_scale = Math::Matrix::CreateScale({ 1.5,1.5,0 });
	m_scaleN = Math::Matrix::CreateScale({ 1,1,0 });
}

void TitleUI::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		KdAudioManager::Instance().StopAllSound();
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Game
		);
	}

	if (Topintensity < 1)
	{
		Topintensity += IntensityNum;
	}
	else
	{
		Topintensity = 1;

		if (Underintensity < 0.6)
		{
			Underintensity += IntensityNum;
		}
		else
		{
			Underintensity = 0.6;
			DrawEnd = true;
		}
	}

	if (DrawEnd)
	{
		UnderPos = { TopPos.x + 10,TopPos.y - 10 };

		if (TopPos.y < 100)
		{
			TopPos.y += 0.8;
		}
		else
		{
			TopPos.y = 100;
			if (!firstDraw)
			{
				if (startIntensity > 0.3)
				{
					firstDraw = true;
				}

				startIntensity += startIntensityNum;
			}
			else {
				if (startIntensity > 0.9 || startIntensity < 0.3)
				{
					startIntensityNum *= -1;
				}
				startIntensity += startIntensityNum;
			}
		}
		
	}
}

void TitleUI::DrawSprite()
{

	if (m_titleback)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_titleback, 0, 0);
	}

	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_scale);

	if (m_titletexUnder)
	{
		UnderColor = {1,1,1,Underintensity};
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_titletexUnder, UnderPos.x, UnderPos.y, nullptr, &UnderColor);
	}
	if (m_titletexTop)
	{
		TopColor = { 1,1,1,Topintensity };
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_titletexTop, TopPos.x, TopPos.y, nullptr, &TopColor);
	}

	if (m_titleStartTex)
	{
		StartColor = { 1,1,1,startIntensity };
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_titleStartTex, 0,-80, nullptr, &StartColor);
	}

	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_scaleN);
}
