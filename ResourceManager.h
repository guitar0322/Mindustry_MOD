#pragma once
class Item;
class PropContainer;
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
	PropContainer* propContainer;

	void Init();
	void Update();
	void Render();
	vector<Item*> _resV;

	void AddResource(Item* item);
	void RemoveResource(Item* item);
};

