#pragma once
#include "DrawBase.h"
class VoxelUpdateCheat : public DrawNode {
public:
	static auto& GetInstance() {
		static VoxelUpdateCheat Inter;
		return Inter;
	}
	VoxelUpdateCheat() = default;
	virtual void DrawMenu()override;
	virtual const DrawGuiIInfo& GetGuiInfo()const override;
};