#include "event.h"

using namespace minalear;

// Generic Event
Event::Event(EventType type) 
	: type(type) { }
const char* Event::ToString() const {
	return "<Generic Event>";
}

// Tick Event
TickEvent::TickEvent() : Event(EventType::Tick) { }
const char* TickEvent::ToString() const {
	return "<Tick Event>";
}

// Force Quit Event
ForceQuit::ForceQuit() : Event(EventType::ForceQuit) { }
const char* ForceQuit::ToString() const {
	return "<Force Quit Event>";
}

// Mouse Move Event
MouseMoveEvent::MouseMoveEvent(glm::vec2 pos) 
	: Event(EventType::MouseMove), pos(pos) { }
const char* MouseMoveEvent::ToString() const {
	return "<Mouse Move Event>";
}


void EventDispatcher::Subscribe(const EventFn& callback) {
	observers.push_back(callback);
}
void EventDispatcher::Post(const Event& event) const {
	for (const auto& observer : observers) {
		observer(event);
	}
}