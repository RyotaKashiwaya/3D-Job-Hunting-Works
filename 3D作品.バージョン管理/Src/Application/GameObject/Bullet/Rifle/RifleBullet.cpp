#include "RifleBullet.h"
#include"Src/Application/GameObject/Character/Character.h"
#include"Src/Application/GameObject/Enemy/EnemyManager.h"
#include"../../../Scene/SceneManager.h"
void RifleBullet::Update()
{	

	m_shotTime--;

	if (m_shotTime == 0)
	{
		m_isExpired = true;
	}

	m_pos += m_moveDir * m_moveSpeed;

	Math::Matrix _transMat;
	_transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = m_rotBulletMat * _transMat;


}

void RifleBullet::PostUpdate()
{

	//球判定用の変数を作成
	KdCollider::SphereInfo sphere;
	//球の中心点設定
	sphere.m_sphere.Center = m_pos;
	//球の半径を設定
	sphere.m_sphere.Radius = 1.0f;
	//当たり判定をしたいタイプを設定
	sphere.m_type = KdCollider::TypeGround;

	//球に当たったオブジェクトの情報を格納
	std::list < KdCollider::CollisionResult> retSphereList;

	//当たり判定！！
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		//自分だったら処理を飛ばす
		if (obj.get() == this) continue;
		obj->Intersects(sphere, &retSphereList);
	}

	//球に当たったリストから一番近いオブジェクトを抽出
	float maxOverLap = 0;	//はみでたレイの長さ
	Math::Vector3 hitDir;	//当たった方法
	bool isHit = false;		//当たっていたらtrue
	for (auto& ret : retSphereList)
	{
		//球にめり込んで、オーバーした長さが一番長いもの
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			hitDir = ret.m_hitDir;
			isHit = true;
		}
	}

	if (isHit)
	{
		m_isExpired = true;
	}


}

void RifleBullet::DrawBright()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
	
}

void RifleBullet::DrawLit()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
	

}

void RifleBullet::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Models/Object/Weapon/Rifle/Bullet.gltf");

		m_pCollider = std::make_unique<KdCollider>();
		m_pCollider->RegisterCollisionShape("Bullet", m_spModel, KdCollider::TypeDamage);
	}

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void RifleBullet::Shot(Math::Vector3 _mozlePos, Math::Vector3 _shotDir)
{
	m_pos = _mozlePos;
	m_moveDir = _shotDir;
	m_moveDir.Normalize();

	//レティクルへのベクトルと弾への信仰ベクトルから弾の向き(回転行列)を作成

	//①　ベクトルA ・・・弾の現在の進行ベクトル
	Math::Vector3 _vecA = m_mWorld.Backward();
	_vecA.Normalize();

	//②　ベクトルB ・・・照準への進行ベクトル
	Math::Vector3 _vecB = m_moveDir;
	_vecB.Normalize();

	//①と②のベクトルの内積値から角度を算出
	float _dot = _vecA.Dot(_vecB);				//内積値を算出
	float _angle = acos(_dot);					//内積で取得したcos値から2つのベクトルの角度を算出

	//①と②の外積を利用して、回転するためのベクトル(回転軸)を作成
	Math::Vector3 _rotAxis = _vecA.Cross(_vecB);

	//内積で算出した角度分、外積で算出したベクトル(回転軸)で回転する行列を作成
	//＝弾がレティクルの方向を向く


	m_rotBulletMat = Math::Matrix::CreateFromAxisAngle(_rotAxis, _angle);

}


void RifleBullet::OnHit()
{
	m_isExpired = true;
}


