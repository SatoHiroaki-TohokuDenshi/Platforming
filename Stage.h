#pragma once
#include "Engine/GameObject.h"

enum
{
    TYPE_FLOOR,
    TYPE_WALL,
    TYPE_MAX,
};

//Stage���Ǘ�����N���X
class Stage : public GameObject
{
    int hModel_[TYPE_MAX];    //���f���ԍ�
    int **table_;             //�}�b�v�f�[�^
    int mapWidth_;            //�}�b�v�̕�
    int mapHeight_;           //�}�b�v�̍���

public:
    //�R���X�g���N�^
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    /// <summary> �w����W���ǂ��ǂ����𒲂ׂ� </summary>
    /// <param name="x_">x���W</param> <param name="z_">z���W</param>
    /// <returns>��=true, ��=false</returns>
    bool IsWall(int x_, int z_);
};