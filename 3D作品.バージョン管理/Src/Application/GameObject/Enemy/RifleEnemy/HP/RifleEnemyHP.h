#pragma once

class RifleEnemy;
class Character;
class GameUI;


class RifleEnemyHP :public KdGameObject
{
public:

	void Update()override;

	void DrawSprite()override;

	void Init()override;

	void SetPearent(std::shared_ptr<RifleEnemy> _ptr)
	{
		m_wpPearent = _ptr;
	}

	void SetChara(std::shared_ptr<Character> _ptr){m_wpChara = _ptr;}
	void SetCamera(std::shared_ptr<KdCamera> _ptr){m_wpCam = _ptr;}
	void SetGameUI(std::shared_ptr<GameUI> _ptr){m_wpGameUI = _ptr;}
	void SetExpired(bool _flg) { m_isExpired = _flg; }

	void Rotate();
private:		

	std::weak_ptr<RifleEnemy> m_wpPearent;
	std::weak_ptr<Character> m_wpChara;
	std::weak_ptr<KdCamera> m_wpCam;
	std::weak_ptr<GameUI> m_wpGameUI;

	//std::shared_ptr<KdSquarePolygon> m_flamePoly = nullptr;
	//std::shared_ptr<KdSquarePolygon> m_gagePoly = nullptr;
	//std::shared_ptr<KdSquarePolygon> m_gageUnderPoly = nullptr;

	std::shared_ptr<KdTexture> m_flameTex = nullptr;
	std::shared_ptr<KdTexture> m_gageTex1 = nullptr;
	std::shared_ptr<KdTexture> m_gageTex2 = nullptr;
	std::shared_ptr<KdTexture> m_gageTex3 = nullptr;
	std::shared_ptr<KdTexture> m_gageUnderTex = nullptr;


	Math::Matrix					 m_ScaleMat;
	Math::Matrix					 m_RotMat;
	Math::Vector3					 m_LocalPos;

	Math::Vector2					 m_scale;

	Math::Rectangle					 m_rect;

	bool							 IsHit = false;
	int								 HpDrawCnt = 0;
	int								 HpDrawCntNum = 300;

	int oldLife = 0;
	int maxlife = 0;

	int cnt = 0;
	int cntrect = 0;
};