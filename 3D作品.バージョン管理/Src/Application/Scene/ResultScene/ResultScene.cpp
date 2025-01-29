#include "ResultScene.h"
#include"../../GameObject/UI/ResultUI/ResultUI.h"
#include"../../Scene/SceneManager.h"
void ResultScene::Event()
{

}

void ResultScene::Init()
{
	//カーソルを非表示
	ShowCursor(false);

	std::shared_ptr<ResultUI>_ui = std::make_shared<ResultUI>();
	_ui->Init();
	AddObject(_ui);
}
