#pragma once



class RifleCartridge :public KdGameObject
{
public:

	RifleCartridge() {}
	~RifleCartridge(){}

	void Update()override;

	void DrawLit()override;

	void Init()override;

	void SetDir(Math::Vector3 _dir) { m_dir = _dir; }

	void SetPos(Math::Vector3 _pos) { LocalPos = _pos; }

	void Shot(Math::Vector3 _mozlePos, Math::Vector3 _shotDir);

	
private:



	std::shared_ptr<KdModelWork> m_spModel = nullptr;

	std::shared_ptr<KdRandomGenerator> m_RandomGen;

	Math::Matrix					   m_rotCartridge = Math::Matrix::Identity;

	Math::Matrix					   m_trans = Math::Matrix::Identity;

	//進行方向(ベクトルの向き)
	Math::Vector3					   m_moveDir = Math::Vector3::Zero;

	Math::Vector3					   m_pos = Math::Vector3::Zero;
	Math::Vector3					   LocalPos = Math::Vector3::Zero;

	Math::Vector3					   m_dir = {1,1,0};

	float							   m_speed = 0.05;

	float							   m_gravity = 0;
	float							   m_gravityPow= 0.005f;

	int								   ExpiredCnt = {};
	int								   ExpiredTime = 60;
};