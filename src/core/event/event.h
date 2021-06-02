#ifndef MINALEAR_EVENT_H
#define MINALEAR_EVENT_H

#include <functional>
#include <vector>
#include <string>
#include "glm/glm.hpp"

namespace minalear {
	enum class EventType {
		WindowResize,
		KeyDown,
		KeyUp,
		MouseMove,
		MouseButtonDown,
		MouseButtonUp,
		Tick,
		ForceQuit
	};

	class Event {
	public:
		EventType type;
		Event(EventType type);

		virtual const char* ToString() const = 0;
	};

	class TickEvent : public Event {
	public:
		TickEvent();
		const char* ToString() const override;
	};

	class ForceQuit : public Event {
	public:
		ForceQuit();
		const char* ToString() const override;
	};

	class MouseMoveEvent : public Event {
	public:
		glm::vec2 pos;
		MouseMoveEvent(glm::vec2 pos);
		const char* ToString() const override;
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
