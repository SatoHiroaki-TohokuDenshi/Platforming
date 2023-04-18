#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class Gauge : public GameObject
{
    int hPictGauge_;    //HPバーの中身
    int hPictFrame_;    //HPバーの外枠

    int maxHP_;
    int nowHP_;
    int aniHP_;
public:
    //コンストラクタ
    Gauge(GameObject* parent);

    //デストラクタ
    ~Gauge();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void SetHP(int now, int max) {
        nowHP_ = now;
        maxHP_ = max;
        aniHP_ = (aniHP_ * 9 + nowHP_) / 10;
    };
};