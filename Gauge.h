#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Gauge : public GameObject
{
    int hPictGauge_;    //HP�o�[�̒��g
    int hPictFrame_;    //HP�o�[�̊O�g

    int maxHP_;
    int nowHP_;
    int aniHP_;
public:
    //�R���X�g���N�^
    Gauge(GameObject* parent);

    //�f�X�g���N�^
    ~Gauge();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void SetHP(int now, int max) {
        nowHP_ = now;
        maxHP_ = max;
        aniHP_ = (aniHP_ * 9 + nowHP_) / 10;
    };
};