#pragma once

#define TILESIZE 32						//Ÿ�� ���� ũ��

#define TILENUMX 100						//1�� Ÿ�� ����
#define TILENUMY 100						//1�� Ÿ�� ����

#define TILESIZEX TILESIZE * TILENUMX		//Ÿ�� ���� ���� ũ��
#define TILESIZEY TILESIZE * TILENUMY		//Ÿ�� ���� ���� ũ��

//Ÿ�ϼ� ����
#define TILESETX 4 //�ʿ信 ���� �ø��ô�
#define TILESETY 9 //���� �ø��ô�


//��Ʈ�ʵ�
#define ATTR_UNMOVE 0x00000001			//������ Ÿ��


//ȯ��
/*ȯ�� �̸�
��, ��, ����, ��, ��
*/
enum ENVIRONMENT
{
	ENV_WATER, ENV_DEEPWATER, ENV_SAND1, ENV_SAND2, ENV_SAND3, ENV_DARKSAND, 
	ENV_DIRT1, ENV_DIRT2, ENV_DIRT3, ENV_STONE1, ENV_STONE2, ENV_STONE3, 
	ENV_BASALT1, ENV_BASALT2, ENV_BASALT3, ENV_SNOW1, ENV_SNOW2, ENV_SNOW3,
	ENV_ICE1, ENV_ICE2, ENV_ICE3, ENV_ICE_WALL1, ENV_ICE_WALL2,
	ENV_NONE
};

//�ڿ�
/*�ڿ� �̸�
����, ��, ��ö
*/
enum RESOURCES
{
	RES_COPPER1, RES_COPPER2, RES_COPPER3,
	RES_LEAD1, RES_LEAD2, RES_LEAD3,
	RES_SCRAP1, RES_SCRAP2, RES_SCRAP3,
	RES_NONE
};

//Ÿ�� ���� ����ü
struct tagTile
{
	ENVIRONMENT		environment;
	RESOURCES		resources;
};

struct tagTileSet
{
	Rect rcTile;
	int TileX;
	int TileY;
};
