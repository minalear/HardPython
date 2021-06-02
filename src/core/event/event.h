#ifndef MINALEAR_EVENT_H
#define MINALEAR_EVENT_H

#include <functional>
#include <vector>
#include <memory>
#include "glm/glm.hpp"
#include "SDL2/SDL_scancode.h"

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

	struct TickEvent { };

	// KeyDown/KeyUp
	struct KeyboardEvent {
    SDL_Scancode scancode;
    bool repeat;
	};

	struct Event {
    EventType type;
    Event(EventType type) : type(type) { }

    union {
      TickEvent tick;
      KeyboardEvent key;
    };
	};

	using EventFn = std::function<void(const Event&)>;
	class EventDispatcher {
	private:
		std::vector<EventFn> observers;

	public:
		void Subscribe(const EventFn& callback);
		void Post(const Event& event) const;
	};

	extern EventDispatcher g_EventHandler;
}

#endif
