#include "TitleScene.h"
#include "../SceneManager.h"
#include"../../GameObject/UI/TitleUI/TitleUI.h"

void TitleScene::Init()
{


	std::shared_ptr<TitleUI> titleui = std::make_shared<TitleUI>();
	titleui->Init();
	AddObject(titleui);

}

void TitleScene::Event()
{
	
}