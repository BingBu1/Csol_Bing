#pragma once
#include <unordered_map>
namespace Key {
	class KeyMap_{
	public:
		void Update(int Key, int Message, int wParam)noexcept;
		bool GetKeyStatus(int Key);
		bool GetMouseStatus(int Buttons);
	private:
		std::unordered_map<int, bool>Key_Map;
		std::unordered_map<int, bool>Mouse_Map;
	};

	void FastKey()noexcept;
	void CatchMouse();
	void KeyCallBack(UINT Message, WPARAM wParam, LPARAM lParam) noexcept;
	inline bool IsActiva = true;
	inline PULONG CsolMoney;
	inline KeyMap_ KeyMap;
}