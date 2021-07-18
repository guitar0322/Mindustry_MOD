#pragma once
class AnimationClip;
class ID2D1Bitmap;
/*********************************************
* Framework ClipManager
* By ȫ�뿵
* UpDate 21-07-06
* Property : #
* Function : @
* #_clipMap : AnimationClip�� key�� ����� ��
* @AddClip
*(
	Ŭ�� key���ڿ�, 
	���ϰ��, 
	Ŭ�� ��ü ����, 
	Ŭ�� ����, 
	Ŭ�� ������ ����, 
	Ŭ�� ������ ����
*)
* @FindClip(AddClip���� ������ key���ڿ�)
* @CreateBitmapFromFile(���� ���)
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

