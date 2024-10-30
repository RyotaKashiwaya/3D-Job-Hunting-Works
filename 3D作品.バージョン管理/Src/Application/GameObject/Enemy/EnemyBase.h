#pragma once

class EnemyBase : public KdGameObject
{
public:

	EnemyBase() {}
	virtual  ~EnemyBase() override{}

	virtual void Update()override;

	virtual void DrawLit()override;

	virtual void Init()override;

	virtual void EnemyPop();

	virtual void OnHit();

protected:
	std::shared_ptr<KdRandomGenerator> m_RandomGen;

	std::shared_ptr<KdModelWork> m_spCarModel = nullptr;
	std::shared_ptr<KdModelWork> m_spHumanModel = nullptr;

	std::shared_ptr<KdModelWork> m_spWeaponModel = nullptr;
	Math::Matrix				 m_weaponMat = Math::Matrix::Identity;

	bool						IsPopDirection = false;

	bool						 IsDead = false;
};