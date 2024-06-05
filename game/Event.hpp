#pragma once
#include <string>

class Event
{
protected:
	virtual ~Event() = default;
public:
	virtual std::string GetName() const = 0;
};