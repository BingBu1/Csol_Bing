#pragma once
struct MapStruct{
	char Mem[0x6F4];
	char MapName[4];
};
class JoinLocal_{
public:
	void JoinLocal();
	void Init(MapStruct *Tmp) { Map = Tmp; }
	std::string GetMapName();
private:
	MapStruct *Map;
};
inline JoinLocal_ JoinLocal;