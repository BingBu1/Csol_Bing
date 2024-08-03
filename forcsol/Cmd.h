#pragma once
typedef enum class cmd_source
{
	src_client,	// came in over a net connection as a clc_stringcmd  host_client will be valid during this state.
	src_command,	// from the command buffer
	src_server, // from svc_stufftext
} cmd_source_t;
void Cmd_ExecuteString(const char* String, cmd_source_t src = cmd_source_t::src_command);

using P_Execute = void (*)(const char* String, cmd_source_t src);

extern P_Execute ExecuteFun;