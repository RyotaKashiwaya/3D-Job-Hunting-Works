#include "ArmoredCar.h"

void ArmoredCar::Update()
{
	m_mWorld = Math::Matrix::CreateTranslation(m_pos);
}

void ArmoredCar::DrawLit()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
}

void ArmoredCar::Init()
{
	//親(プレイヤー)の行列を取得
	Math::Matrix _parentMat = Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject> _spParent = m_wpParent.lock();
	if (_spParent)
	{
		//親の行列を取得
		_parentMat = _spParent->GetMatrix();
	}

	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelData>();
		m_spModel->Load("Asset/Models/Object/ArmoredCar/ArmoredCar.gltf");
	}
	m_pos = { 0,10,0 };
}
