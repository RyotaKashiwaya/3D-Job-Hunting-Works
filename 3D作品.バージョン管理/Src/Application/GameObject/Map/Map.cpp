#include "Map.h"
#include"../../GameObject/Terrain/Terrain.h"
#include"../../GameObject/Terrain/Building.h"
#include"../../GameObject/Back/Back.h"
#include"../../GameObject/Character/Character.h"
#include"../../Scene/SceneManager.h"

void Map::Update()
{

	int _rot = m_RandomGen->GetInt(0, 50);
	if (BuildingMakeCnt == 0)
	{
		if (_rot < 10)
		{

			BuildingMakeCnt = m_RandomGen->GetInt(60, 150);
			MakeBuilding();
		}
	}
	else
	{
		BuildingMakeCnt--;
	}

	if (m_pos.z < 2000)
	{
		m_pos.z += 40;
		MakeTerrain();
	}
	else
	{
		m_pos.z = 2000;

		if (TerrainMakeCnt > 4)
		{
			TerrainMakeCnt = 0;
			MakeTerrain();
		}
		TerrainMakeCnt++;
	}

	
}
void Map::Init()
{
	m_RandomGen = std::make_shared<KdRandomGenerator>();

	m_pos.z = -150;
	MakeTerrain();
}

void Map::MakeTerrain()
{
	std::shared_ptr<Terrain> _terrain = std::make_shared<Terrain>();
	_terrain->Init();
	_terrain->SetChara(m_spChara);
	_terrain->SetPos(m_pos);
	SceneManager::Instance().AddObject(_terrain);
}

void Map::MakeBuilding()
{
	int _rot = m_RandomGen->GetInt(0, 1000);
	Math::Vector3 _pos = m_pos;
	if (_rot > 750)
	{
		_pos.x = 800;
	}
	else if(_rot > 500)
	{
		_pos.x = 1000;
	}
	else if (_rot > 250)
	{
		_pos.x = -800;
	}
	else 
	{
		_pos.x = -1000;
	}
	std::shared_ptr<Building> _building = std::make_shared<Building>();
	_building->Init();
	_building->SetChara(m_spChara);
	_building->SetPos(_pos);
	SceneManager::Instance().AddObject(_building);
}
