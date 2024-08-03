#pragma once
#include "DrawBase.h"
class zs_BuyBug :public DrawNode {
public:
	static auto& GetInstance() {
		static zs_BuyBug Inter;
		return Inter;
	}
	zs_BuyBug() = default;
	virtual void DrawMenu()override;
	virtual const DrawGuiIInfo& GetGuiInfo()const override;
};