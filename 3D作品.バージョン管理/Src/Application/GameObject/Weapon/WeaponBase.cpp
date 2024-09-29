#include "WeaponBase.h"

void WeaponBase::Update()
{
	const std::shared_ptr<const KdGameObject> _spParent = m_wpParent.lock();
	if (_spParent)
	{
		//親の行列を取得
		Math::Matrix _parentMat = _spParent->GetMatrix();

		//親の行列を反映した行列を作成
		m_mWorld = m_localMat * m_ReloadMoveMat * _parentMat;
	}
}

void WeaponBase::DrawLit()
{
	if (!m_spModel)return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}
