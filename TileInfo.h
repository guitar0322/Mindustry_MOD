#pragma once

#define TILESIZE 32						//타일 조각 크기

#define TILENUMX 100						//1행 타일 개수
#define TILENUMY 100						//1열 타일 개수

#define TILESIZEX TILESIZE * TILENUMX		//타일 맵의 가로 크기
#define TILESIZEY TILESIZE * TILENUMY		//타일 맵의 세로 크기

//타일셋 정렬
#define TILESETX 4 //필요에 따라 늘립시다
#define TILESETY 8 //추후 늘립시다


//비트필드
#define ATTR_UNMOVE 0x00000001			//못가는 타일


//환경
/*환경 이름
모래, 물, 바위, 돌, 눈
*/
enum ENVIRONMENT
{
	ENV_WATER, ENV_DEEPWATER, ENV_SAND1, ENV_SAND2, ENV_SAND3, ENV_DARKSAND, 
	ENV_DIRT1, ENV_DIRT2, ENV_DIRT3, ENV_STONE1, ENV_STONE2, ENV_STONE3, 
	ENV_BASALT1, ENV_BASALT2, ENV_BASALT3, ENV_SNOW1, ENV_SNOW2, ENV_SNOW3,
	ENV_NONE
};

//자원
/*자원 이름
구리, 납, 고철
*/
enum RESOURCES
{
	RES_COPPER1, RES_COPPER2, RES_COPPER3,
	RES_LEAD1, RES_LEAD2, RES_LEAD3,
	RES_SCRAP1, RES_SCRAP2, RES_SCRAP3,
	RES_NONE
};

//오브젝트
/*오브젝트 이름
코어, 드릴, 포탑, 컨베이어(레일), 분배기, 에너미스팟, 월, 배터리
*/
enum OBJECT
{
	OBJ_CORE, OBJ_DRILL, OBJ_TURRECT, OBJ_CONVEYOR, 
	OBJ_DISTRIBUTOR, OBJ_ENEMYSPAWN, OBJ_WALL, OBJ_BATTERY, 
	OBJ_NONE
};

//포지션
enum POS
{
	POS_CORE
};

//타일 조각 구조체
struct tagTile
{
	ENVIRONMENT		environment;
	RESOURCES		resources;
	OBJECT			object;

};

struct tagTileSet
{
	Rect rcTile;
	int TileX;
	int TileY;
};
