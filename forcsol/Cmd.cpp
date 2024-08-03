#include "Cmd.h"
P_Execute ExecuteFun = nullptr;
void Cmd_ExecuteString(const char* text, cmd_source_t src) {
	ExecuteFun(text, src);
}