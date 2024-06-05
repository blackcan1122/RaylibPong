#pragma once
#include "Event.hpp"

class CollisionEvent : public Event
{
public:
	CollisionEvent() = default;

	std::string GetName() const override;
	bool m_HasCollisionHappend;

};