#pragma once

class Character;

class Map :public KdGameObject
{
public:

	Map(){}
	~Map(){}

	void Update()override;
	void Init()override;

	void MakeTerrain();

	void MakeBuilding();

	void SetChara(const std::shared_ptr<Character> _ptr)
	{
		m_spChara = _ptr;
	}

private:

	std::shared_ptr<KdRandomGenerator> m_RandomGen;

	std::shared_ptr<Character> m_spChara;

	Math::Vector3				m_pos = {};

	int							TerrainMakeCnt = {};

	int							BuildingMakeCnt = 0;
};