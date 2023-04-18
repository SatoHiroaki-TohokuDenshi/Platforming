#include "Player.h"
#include "Gauge.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1), pStage(nullptr), prevPosition_(0, 0, 0),
        nowHP_(150), maxHP_(180)
{
}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Player.fbx");
    assert(hModel_ >= 0);

    transform_.position_.x = 2;
    transform_.position_.z = 2;

    pStage = (Stage*)FindObject("Stage");
}

//�X�V
void Player::Update()
{
    prevPosition_ = transform_.position_;

    //�ړ�����
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

    //�ړ��ɔ�����]����
    XMVECTOR vLength = XMVector3Length(vMove);
    float length = XMVectorGetX(vLength);

    if (length != 0)
    {
        XMVECTOR vFront = { 0, 0, 1, 0 };               //������\���P�ʃx�N�g��
        vMove = XMVector3Normalize(vMove);              //�ړ������𐳋K��
        XMVECTOR vDot = XMVector3Dot(vFront, vMove);    //���ς��v�Z����
        float dot = XMVectorGetX(vDot);                 //�K�v�ȕ����������o��
        float angle = acos(dot);                        //���W�A������x���@�ɕϊ�����

        //���E�̂ǂ���������Ă��邩�𔻒f
        XMVECTOR vCross = XMVector3Cross(vFront, vMove);//�O�ς��v�Z����
        if (XMVectorGetY(vCross) < 0)                   //���ʂ�Y��0�����i���������Ă���j��������
        {
            angle *= -1;                                //���E�𔽓]����
        }

        transform_.rotate_.y = XMConvertToDegrees(angle);
    }

    //�ǂƂ̔���
    int checkX1, checkX2;
    int checkZ1, checkZ2;

    //�E�̔���
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
    //���̔���
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
    //��̔���
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
    //���̔���
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

//�`��
void Player::Draw()
{   
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Player::Release()
{
}