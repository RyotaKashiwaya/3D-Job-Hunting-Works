#include "RifleEnemyHP.h"
#include"../../RifleEnemy/RifleEnemy.h"
void RifleEnemyHP::Update()
{
	std::shared_ptr<RifleEnemy> m_spEnemy = m_wpPearent.lock();

}

void RifleEnemyHP::DrawLit()
{
}

void RifleEnemyHP::Init()
{
	if (!m_spHpFlamePoly)
	{
		m_spHpFlamePoly = std::make_shared<KdSquarePolygon>();
	}

	if (!m_spHpGagePoly)
	{
		m_spHpGagePoly = std::make_shared<KdSquarePolygon>();
	}
}
