#include "Gauge.h"
#include "Engine/Image.h"

//�R���X�g���N�^
Gauge::Gauge(GameObject* parent)
    :GameObject(parent, "Gauge"), hPictGauge_(-1), hPictFrame_(-1),
        maxHP_(0), nowHP_(0), aniHP_(0)
{
}

//�f�X�g���N�^
Gauge::~Gauge()
{
}

//������
void Gauge::Initialize()
{
    //�摜�f�[�^�̃��[�h
    hPictGauge_ = Image::Load("LifeGauge.png");
    assert(hPictGauge_ >= 0);
    //�摜�f�[�^�̃��[�h
    hPictFrame_ = Image::Load("LifeGauge_Frame.png");
    assert(hPictFrame_ >= 0);

    transform_.position_.x = -0.95f;
    transform_.position_.y = 0.85f;
}

//�X�V
void Gauge::Update()
{
}

//�`��
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

//�J��
void Gauge::Release()
{
}