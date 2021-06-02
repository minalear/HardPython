#ifndef MINALEAR_EVENT_H
#define MINALEAR_EVENT_H

#include <functional>
#include <vector>
#include "glm/glm.hpp"

namespace minalear {
	enum class EventType {
		WindowResize,
		KeyDown,
		KeyUp,
		MouseMove,
		MouseButtonDown,
		MouseButtonUp,
		Tick
	};

	class Event {
	public:
		EventType type;
		Event(EventType type) : type(type) { }
	};

	class WindowResizeEvent : public Event {
	public:
		int viewport_width, viewport_height;
		WindowResizeEvent(int width, int height)
			: Event(EventType::WindowResize), viewport_width(width), viewport_height(height) { }
	};

	class KeyDownEvent : public Event {
	public:

	};
	class KeyUpEvent : public Event {

	};

	

	class MouseMoveEvent : public Event {
	public:
		glm::vec2 pos;
		MouseMoveEvent(glm::vec2 pos) : Event(EventType::MouseMove), pos(pos) { }
	};
	class MouseButtonDownEvent : public Event {

	};
	class MouseButtonUpEvent : public Event {

	};

	class TickEvent : public Event {
	public:
		TickEvent() : Event(EventType::Tick) { }
	};


	using EventFn = std::function<void(const Event&)>;
	class EventDispatcher {
	private:
		std::vector<EventFn> observers;

	public:
		void Subscribe(const EventFn& callback);
		void Post(const Event& event) const;
	};
}

#endif
