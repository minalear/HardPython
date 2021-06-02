#include "event.h"

using namespace minalear;

void EventDispatcher::Subscribe(const EventFn& callback) {
	observers.push_back(callback);
}
void EventDispatcher::Post(const Event& event) const {
	for (const auto& observer : observers) {
		observer(event);
	}
}