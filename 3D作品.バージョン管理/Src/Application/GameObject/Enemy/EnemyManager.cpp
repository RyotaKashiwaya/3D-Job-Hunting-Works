#include "EnemyManager.h"
#include"../../Scene/SceneManager.h"
#include"../../GameObject/Enemy/RifleEnemy/RifleEnemy.h"
#include"../../GameObject/Enemy/RifleEnemy/HP/RifleEnemyHP.h"
#include"../../GameObject/Weapon/Rifle/Rifle.h"
#include"../../GameObject/Bullet/Rifle/RifleBullet.h"
#include"../../GameObject/Character/Character.h"
#include"../../GameObject/UI/GameUI/GameUI.h"
#include"../../main.h"
void EnemyManeger::Update()
{
	std::vector<std::shared_ptr<EnemyBase>>::iterator it = m_enemyList.begin();
	for (auto& enemy : m_enemyList)
	{
		if (enemy->IsExpired() == true)
		{
			m_enemyList.erase(it);
			_nowTotalEnemy--;
			break;
		}
		it++;
	}

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

	if (_nowTotalEnemy < MaxEnemyNum)
	{
		if (EnemyPopCnt > EnemyPopCntNum)
		{
			EnemyPopCntNum = m_RondomGen->GetInt(60, 300);
			EnemyPopCnt = 0;
			_nowTotalEnemy++;
			std::shared_ptr<RifleEnemy> _rifleEnemy = std::make_shared<RifleEnemy>();
			_rifleEnemy->SetChara(m_spChara);
			_rifleEnemy->SetPos({ (m_RondomGen->GetInt(0,1) * -2 + 1) * m_RondomGen->GetFloat(200.0f,1200.0f),0,m_RondomGen->GetFloat(-1000.0f,-800.0f) });
			_rifleEnemy->Init();

			std::shared_ptr<RifleEnemyHP> _rifleHP = std::make_shared<RifleEnemyHP>();
			_rifleHP->SetChara(m_spChara);
			_rifleHP->SetPearent(_rifleEnemy);
			_rifleHP->SetPos(_rifleEnemy->GetPos());
			_rifleHP->SetCamera(m_wpCam.lock());
			_rifleHP->SetGameUI(m_wpGameUI.lock());
			_rifleHP->Init();

			_rifleEnemy->SetUI(_rifleHP);

			SceneManager::Instance().AddObject(_rifleEnemy);
			SceneManager::Instance().AddObject(_rifleHP);

			m_enemyList.push_back(_rifleEnemy);
		}
		else
		{
			EnemyPopCnt++;
		}
	}
}
