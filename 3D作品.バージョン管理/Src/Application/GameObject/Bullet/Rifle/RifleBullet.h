#pragma once

class Character;
class EnemyManager;

class RifleBullet :public KdGameObject
{
public:
	RifleBullet() {}
	~RifleBullet()override {}

	void Update()override;
	void PostUpdate()override;

	void DrawBright()override;

	void DrawLit()override;

	void Init()override;

	void Shot(Math::Vector3 _mozlePos, Math::Vector3 _shotDir);



	void OnHit()override;

private:
	

	std::weak_ptr<Character> m_spChara;

	//モデル情報

	std::shared_ptr<KdModelWork> m_spModel = nullptr;

	//ワールド座標
	Math::Vector3 m_pos = Math::Vector3::Zero;

	//進行方向(ベクトルの向き)
	Math::Vector3 m_moveDir = Math::Vector3::Zero;

	//移動速度(ベクトルの大きさ)
	const float m_moveSpeed = 20.0f;

	//照準への回転行列
	Math::Matrix m_rotBulletMat;

	int			 m_shotTime = 90;		

};