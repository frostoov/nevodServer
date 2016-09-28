#ifndef MASTER_HPP
#define MASTER_HPP

#include "../observer/observer.hpp"

class Master : public Observer, public Subject {
public:

    virtual void writeResetRegister() = 0;

	virtual~ Master();
};

#endif  // MASTER_HPP
