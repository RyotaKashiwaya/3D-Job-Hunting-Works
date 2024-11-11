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

	void SetCamera(std::shared_ptr<Character> _ptr)
	{
		m_wpChara = _ptr;
	}

	void SetExpired(bool _flg) { m_isExpired = _flg; }

	void Rotate();
private:		

	std::weak_ptr<RifleEnemy> m_wpPearent;
	std::weak_ptr<Character> m_wpChara;

	std::shared_ptr<KdSquarePolygon> m_flamePoly = nullptr;
	std::shared_ptr<KdSquarePolygon> m_gagePoly = nullptr;

	Math::Matrix					 m_ScaleMat;
	Math::Matrix					 m_RotMat;
	Math::Vector3					 m_LocalPos;

	Math::Vector3					 m_scale;
};