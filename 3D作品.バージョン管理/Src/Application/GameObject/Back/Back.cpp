#include"Back.h"
#include"../../GameObject/Character/Character.h"
void Back::DrawUnLit()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
}

void Back::Init()
{

	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelData>();
		m_spModel->Load("Asset/Models/Object/Back/Back.gltf");

		m_pCollider = std::make_unique<KdCollider>();
		m_pCollider->RegisterCollisionShape("Back", m_spModel, KdCollider::TypeGround );
	}

	m_mWorld = Math::Matrix::CreateTranslation({ 0,0,50 });
}
