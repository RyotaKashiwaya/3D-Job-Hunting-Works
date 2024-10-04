#include "EnemyManager.h"
#include"../../Scene/SceneManager.h"
#include"../../GameObject/Enemy/RifleEnemy/RifleEnemy.h"
#include"../../GameObject/Weapon/Rifle/Rifle.h"
#include"../../GameObject/Bullet/Rifle/RifleBullet.h"
#include"../../GameObject/Character/Character.h"
#include"../../main.h"
void EnemyManeger::Update()
{
	
	EnemyPop();
	BulletHit();

	Application::Instance().m_log.AddLog("Enemy %d \n",m_enemyList.size());
}

void EnemyManeger::Init()
{
	_nowTotalEnemy = 0;
	m_RondomGen = std::make_shared<KdRandomGenerator>();
}

void EnemyManeger::BulletHit()
{
	Math::Vector3 tmpPos = {};
	std::vector<std::shared_ptr<EnemyBase>>::iterator it = m_enemyList.begin();

	std::shared_ptr<Rifle> _rifle = m_wpRifle.lock();
	bool IsErase = false;

	for (auto& enemy : m_enemyList)
	{
		for (auto& bullet : _rifle->GetBulletList())
		{
			IsErase = false;
			tmpPos = enemy->GetPos() - bullet->GetPos();
			Application::Instance().m_log.AddLog("tmpPosLength %f \n", tmpPos.Length());
			if (tmpPos.Length() < 40.0f)
			{
				enemy->OnHit();
				bullet->OnHit();
				_nowTotalEnemy--;
				m_enemyList.erase(it);
				EnemyPop();
				IsErase = true;
				break;
			}
		}
		if (IsErase)
		{
			break;
		}
		it++;
	}



}

void EnemyManeger::EnemyPop()
{

	if (_nowTotalEnemy < 3)
	{
		_nowTotalEnemy++;
		std::shared_ptr<RifleEnemy> _rifleEnemy = std::make_shared<RifleEnemy>();
		_rifleEnemy->SetChara(m_spChara);
		_rifleEnemy->SetPos({ m_RondomGen->GetFloat(-500.0f,500.0f),0,m_RondomGen->GetFloat(-1000.0f,-800.0f)});
		_rifleEnemy->Init();
		SceneManager::Instance().AddObject(_rifleEnemy);
		m_enemyList.push_back(_rifleEnemy);
	}
}
