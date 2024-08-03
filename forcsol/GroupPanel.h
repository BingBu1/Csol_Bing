#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imconfig.h"
namespace ImGui {
	void BeginGroupPanel(const char* name, const ImVec2& size);
	void EndGroupPanel();
}
void HelpMarker(const char* desc) noexcept;