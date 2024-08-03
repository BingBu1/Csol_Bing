#pragma once
#include "DrawBase.h"
struct PlayerJoinNames{
	std::string Name;
	int Index;
};
class JoinClass : public DrawNode{
public:
	static auto& GetInstance() {
		static JoinClass Inter;
		return Inter;
	}
	JoinClass();
	virtual void DrawMenu()override;
	virtual const DrawGuiIInfo& GetGuiInfo()const override;
	void Init() noexcept;
	void ExecJoinClass(int Index) noexcept;
private:
	std::vector<PlayerJoinNames> Names;
};
