#pragma once

#include"../../../GameObject/Enemy/EnemyBase.h"

class Character;

class RifleEnemy :public EnemyBase
{
public:
	RifleEnemy(){}
	~RifleEnemy()override{}

	void Update()override;
	void PostUpdate()override;

	void DrawLit()override;

	void Init()override;

	void CarRotate();

	void OnHit()override;

	void SetChara(std::shared_ptr<Character> _ptr) { m_wpChara = _ptr; }

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }

private:

	Math::Matrix			m_tramsMat = Math::Matrix::Identity;
	Math::Matrix			m_rotMat = Math::Matrix::Identity;

	std::weak_ptr<Character> m_wpChara;

	float					 m_popPosX = {};
	bool					 m_IsAvoidance = false;


	Math::Vector3				 m_pos = {};
	Math::Vector3				 m_moveDirForPop = {};
	float						 m_moveDirPowForPop = 0;
	const int					 m_distance = 100;
	float						 m_speed = {};
	int							 m_PopEndPosZ = {};
	Math::Vector3				 m_RotDir = {};
};