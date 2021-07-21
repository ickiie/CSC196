#include "EventSystem.h"

void nc::EventSystem::Startup() {

}

void nc::EventSystem::Shutdown() {

}

void nc::EventSystem::Update(float dt) {

}

void nc::EventSystem::Subscribe(const std::string& name, function_t function) {

	Observer observer;
	observer.function = function;

	observers[name].push_back(observer);
}

void nc::EventSystem::Notify(const Event& event) {

	auto& eventObservers = observers[event.name];
	for (auto& observer : eventObservers) {

		observer.function(event);
	}
}
