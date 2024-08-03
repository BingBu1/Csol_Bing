#pragma once
// All interfaces derive from this
class ImBaseInterface {
public:
	virtual ~ImBaseInterface() {}
};

#define InterFace "CreateInterface"

using CreateInterFace = ImBaseInterface * (*)(const char* pName, int* pReturnCode);
CreateInterFace FindCreateInterFace(char* ModleName);