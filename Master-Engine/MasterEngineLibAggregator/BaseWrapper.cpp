#include "stdafx.h"
#include "BaseWrapper.h"

BaseWrapper::BaseWrapper(void* pointer)
{
	orginal_pointer_ = pointer;
}

BaseWrapper::~BaseWrapper() = default;
