#pragma once

class RifleEnemy;

class RifleEnemyWeapon :public KdGameObject
{
public:

	RifleEnemyWeapon(){}
	~RifleEnemyWeapon(){}

	void Update()override;

	void DrawLit()override;

	void Init()override;

	void SetRIfleEnemy(const std::shared_ptr<RifleEnemy>& _ptr) { m_wpEnemy = _ptr; }

private:

	std::weak_ptr< RifleEnemy> m_wpEnemy;

	std::shared_ptr<KdModelWork> m_spModel = nullptr;


};