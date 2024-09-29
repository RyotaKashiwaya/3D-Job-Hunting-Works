#pragma once

class EnemyBase;
class Rifle;
class Character;

class EnemyManeger :public KdGameObject
{
public:

	void Update()override;

	void Init()override;

	void SetRifle(std::shared_ptr<Rifle> _ptr) { m_wpRifle = _ptr; }
	void SetChara(std::shared_ptr<Character> _ptr) { m_spChara = _ptr; }

	void BulletHit();

	void EnemyDet() { _nowTotalEnemy--; }

	void EnemyPop();
private:
	std::shared_ptr<KdRandomGenerator> m_RondomGen;

	std::weak_ptr<Rifle> m_wpRifle;
	std::shared_ptr<Character> m_spChara;

	std::vector<std::shared_ptr<EnemyBase>> m_enemyList;

	int							_nowTotalEnemy = 0; 

};