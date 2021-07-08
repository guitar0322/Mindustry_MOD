#pragma once
#include "singletonBase.h"

class ZOrder;
class ZOrderManager : public singletonBase<ZOrderManager>
{
private:
	vector<ZOrder*> _zOrderV;
public:
	ZOrderManager();
	~ZOrderManager();

	HRESULT init();
	void release();
	void Update();
	void Render();

	void AddZOrder(ZOrder* newZOrder);
	void EraseZOrder(ZOrder* targetZOrder);
};

