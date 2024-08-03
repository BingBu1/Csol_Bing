#pragma once
#include "DrawBase.h"
class BasicCheat : public DrawNode {
public:
	static auto& GetInstance() {
		static BasicCheat Inter;
		return Inter;
	}
	BasicCheat();
	virtual void DrawMenu()override;
	virtual const DrawGuiIInfo& GetGuiInfo()const override;

	virtual void Update();
};