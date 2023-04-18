#include "TestScene.h"
#include "Engine/Camera.h"
#include "Stage.h"
#include "Player.h"
#include "Gauge.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	Camera::SetPosition(XMFLOAT3(6.5, 10, -7));
	Camera::SetTarget(XMFLOAT3(6.5, 2, 3));
	Instantiate<Stage>(this);
	Instantiate<Player>(this);
	Instantiate<Gauge>(this);
}

//更新
void TestScene::Update()
{
}

//描画
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
}
