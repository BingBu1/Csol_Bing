#pragma once
#include "DrawBase.h"
class LockModeCheat : public DrawNode {
public:
	static auto& GetInstance() {
		static LockModeCheat Inter;
		return Inter;
	}
	LockModeCheat();
	virtual void DrawMenu()override;
	virtual const DrawGuiIInfo& GetGuiInfo()const override;
	void Update()noexcept;
};