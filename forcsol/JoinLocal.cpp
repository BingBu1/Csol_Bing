#include "main.h"
#include "JoinLocal.h"
#include <fmt/format.h>
void JoinLocal_::JoinLocal(){
	auto MapCommand = fmt::format("map {}", this->Map->MapName);
	g_pEngine->pfnClientCmd((char*)MapCommand.c_str());
}

std::string JoinLocal_::GetMapName(){
	return std::string(this->Map->MapName);
}
