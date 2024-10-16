#pragma once

class CameraBase;
class WeaponBase;
class GameUI;

class Character : public KdGameObject
{
public:
	Character()							{}
	~Character()			override	{}

	void Init()				override;
	void Update()			override;
	void PostUpdate()		override;

	void SetParent(const std::shared_ptr<KdGameObject>& parent)
	{
		m_wpParent = parent;
	}

	void SetWeapon(const std::shared_ptr<WeaponBase>& weapon)
	{
		m_wpWeapon = weapon;
	}

	void SetGameUI(std::shared_ptr< GameUI>& _ptr)
	{
		m_wpGameUI = _ptr;
	}

	//void SetCamera(const std::shared_ptr<CameraBase>& camera)
	//{
	//	m_wpCamera = camera;
	//}

	void OnHit()override;

private:
	//親(持ち主)の情報
	std::weak_ptr<KdGameObject> m_wpParent;

	std::weak_ptr<GameUI> m_wpGameUI;

	Math::Matrix				m_ParentTrans = Math::Matrix::Identity;

	Math::Vector3				 m_Localpos = Math::Vector3::Zero;

	Math::Matrix				 m_LocalMat = Math::Matrix::Identity;

	const Math::Matrix GetRotationMatrix()const
	{
		return Math::Matrix::CreateFromYawPitchRoll(
			DirectX::XMConvertToRadians(m_DegAng.y),
			DirectX::XMConvertToRadians(m_DegAng.x),
			DirectX::XMConvertToRadians(m_DegAng.z));
	}

	const Math::Matrix GetRotationYMatrix() const
	{
		return Math::Matrix::CreateRotationY(
			DirectX::XMConvertToRadians(m_DegAng.y));
	}

	void UpdateRotateByMouse();

	//void UpdateRotate(const Math::Vector3& srcMoveVec);

	Math::Vector3				m_pos = Math::Vector3::Zero;

	//武器情報
	std::weak_ptr<WeaponBase> m_wpWeapon;

	//回転用角度
	Math::Vector3 m_DegAng = Math::Vector3::Zero;

	//進行方向（ベクトルの向き）
	Math::Vector3 m_moveDir = Math::Vector3::Zero;



	//std::weak_ptr<CameraBase>			m_wpCamera;

	//Math::Vector3						m_worldRot;

	//移動速度(ベクトルの大きさ)
	const float m_moveSpeed = 0.3f;

	//プレイヤー座標修正
	const float m_adjustHeigh = 23.0f;

	//キーフラグ
	bool m_LeftKeyFlg = false;
	bool m_rightKeyFlg = false;

	// カメラ回転用マウス座標の差分
	POINT						m_FixMousePos = { 640,360 };

	int	 GunFireTime = 5;
	int	 FireTimeCnt = 0;
};