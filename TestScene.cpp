#include "TestScene.h"
#include "Engine/Camera.h"
#include "Stage.h"
#include "Player.h"
#include "Gauge.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
	Camera::SetPosition(XMFLOAT3(6.5, 10, -7));
	Camera::SetTarget(XMFLOAT3(6.5, 2, 3));
	Instantiate<Stage>(this);
	Instantiate<Player>(this);
	Instantiate<Gauge>(this);
}

//�X�V
void TestScene::Update()
{
}

//�`��
void TestScene::Draw()
{
}

//�J��
void TestScene::Release()
{
}
