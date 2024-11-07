#pragma once

class RifleEnemy;
class Character;

class RifleEnemyHP :public KdGameObject
{
public:

	void Update()override;

	void DrawSprite()override;

	void DrawLit()override;

	void Init()override;

	void SetPearent(std::shared_ptr<RifleEnemy> _ptr)
	{
		m_wpPearent = _ptr;
	}

	void SetCamera(std::shared_ptr<KdCamera> _ptr)
	{
		m_wpCamera = _ptr;
	}

private:		

	std::weak_ptr<RifleEnemy> m_wpPearent;
	std::weak_ptr<KdCamera> m_wpCamera;

	std::shared_ptr<KdSquarePolygon> m_flamePoly = nullptr;
	std::shared_ptr<KdSquarePolygon> m_gagePoly = nullptr;

	Math::Matrix					 m_ScaleMat;
	Math::Matrix					 m_LocalMat;

	Math::Vector3					 m_scale;
};