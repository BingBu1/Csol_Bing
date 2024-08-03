#pragma once
#include<map>
#include<vector>
#include<string>
#include"DrawBase.h"
class CheatManagerBase{
public:
	CheatManagerBase();
	static auto& GetInstance() noexcept {
		static CheatManagerBase InterFace_;
		return InterFace_;
	}
	void Init();
	void PushNode(DrawNode* Node);
	void AddDrawNodes(std::vector<DrawNode*> Node);
	void AddDrawSecl(std::vector<std::string> Node);
	void Render()noexcept;
	void DrawChilnd(const std::string &Name, std::vector<DrawNode*>&NodeList)noexcept;
private:
	std::vector<std::string> SeclVector;
	std::map <std::string, std::map<std::string, std::vector<DrawNode*>>>m_DrawBaseMap;
	int CurrentIndex;
	std::string* Current;
	bool IsMove;
};
