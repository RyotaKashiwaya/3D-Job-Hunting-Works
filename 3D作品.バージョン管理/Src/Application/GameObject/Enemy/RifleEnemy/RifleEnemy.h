﻿#pragma once

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

	void WeaponRotate();
private:



	Math::Matrix			m_tramsMat = Math::Matrix::Identity;
	Math::Matrix			m_rotMat = Math::Matrix::Identity;

	Math::Matrix			m_weapomLocal = Math::Matrix::Identity;
	Math::Matrix			m_weapomTrans = Math::Matrix::Identity;
	Math::Matrix			m_weapomScale = Math::Matrix::Identity;
	Math::Matrix			m_weapomRot = Math::Matrix::Identity;

	Math::Matrix			m_WeaponMazzleMat = Math::Matrix::Identity;
	Math::Vector3			m_WeaponMazzlePos = Math::Vector3::Zero;

	std::weak_ptr<Character> m_wpChara;

	float					 m_popPosX = {};
	bool					 m_IsAvoidance = false;


	Math::Vector3				 m_pos = {};
	Math::Vector3				 m_moveDirForPop = {};
	float						 m_moveDirPowForPop = 0;
	const int					 m_distance = 50;
	float						 m_speed = {};
	int							 m_PopEndPosZ = {};
	Math::Vector3				 m_RotDir = {};

	bool						 m_IsAttack = false;
	int							 AttackCnt = 0;
	int							 AttackCntNum = 3;

	int							 bulletCnt = 0;
	int							 bulletCntNum = 3;

	bool						 keyFlg = false;

	int							 Flame = {};
};