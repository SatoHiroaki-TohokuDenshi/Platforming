#pragma once
#include "Engine/GameObject.h"

enum
{
    TYPE_FLOOR,
    TYPE_WALL,
    TYPE_MAX,
};

//Stageを管理するクラス
class Stage : public GameObject
{
    int hModel_[TYPE_MAX];    //モデル番号
    int **table_;             //マップデータ
    int mapWidth_;            //マップの幅
    int mapHeight_;           //マップの高さ

public:
    //コンストラクタ
    Stage(GameObject* parent);

    //デストラクタ
    ~Stage();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    /// <summary> 指定座標が壁かどうかを調べる </summary>
    /// <param name="x_">x座標</param> <param name="z_">z座標</param>
    /// <returns>壁=true, 床=false</returns>
    bool IsWall(int x_, int z_);
};