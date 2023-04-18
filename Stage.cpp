#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/CsvReader.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hModel_{-1, -1},
    table_(nullptr), mapHeight_(0), mapWidth_(0)
{
    CsvReader csv;
    csv.Load("map.csv");

    mapHeight_ = csv.GetHeight();
    mapWidth_ = csv.GetWidth();

    table_ = new int* [mapWidth_];
    for (int x = 0; x < mapHeight_; x++)
    {
        table_[x] = new int[mapHeight_];
    }

    for (int x = 0; x < mapHeight_; x++)
    {
        for (int z = 0; z < mapWidth_; z++)
        {
            table_[x][(mapWidth_ - 1) - z] = csv.GetValue(x, z);
        }
    }
}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
    const char* fileName[] = {
        "Floor.fbx" ,
        "Wall.fbx" 
    };
    //���f���f�[�^�̃��[�h
    for (int i = 0; i < TYPE_MAX; i++)
    {
        hModel_[i] = Model::Load(fileName[i]);
        assert(hModel_[i] >= 0);
    }
}

//�X�V
void Stage::Update()
{
}

//�`��
void Stage::Draw()
{
    //Stage�I�u�W�F�N�g�����炳���ɁA�X�e�[�W��z�u���邽�߂̕ϐ�
    Transform blockTrans;
    //�\�����郂�f�����Ǘ�����ϐ�
    int type = 0;

    for (int x = 0; x < mapHeight_; x++)
    {
        for (int z = 0; z < mapWidth_; z++)
        {
            blockTrans.position_.x = x;
            blockTrans.position_.z = z;

            type = table_[x][z];

            Model::SetTransform(hModel_[type], blockTrans);
            Model::Draw(hModel_[type]);
        }
    }
}

//�J��
void Stage::Release()
{
    for (int x = 0; x < mapHeight_; x++)
    {
        delete[] table_[x];
    }
    delete[] table_;
}

bool Stage::IsWall(int x_, int z_)
{
    /*
    if (table_[x_][z_] == 1)
        return (true);
    return (false);
    */
    return(table_[x_][z_]);
}