#pragma once
class TagManager : public singletonBase<TagManager>
{
private:
	map<string, int> tagMap;
	int lastIdx;
public:
	TagManager();
	~TagManager();
	
	HRESULT init();
	void release();
	void AddTag(string newTag) { tagMap.insert(make_pair(newTag, lastIdx++)); }
	int GetTag(string tag) { return tagMap.find(tag)->second; }
};

