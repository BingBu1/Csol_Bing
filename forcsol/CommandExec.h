#pragma once
#include "DrawBase.h"
class CommandExec : public DrawNode{
public:
	static auto& GetInstance() {
		static CommandExec Inter;
		return Inter;
	}
	CommandExec();
	void Update() noexcept;
	virtual void DrawMenu() override;
	virtual const DrawGuiIInfo& GetGuiInfo()const override;
private:
	bool m_Value;
};
class CommandBuyWeapon : public DrawNode {
public:
	static auto& GetInstance() {
		static CommandBuyWeapon Inter;
		return Inter;
	}
	CommandBuyWeapon();
	void Update() noexcept;
	virtual void DrawMenu() override;
	virtual const DrawGuiIInfo& GetGuiInfo()const override;
private:
	bool m_Value;
};
