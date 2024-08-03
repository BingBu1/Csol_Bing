#pragma once
#include "DrawBase.h"
class GodAxeAuto : public DrawNode{
public:
	static auto& GetInstance() {
		static GodAxeAuto Inter;
		return Inter;
	}
	GodAxeAuto() = default;
	virtual void DrawMenu()override;
	virtual const DrawGuiIInfo& GetGuiInfo()const override;
};

