#include "Task.h"

unsigned Task::nextId = 1;

Task::Task(const String& _name, const String& due_date, const String& _description)
{
	setName(_name);
	setDescription(_description);

	if (due_date != "no") {
		date = DatePool::getInstance().getDate(due_date, _name);
	}

	s = Status::ON_HOLD;
	id = nextId;
	nextId++;
}

const String& Task::getName() const
{
	return name;
}

const String& Task::getDescription() const
{
	return description;
}

Status Task::getStatus() const
{
	return s;
}

unsigned Task::getId() const
{
	return id;
}

void Task::setStatus(Status _s)
{
	s = _s;
}

void Task::setName(String newName)
{
	name = newName;
}

void Task::setDescription(String newDescr)
{
	description = newDescr;
}

const Date& Task::getTaskDate() const
{
	if (date.hasValue()) return date.getValue();


}

bool Task::hasDate() const
{
	return date.hasValue();
}

void Task::clearDate()
{
	date.clear();
}

void Task::setDate(const Date* d)
{
	date.setValue(d);
}

Task::~Task()
{
	if (date.hasValue()) {
		DatePool::getInstance().removeDate(date.getValue(), name);
	}
}

std::ostream& operator<<(std::ostream& os, const Task& t)
{
	os << "Task name: " << t.name << std::endl;
	os << "Task id: " << t.id << std::endl;

	os << "Due date: ";
	if (t.date.hasValue()) os << t.date.getValue() << std::endl;
	else os << "No due date" << std::endl;

	os << "Task description: " << t.description << std::endl;

	os << "Status: ";
	switch (t.s) {
	case Status::ON_HOLD:
		os << "ON_HOLD" << std::endl;
		break;
	case Status::DONE:
		os << "DONE" << std::endl;
		break;
	case Status::IN_PROGRESS:
		os << "IN PROGRESS" << std::endl;
		break;
	case Status::OVERDUE:
		os << "OVERDUE" << std::endl;
		break;
	}

	return os;
}

bool operator==(const Task& left, const Task& right)
{
	return (left.getTaskDate() == right.getTaskDate() &&
		left.getName() == right.getName() && left.getDescription() == right.getDescription());
}
