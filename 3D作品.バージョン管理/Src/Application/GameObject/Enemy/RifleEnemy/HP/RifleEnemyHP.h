#pragma once

class RifleEnemy;

class RifleEnemyHP :public KdGameObject
{
public:

	void Update()override;

	void DrawLit()override;

	void Init()override;

	void SetPearent(std::shared_ptr<RifleEnemy> _ptr)
	{
		m_wpPearent = _ptr;
	}

private:

	std::weak_ptr<RifleEnemy> m_wpPearent;

	std::shared_ptr<KdSquarePolygon> m_spHpGagePoly = nullptr;
	std::shared_ptr<KdSquarePolygon> m_spHpFlamePoly = nullptr;

	Math::Vector3					 m_HPpos;

	Math::Rectangle					 m_rect;

};