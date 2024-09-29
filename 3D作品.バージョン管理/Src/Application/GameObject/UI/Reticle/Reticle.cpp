#include "Reticle.h"

void Reticle::Init()
{
	m_tex = std::make_shared<KdTexture>();
	m_tex->Load("Asset/Textures/Object/UI/Reticle/Reticle.png");
}

void Reticle::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_tex, 0, 0);
}
