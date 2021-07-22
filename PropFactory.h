#pragma once
#include <queue>
#include <map>
#include "PropInfo.h"
class PropContainer;
class GameInfo;
class Prop;
class GameMap;
class ResourceManager;
class PlayerControler;

class PropFactory
{
private:
	typedef struct tagPropInfo {
		float buildTime;
		int size;
		int resource;
		int resourceAmount;
		string clipName;
		wstring propName;
	}PROPINFO;

	typedef struct tagQueuePropElement {
		int x;
		int y;
		int catagory;
		int propIdx;
		PROPDIR dir;
	}ELEMPROP;
private:
	bool _isFirstConveyor;
	int _buildPositionX;
	int _buildPositionY;
	Animator* _firstConveyorAnimator;
	float _buildTime;
	queue<ELEMPROP> _propQueue;
	vector<ImageObject> _previewV;
	vector<PROPINFO> _propInfoV[CATEGORY_NUM];
	GameInfo* _gameInfo;
	GameMap* _gameMap;
	ResourceManager* _resourceManager;
	PlayerControler* _playerControler;
public:
	PropFactory();
	~PropFactory();
	PropContainer* propContainer;
	void Init();
	void Update();
	void Render();
	void Release();

	bool isBuilding;		//짓는 중인지 여부
	bool isProduction;		//드릴인지 여부


	template<typename T>
	ImageObject* CreateProp(int tileX, int tileY);
	void CreateConveyor(int tileX, int tileY, PROPDIR dir);
	void CreateDrill(int tileX, int tileY);
	void ContainProp(int hashKey, Prop* newProp, PROPDIR dir);
	ImageObject* CreatePreview(int tileX, int tileY);
	void AddPropElem(vector<ImageObject>& previewV, int categoryIdx, int propIdx, PROPDIR dir);
	void InitPropInfo();
	void LinkGameInfo(GameInfo* gameInfo) { _gameInfo = gameInfo; }
	void LinkGameMap(GameMap* gameMap) { _gameMap = gameMap; }
	void LinkResourceManager(ResourceManager* resourceManager) { _resourceManager = resourceManager; }
	void LinkPlayerControler(PlayerControler* playerControler) { _playerControler = playerControler; }
	
	void SetBuildPositionX(int buildPositionX) { _buildPositionX = buildPositionX; }
	int GetBuildPositionX() { return _buildPositionX; }
	void SetBuildPositionY(int buildPositionY) { _buildPositionY = buildPositionY; }
	int GetBuildPositionY() { return _buildPositionY; }

};

