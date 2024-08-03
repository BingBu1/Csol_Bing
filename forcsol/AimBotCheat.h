#pragma once
#include "DrawBase.h"
class AimBotCheat :public DrawNode {
public:
	static auto& GetInstance() {
		static AimBotCheat Inter;
		return Inter;
	}
	AimBotCheat() = default;
	virtual void DrawMenu()override;
	virtual const DrawGuiIInfo& GetGuiInfo()const override;
};