#pragma once
#include <string>
#include "GroupPanel.h"

struct DrawGuiIInfo {
	std::string Name;
	std::string FormMainSecl;
	bool IsGrop;
};

class DrawNode{
public:
	DrawNode(DrawNode const&) = delete;
	void operator=(DrawNode const&) = delete;
	virtual void DrawMenu() = 0;
	virtual const DrawGuiIInfo& GetGuiInfo() const = 0;
protected:
	DrawNode() {};
};

