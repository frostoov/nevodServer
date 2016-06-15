#ifndef MASTER_HPP
#define MASTER_HPP

#include "../observer/observer.hpp"

class Master : public Observer, public Subject {
public:

	virtual~ Master();
};

#endif  // MASTER_HPP
