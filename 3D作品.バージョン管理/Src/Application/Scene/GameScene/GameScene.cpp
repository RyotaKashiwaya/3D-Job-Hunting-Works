#include "GameScene.h"
#include"../SceneManager.h"

#include "../../GameObject/Terrain/Terrain.h"
#include"../../GameObject/Map/Map.h"
#include"../../GameObject/Back/Back.h"
#include "../../GameObject/Character/Character.h"
#include"../../GameObject/ArmoredCar/ArmoredCar.h"
#include"../../GameObject/Enemy/EnemyManager.h"
#include"../../GameObject/UI/Reticle/Reticle.h"
#include"../../GameObject/Weapon/Rifle/Rifle.h"
#include"../../GameObject/Bullet/Rifle/RifleBullet.h"
#include"../../GameObject/Weapon/LMG/LMG.h"
#include"../../GameObject/Bullet/LMG/LMGBullet.h"
#include"../../GameObject/UI/GunUI/GunUI.h"
#include"../../GameObject/UI/GameUI/GameUI.h"

#include "../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include "../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include "../../GameObject/Camera/CCTVCamera/CCTVCamera.h"

#include"Src/Framework/Window/KdWindow.h"

// 少数第n位で四捨五入する
void round_n(float& number, int n)
{
	number = number * pow(10, n - 1);
	number = round(number);
	number /= pow(10, n - 1);
}

void GameScene::Init()
{
	//カーソルを非表示
	ShowCursor(false);

	//===================================================================
	// ステージ初期化
	//===================================================================
	std::shared_ptr<Map> map = std::make_shared<Map>();
	map->Init();
	AddObject(map);

	/*std::shared_ptr<Terrain> _terrain = std::make_shared<Terrain>();
	_terrain->Init();
	AddObject(_terrain);*/

	//===================================================================
	// 壁初期化
	//===================================================================
	std::shared_ptr<Back> back = std::make_shared<Back>();
	back->Init();
	AddObject(back);


	//===================================================================
	// キャラクター初期化
	//===================================================================
	std::shared_ptr<Character> character = std::make_shared<Character>();
	character->Init();
	AddObject(character);

	//===================================================================
	// 装甲車初期化
	//===================================================================
	std::shared_ptr<ArmoredCar>car = std::make_shared<ArmoredCar>();
	car->Init();
	AddObject(car);

	//===================================================================
	// 敵初期化
	//===================================================================
	std::shared_ptr<EnemyManeger> enemyManeger = std::make_shared<EnemyManeger>();
	enemyManeger->Init();
	AddObject(enemyManeger);

	//===================================================================
	// 武器初期化
	//===================================================================
	std::shared_ptr<Rifle> gun = std::make_shared<Rifle>();
	gun->Init();
	AddObject(gun);

	//===================================================================
	// レティクル初期化
	//===================================================================
	std::shared_ptr<Reticle> reticle = std::make_shared<Reticle>();
	reticle->Init();
	AddObject(reticle);

	//===================================================================
	// ゲームUI初期化
	//===================================================================
	std::shared_ptr<GameUI> gameUI = std::make_shared<GameUI>();
	gameUI->Init();
	AddObject(gameUI);

	//===================================================================
	// 銃UI初期化
	//===================================================================
	std::shared_ptr<GunUI> gunui = std::make_shared<GunUI>();
	gunui->SetGun(gun);
	gunui->Init();
	AddObject(gunui);

	//===================================================================
	// カメラ初期化
	//===================================================================
	std::shared_ptr<FPSCamera>		_fpscam = std::make_shared<FPSCamera>();

	//  std::shared_ptr<TPSCamera>		_camera = std::make_shared<TPSCamera>();
	//	std::shared_ptr<CCTVCamera>		_camera = std::make_shared<CCTVCamera>();
	_fpscam->Init();
	AddObject(_fpscam);

	map->SetChara(character);
	character->SetWeapon(gun);
	character->SetParent(car);
	character->SetGameUI(gameUI);
	_fpscam->SetTarget(character);
	_fpscam->SetWeapon(gun);
	gun->SetParent(character);
	gunui->SetGameUI(gameUI);
	enemyManeger->SetRifle(gun);
	enemyManeger->SetChara(character);
	enemyManeger->SetCamera(_fpscam->GetCamera());
	enemyManeger->SetGameUI(gameUI);
}

void GameScene::Event()
{
	
}