#pragma once 

class ShotFire :public KdGameObject
{
public:

	ShotFire(){}
	~ShotFire(){}

	void Update()override;

	void DrawUnLit()override;
	void DrawBright()override;

	void Init()override;

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }
	
	void Shot(Math::Vector3 _mozlePos, Math::Vector3 _shotDir);
private:
	std::shared_ptr<KdRandomGenerator> m_RandomGen;

	std::shared_ptr<KdAnimator>	m_spAnimator = nullptr;

	std::shared_ptr<KdModelWork> m_spModel = nullptr;

	Math::Matrix				 m_tramsMat = Math::Matrix::Identity;

	Math::Matrix				 m_scaleMat = Math::Matrix::Identity;

	Math::Matrix				 m_rotMat = Math::Matrix::Identity;

	Math::Vector3				 m_pos = Math::Vector3::Zero;

	Math::Vector3 m_moveDir =	 Math::Vector3::Zero;

	Math::Vector3				 m_Scele = { 0.005f,0.005f,1 };

	//照準への回転行列
	Math::Matrix m_rotBulletMat;
};