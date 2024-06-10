#pragma once
#include <memory>
#include "Tickable.h"
#include "Event.hpp"
#include "EventDispatcher.hpp"

class GravityEvent : public Event
{
public:
	GravityEvent() = default;

	std::string GetName() const override;
	void GetDispatcher(EventDispatcher* CurrentDispatcher);

	float Gravity;


};