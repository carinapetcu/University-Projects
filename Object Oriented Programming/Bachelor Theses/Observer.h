#pragma once
#include <vector>

class Observer
{
public:
	virtual void update() = 0;
	virtual ~Observer() {};
};

class Subject
{
private:
	std::vector<Observer*> observers;

public:
	void addObserver(Observer* observer) { observers.push_back(observer); };
	void deleteObserver(Observer* observer) {
		auto iterator = std::find(observers.begin(), observers.end(), observer);
		if (iterator != observers.end())
			observers.erase(iterator);
	}
	void notify() {
		for (auto observer : observers)
			observer->update();
	}
};
