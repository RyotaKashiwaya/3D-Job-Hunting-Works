#pragma once

class EnemyBase;
class Rifle;
class Character;
class FPSCamera;

#define MAXENEMYNUM = 5;

class EnemyManeger :public KdGameObject
{
public:

	void Update()override;

	void Init()override;

	void SetRifle(std::shared_ptr<Rifle> _ptr) { m_wpRifle = _ptr; }
	void SetChara(std::shared_ptr<Character> _ptr) { m_spChara = _ptr; }
	void SetCamera(std::shared_ptr<KdCamera> _ptr) { m_wpCam = _ptr; }

	void BulletHit();

	void EnemyDet() { _nowTotalEnemy--; }

	void EnemyPop();

	std::vector<std::shared_ptr<EnemyBase>> GetEnemyList() { return m_enemyList; }
private:
	std::shared_ptr<KdRandomGenerator> m_RondomGen;

	std::weak_ptr<Rifle> m_wpRifle;
	std::shared_ptr<Character> m_spChara;
	std::weak_ptr<KdCamera> m_wpCam;

	std::vector<std::shared_ptr<EnemyBase>> m_enemyList;

	int							_nowTotalEnemy = 0; 
	static const int			MaxEnemyNum = 2;

	int							EnemyPopCnt = 0;
	int							EnemyPopCntNum = 0;

public:

	static EnemyManeger& Instance()
	{
		static EnemyManeger instance;
		return instance;
	}

};