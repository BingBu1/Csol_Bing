#pragma once
#include "DrawBase.h"
class DevDebug : public DrawNode {
public:
	static auto& GetInstance() {
		static DevDebug Inter;
		return Inter;
	}
	DevDebug();
	virtual void DrawMenu()override;
	virtual const DrawGuiIInfo& GetGuiInfo()const override;
private:
	char InPutPassWorld[10];
	std::string PassWorld;
};