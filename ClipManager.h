#pragma once
#include "AnimationClip.h"
/*********************************************
* Framework ClipManager
* By 홍대영
* UpDate 21-07-06
* Property : #
* Function : @
* #_clipMap : AnimationClip과 key로 연결된 맵
* @AddClip
*(
	클립 key문자열, 
	파일경로, 
	클립 전체 넓이, 
	클립 높이, 
	클립 프레임 개수, 
	클립 프레임 간격
*)
* @FindClip(AddClip에서 저장한 key문자열)
* @CreateBitmapFromFile(파일 경로)
*********************************************/
class ClipManager : public singletonBase<ClipManager>
{
private:
	map<string, AnimationClip*> _clipMap;
	map<string, AnimationClip*>::iterator _clipMapIter;
	class IWICImagingFactory* mWicFactory;
public:
	ClipManager();
	~ClipManager();
	void Init();
	void Release();
	AnimationClip* AddClip(string clipName, string filePath, int width, int height, int frameNumX, int frameNumY, float frameTerm);
	AnimationClip* AddClip(string clipName, string filePath, int width, int height);
	AnimationClip* FindClip(string clipName);
	ID2D1Bitmap* CreateBitmapFromFile(wstring& filePath);
};

