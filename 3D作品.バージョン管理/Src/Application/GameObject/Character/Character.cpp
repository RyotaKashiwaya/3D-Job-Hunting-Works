#include "Character.h"

#include "../../main.h"
#include "../Camera/CameraBase.h"
#include"../../Scene/SceneManager.h"
#include"../../GameObject/Weapon/WeaponBase.h"

void Character::Init()
{
	m_pos.y = m_adjustHeigh;

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Character::Update()
{
	const std::shared_ptr<const KdGameObject> _spParent = m_wpParent.lock();

	m_ParentTrans = Math::Matrix::CreateTranslation(_spParent->GetPos());


	m_moveDir = Math::Vector3::Zero;

	if (!(GetAsyncKeyState(VK_LSHIFT) & 0x8000))
	{
		UpdateRotateByMouse();
	}


	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (FireTimeCnt == 0)
		{
			m_rightKeyFlg = true;
			std::shared_ptr<WeaponBase> _spWeapon = m_wpWeapon.lock();
			if (_spWeapon)
			{
				_spWeapon->ShotBullet(false);
			}
			FireTimeCnt = GunFireTime;
		}
		else
		{
			FireTimeCnt--;
		}
	}
	else
	{
		FireTimeCnt = 0;
	}

	m_moveDir = m_moveDir.TransformNormal(m_moveDir, GetRotationYMatrix());

	m_moveDir.Normalize();
	m_pos += m_moveDir * m_moveSpeed;

	Application::Instance().m_log.AddLog("m_pos.z = %f \n", m_pos.z);

	// キャラクターのワールド行列を創る処理
	Math::Matrix _trans = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix _rotation = GetRotationMatrix();
	m_mWorld = (_rotation * _trans) * m_ParentTrans;
}

void Character::PostUpdate()
{

}

void Character::OnHit()
{

}


void Character::UpdateRotateByMouse()
{
	// マウスでカメラを回転させる処理
	POINT _nowPos;
	GetCursorPos(&_nowPos);

	POINT _mouseMove{};
	_mouseMove.x = _nowPos.x - m_FixMousePos.x;
	_mouseMove.y = _nowPos.y - m_FixMousePos.y;

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	// 実際にカメラを回転させる処理(0.15はただの補正値)
	m_DegAng.x += _mouseMove.y * 0.15f;
	m_DegAng.y += _mouseMove.x * 0.15f;

	// 回転制御
	m_DegAng.x = std::clamp(m_DegAng.x, -80.f, 20.f);
}

