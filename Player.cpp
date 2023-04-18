#include "Player.h"
#include "Gauge.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"

//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1), pStage(nullptr), prevPosition_(0, 0, 0),
        nowHP_(150), maxHP_(180)
{
}

//デストラクタ
Player::~Player()
{
}

//初期化
void Player::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Player.fbx");
    assert(hModel_ >= 0);

    transform_.position_.x = 2;
    transform_.position_.z = 2;

    pStage = (Stage*)FindObject("Stage");
}

//更新
void Player::Update()
{
    prevPosition_ = transform_.position_;

    //移動処理
    XMFLOAT3 fMove = XMFLOAT3(0, 0, 0);

    if (Input::IsKey(DIK_LEFT))
    {
        fMove.x = -0.1f;
    }
    if (Input::IsKey(DIK_RIGHT))
    {
        fMove.x = 0.1f;
    }
    if (Input::IsKey(DIK_UP))
    {
        fMove.z = 0.1f;
    }
    if (Input::IsKey(DIK_DOWN))
    {
        fMove.z = -0.1f;
    }

    XMVECTOR vMove = XMLoadFloat3(&fMove);
    vMove = XMVector3Normalize(vMove);
    vMove *= 0.2f;
    XMStoreFloat3(&fMove, vMove);

    transform_.position_.x += fMove.x;
    transform_.position_.z += fMove.z;

    //移動に伴う回転処理
    XMVECTOR vLength = XMVector3Length(vMove);
    float length = XMVectorGetX(vLength);

    if (length != 0)
    {
        XMVECTOR vFront = { 0, 0, 1, 0 };               //向きを表す単位ベクトル
        vMove = XMVector3Normalize(vMove);              //移動方向を正規化
        XMVECTOR vDot = XMVector3Dot(vFront, vMove);    //内積を計算する
        float dot = XMVectorGetX(vDot);                 //必要な部分だけ取り出す
        float angle = acos(dot);                        //ラジアンから度数法に変換する

        //左右のどちらを向いているかを判断
        XMVECTOR vCross = XMVector3Cross(vFront, vMove);//外積を計算する
        if (XMVectorGetY(vCross) < 0)                   //結果のYが0未満（左を向いている）だったら
        {
            angle *= -1;                                //左右を反転する
        }

        transform_.rotate_.y = XMConvertToDegrees(angle);
    }

    //壁との判定
    int checkX1, checkX2;
    int checkZ1, checkZ2;

    //右の判定
    {
        checkX1 = (int)(transform_.position_.x + 0.3f);
        checkZ1 = (int)(transform_.position_.z + 0.05f);
        checkX2 = (int)(transform_.position_.x + 0.3f);
        checkZ2 = (int)(transform_.position_.z - 0.05f);
        if (pStage->IsWall(checkX1, checkZ1) ||
            pStage->IsWall(checkX2, checkZ2))
        {
            transform_.position_.x = (float)((int)transform_.position_.x) + 0.7f;
        }
    }
    //左の判定
    {
        checkX1 = (int)(transform_.position_.x - 0.3f);
        checkZ1 = (int)(transform_.position_.z + 0.05f);
        checkX2 = (int)(transform_.position_.x - 0.3f);
        checkZ2 = (int)(transform_.position_.z - 0.05f);
        if (pStage->IsWall(checkX1, checkZ1) ||
            pStage->IsWall(checkX2, checkZ2))
        {
            transform_.position_.x = (float)((int)transform_.position_.x) + 0.3f;
        }
    }
    //上の判定
    {
        checkX1 = (int)(transform_.position_.x - 0.05f);
        checkZ1 = (int)(transform_.position_.z + 0.3f);
        checkX2 = (int)(transform_.position_.x + 0.05f);
        checkZ2 = (int)(transform_.position_.z + 0.3f);
        if (pStage->IsWall(checkX1, checkZ1) ||
            pStage->IsWall(checkX2, checkZ2))
        {
            transform_.position_.z = (float)((int)transform_.position_.z) + 0.7f;
        }
    }
    //下の判定
    {
        checkX1 = (int)(transform_.position_.x + 0.05f);
        checkZ1 = (int)(transform_.position_.z - 0.3f);
        checkX2 = (int)(transform_.position_.x - 0.05f);
        checkZ2 = (int)(transform_.position_.z - 0.3f);
        if (pStage->IsWall(checkX1, checkZ1) ||
            pStage->IsWall(checkX2, checkZ2))
        {
            transform_.position_.z = (float)((int)transform_.position_.z) + 0.3f;
        }
    }

    if (Input::IsKeyDown(DIK_M))
    {
        nowHP_ += 30;
        if (nowHP_ > maxHP_)
        {
            nowHP_ = maxHP_;
        }
    }
    if (Input::IsKeyDown(DIK_N))
    {
        nowHP_ -= 30;
        if (nowHP_ < 0)
        {
            nowHP_ = 0;
        }
    }

    Gauge* pGauge = (Gauge*)FindObject("Gauge");
    pGauge->SetHP(nowHP_, maxHP_);
}

//描画
void Player::Draw()
{   
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Player::Release()
{
}