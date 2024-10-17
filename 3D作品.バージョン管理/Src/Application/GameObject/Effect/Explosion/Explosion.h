﻿#pragma once 

class Explotion :public KdGameObject
{
public:

	Explotion() {}
	~Explotion() {}

	void Update()override;

	void DrawUnLit()override;
	void DrawBright()override;

	void Init()override;

	void SetRotY(float _rotY = 0) { m_rotY = _rotY; }

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }

	void SetScale(float _scale = 0.005f) { m_Scele = { _scale,_scale,1 }; }

	void Shot(Math::Vector3 _mozlePos, Math::Vector3 _shotDir);

	//親情報入力(死亡した際にこのクラスを呼ぶ場合などに親クラスのOnHitを作動させるため)
	void SetPearent(std::shared_ptr<KdGameObject> _ptr) { m_wpPearent = _ptr; }

private:
	std::weak_ptr<KdGameObject> m_wpPearent;

	std::shared_ptr<KdRandomGenerator> m_RandomGen;

	std::shared_ptr<KdAnimator>	m_spAnimator = nullptr;

	std::shared_ptr<KdModelWork> m_spModel = nullptr;

	Math::Matrix				 m_tramsMat = Math::Matrix::Identity;

	Math::Matrix				 m_scaleMat = Math::Matrix::Identity;

	float						 m_rotY = {};
	Math::Matrix				 m_rotMat = Math::Matrix::Identity;

	Math::Vector3				 m_pos = Math::Vector3::Zero;

	Math::Vector3 m_moveDir = Math::Vector3::Zero;

	Math::Vector3				 m_Scele = {};

	//照準への回転行列
	Math::Matrix m_rotBulletMat;
};