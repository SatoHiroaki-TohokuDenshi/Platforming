#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"

//Playerを管理するクラス
class Player : public GameObject
{
    int hModel_;    //モデル番号

    XMFLOAT3 prevPosition_;
    Stage* pStage;

    int nowHP_, maxHP_;

public:
    //コンストラクタ
    Player(GameObject* parent);

    //デストラクタ
    ~Player();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};