#ifndef OBSERVER_H
#define OBSERVER_H

#include <list>
#include <algorithm>
#include <memory>


class Subject;
class Observer;

class Observer : public std::enable_shared_from_this<Observer> {
public:
	using SubjectPtr = std::shared_ptr<Subject>;

	virtual ~Observer();
	virtual void update(const SubjectPtr subject) = 0;

protected:
    Observer();
};

class Subject : public std::enable_shared_from_this<Subject> {
public:
	using ObserverPtr = std::shared_ptr<Observer>;

    virtual ~Subject();
	virtual void attach(const ObserverPtr obs);
	virtual void detach(const ObserverPtr obs);
    virtual void notify();
	virtual void notify(const ObserverPtr obs);
	virtual bool isAttach(const ObserverPtr obs);

protected:
    Subject();

private:
	std::list<ObserverPtr> observers_;
};

#endif  // OBSERVER_H
