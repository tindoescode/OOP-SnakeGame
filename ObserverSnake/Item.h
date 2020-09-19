#pragma once
#include <string>
#include <memory>

#include "Object.h"

// Item on slot that snake can use to boost
class Item
{
	std::shared_ptr<Object> _object;
public:
	virtual void operate() { _object->operate(); }
};

