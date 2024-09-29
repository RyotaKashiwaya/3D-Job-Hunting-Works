#pragma once

class Character;

class Back :public KdGameObject
{
public:

	Back() {}
	~Back() {}

	void DrawUnLit()override;
	void Init() override;

	void SetChara(std::shared_ptr<Character> _ptr)
	{
		m_wpChara = _ptr;
	};


private:

	std::shared_ptr<KdModelData>m_spModel = nullptr;
	std::weak_ptr<Character> m_wpChara;

};