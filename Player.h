#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"

//Player���Ǘ�����N���X
class Player : public GameObject
{
    int hModel_;    //���f���ԍ�

    XMFLOAT3 prevPosition_;
    Stage* pStage;

    int nowHP_, maxHP_;

public:
    //�R���X�g���N�^
    Player(GameObject* parent);

    //�f�X�g���N�^
    ~Player();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};