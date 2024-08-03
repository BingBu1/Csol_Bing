#pragma once
#include "DrawBase.h"
class ViewCheat : public DrawNode{
public:
	static auto& GetInstance() {
		static ViewCheat Inter;
		return Inter;
	}
	ViewCheat() = default;
	virtual void DrawMenu()override;
	virtual const DrawGuiIInfo& GetGuiInfo()const override;
};