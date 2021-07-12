#pragma once

#define TILESIZE 32						//Ÿ�� ���� ũ��

#define TILENUMX 100						//1�� Ÿ�� ����
#define TILENUMY 100						//1�� Ÿ�� ����

#define TILESIZEX TILESIZE * TILENUMX		//Ÿ�� ���� ���� ũ��
#define TILESIZEY TILESIZE * TILENUMY		//Ÿ�� ���� ���� ũ��

//Ÿ�ϼ� ����
#define TILESETX 4 //�ʿ信 ���� �ø��ô�
#define TILESETY 8 //���� �ø��ô�


//��Ʈ�ʵ�
#define ATTR_UNMOVE 0x00000001			//������ Ÿ��


//ȯ��
/*ȯ�� �̸�
��, ��, ����, ��, ��
*/
enum ENVIRONMENT
{
	ENV_SAND, ENV,WATER, ENV_ROCK, ENV_STONE, ENV_SNOW, ENV_END
};

//�ڿ�
/*�ڿ� �̸�
����, ��, ��ö
*/
enum RESOURCES
{
	RES_COPPER, RES_LEAD, RES_SCRAP, RES_NONE
};

//������Ʈ
/*������Ʈ �̸�
�ھ�, �帱, ��ž, �����̾�(����), �й��, ���ʹ̽���, ��, ���͸�
*/
enum OBJECT
{
	OBJ_CORE, OBJ_DRILL, OBJ_TURRECT, OBJ_CONVEYOR, 
	OBJ_DISTRIBUTOR, OBJ_ENEMYSPAWN, OBJ_WALL, OBJ_BATTERY, 
	OBJ_NONE
};

//������
enum POS
{
	POS_CORE
};

//Ÿ�� ���� ����ü
struct tagTile
{
	ENVIRONMENT		environment;
	RESOURCES		resources;
	OBJECT			object;
	Rect			rc;

};

struct tagTileSet
{
	Rect rcTile;
	int TileX;
	int TileY;
};

struct tagCurrentTile
{
	int x;
	int y;
};