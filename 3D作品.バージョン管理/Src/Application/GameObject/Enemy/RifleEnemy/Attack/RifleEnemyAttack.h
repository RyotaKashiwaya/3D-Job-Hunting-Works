﻿#pragma once

class RifleEnemyAttack :public KdGameObject
{
public:

	RifleEnemyAttack(){}
	~RifleEnemyAttack()override{}

	void Update()override;

	void PostUpdate()override;

	void DrawLit()override;

	void Init()override;

	void Shot(Math::Vector3 _pos ,Math::Vector3 _targetpos);

	void OnHit()override;
private:

	std::shared_ptr<KdModelWork> m_spBullet = nullptr;
	Math::Vector3				 m_pos = {};
	Math::Vector3				 m_dir = {};

	Math::Matrix				 m_transMat = Math::Matrix::Identity;
	Math::Matrix				 m_rotMat = Math::Matrix::Identity;
	Math::Matrix				 m_ScaleMat = Math::Matrix::Identity;

	float						 m_speed = {};

	int							 m_ExpiredCnt = 10;
	int							 m_Frame = 0;


};