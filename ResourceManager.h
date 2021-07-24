#pragma once
class Item;
class PropContainer;
class ResourceManager
{
private:
	vector<Item*> _resV;
public:
	ResourceManager();
	~ResourceManager();
	PropContainer* propContainer;

	void Init();
	void Update();
	void Render();

	void AddResource(Item* item);
	void AddResource(int resource, float x, float y);
	void RemoveResource(Item* item);

	vector<Item*> GetAllItem() { return _resV; }
};

