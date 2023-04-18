#include "Gauge.h"
#include "Engine/Image.h"

//コンストラクタ
Gauge::Gauge(GameObject* parent)
    :GameObject(parent, "Gauge"), hPictGauge_(-1), hPictFrame_(-1),
        maxHP_(0), nowHP_(0), aniHP_(0)
{
}

//デストラクタ
Gauge::~Gauge()
{
}

//初期化
void Gauge::Initialize()
{
    //画像データのロード
    hPictGauge_ = Image::Load("LifeGauge.png");
    assert(hPictGauge_ >= 0);
    //画像データのロード
    hPictFrame_ = Image::Load("LifeGauge_Frame.png");
    assert(hPictFrame_ >= 0);

    transform_.position_.x = -0.95f;
    transform_.position_.y = 0.85f;
}

//更新
void Gauge::Update()
{
}

//描画
void Gauge::Draw()
{
    Transform transGauge = transform_;
    transGauge.scale_.x = (float)aniHP_ / (float)maxHP_;

    Transform transFrame = transform_;
    transFrame.scale_.x = 0.95f;

    Image::SetTransform(hPictGauge_, transGauge);
    Image::Draw(hPictGauge_);
    Image::SetTransform(hPictFrame_, transFrame);
    Image::Draw(hPictFrame_);
}

//開放
void Gauge::Release()
{
}