#include "Building.h"
#include"../../GameObject/Character/Character.h"
void Building::Init()
{


	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Models/Object/Terrain/building.gltf");

		m_pCollider = std::make_unique<KdCollider>();
		m_pCollider->RegisterCollisionShape("building", m_spModel, KdCollider::TypeGround );
	}
	m_size = { 1,1,1 };
	m_moveDir = { 0,0,-1 };
	m_trans = Math::Matrix::CreateTranslation(m_pos);
	m_scale = Math::Matrix::CreateScale(m_size);
	m_mWorld = m_scale * m_trans;
}

void Building::Update()
{

	if (m_pos.z < m_wpChara.lock()->GetPos().z - 2000)
	{
		m_isExpired = true;
	}

	m_pos += m_moveDir * m_moveSpeed;

	m_trans = Math::Matrix::CreateTranslation(m_pos);
	m_scale = Math::Matrix::CreateScale(m_size);

	m_mWorld = m_scale * m_trans;
}

void Building::DrawLit()
{
	if (!m_spModel) return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}
