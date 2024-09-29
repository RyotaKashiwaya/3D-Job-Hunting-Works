#pragma once;

class ArmoredCar :public KdGameObject
{
public:

	ArmoredCar() {};
	~ArmoredCar() {};

	void Update()override;

	void DrawLit()override;

	void Init()override;


private :

	//親(持ち主)の情報
	std::weak_ptr<KdGameObject> m_wpParent;
	
	std::shared_ptr<KdModelData> m_spModel = nullptr;

	Math::Vector3				m_pos = Math::Vector3::Zero;
};