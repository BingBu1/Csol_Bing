#include <functional>
#include "DropRoom.h"

void DropRoom_::Drop() noexcept{
	DropFuns(_this, true, "Disconnect:", false, false);
}
