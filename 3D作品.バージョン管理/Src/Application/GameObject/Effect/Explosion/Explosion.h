#pragma once 

class RifleEnemy;

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

	void Rotate(Math::Vector3 _mozlePos, Math::Vector3 _shotDir);

	bool IsEnd() { return AnimationEnd; }

private:
	int									animetionNum = 5;
	int									animetionEnd = 50;

	std::shared_ptr<KdRandomGenerator>	m_RandomGen;

	std::shared_ptr<KdSquarePolygon>	m_spPoly = nullptr;

	float								m_rotY = {};
	Math::Matrix						m_rotMat = Math::Matrix::Identity;
	Math::Matrix						m_transMat = Math::Matrix::Identity;
	Math::Matrix						m_scaleMat = Math::Matrix::Identity;

	Math::Vector3						m_pos = Math::Vector3::Zero;

	Math::Vector3						m_moveDir = Math::Vector3::Zero;

	Math::Vector3						m_Scele = {};

	bool								AnimationEnd = false;

	bool								EndFlg = false;
	int									EndCnt = 0;
	int									EndCntNum = 90;
};