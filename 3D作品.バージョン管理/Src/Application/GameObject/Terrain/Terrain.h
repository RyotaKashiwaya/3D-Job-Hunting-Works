#pragma once

class Character;

class Terrain : public KdGameObject
{
public:
	Terrain() {}
	virtual ~Terrain()		override {}

	void Init()				override;
	void Update()			override;
	void DrawLit()			override;

	void SetChara(std::shared_ptr<Character> _ptr)
	{
		m_wpChara = _ptr;
	};

	void SetPos(Math::Vector3 _pos)
	{
		m_pos = _pos;
	}

private:
	std::shared_ptr<KdModelWork> m_spModel = nullptr;
	std::weak_ptr<Character> m_wpChara;

	Math::Matrix			 m_scale;
	Math::Matrix			 m_trans;
	Math::Vector3			 m_size = Math::Vector3::Zero;

	Math::Vector3			 m_pos = Math::Vector3::Zero;
	Math::Vector3			 m_moveDir = Math::Vector3::Zero;
	float					 m_moveSpeed = 10;

};