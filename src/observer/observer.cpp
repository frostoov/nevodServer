#include "observer.hpp"

Observer::Observer() {}

Subject::Subject() {}

Observer::~Observer() {}

Subject::~Subject() {}

void Subject::attach(const ObserverPtr obs) {
	observers_.push_back(obs);
}

void Subject::detach(const ObserverPtr obs) {
    observers_.remove(obs);
}

void Subject::notify() {
	for (auto& obs : observers_)
		obs->update(shared_from_this());
}

void Subject::notify(const ObserverPtr obs) {
	obs->update(shared_from_this());
}

bool Subject::isAttach(const ObserverPtr obs) {
	if (std::find(observers_.begin(), observers_.end(), obs) !=
		observers_.end())
		return true;
	else
		return false;
}
