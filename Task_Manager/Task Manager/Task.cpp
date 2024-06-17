#include "Task.h"

unsigned Task::nextId = 1;

Task::Task(const String& _name, const String& due_date, const String& _description)
{
	userGivenDate = due_date;
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
	date = *d;
}

Task::~Task()
{
	if (date.hasValue()) {
		DatePool::getInstance().removeDate(date.getValue(), name);
	}
}

bool Task::isCollabTask() const
{
	return false;
}

Task* Task::clone() const
{
	return new Task(*this);
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


void Task::saveToDataBase(std::ofstream& ofs) const
{
	bool isCollab = 0;
	unsigned nameLen = name.getSize() + 1;
	unsigned descrLen = description.getSize() + 1;
	unsigned dateLen = userGivenDate.getSize() + 1;
	int statusToInt = (int)(s);

	ofs.write(reinterpret_cast<const char*>(&isCollab), sizeof(bool));

	ofs.write(reinterpret_cast<const char*>(&nameLen), sizeof(unsigned));
	ofs.write(reinterpret_cast<const char*>(name.c_str()), nameLen);

	ofs.write(reinterpret_cast<const char*>(&id), sizeof(unsigned));
	ofs.write(reinterpret_cast<const char*>(&statusToInt), sizeof(int));
	
	ofs.write(reinterpret_cast<const char*>(&descrLen), sizeof(unsigned));
	ofs.write(reinterpret_cast<const char*>(description.c_str()), descrLen);

	ofs.write(reinterpret_cast<const char*>(&dateLen), sizeof(unsigned));
	ofs.write(reinterpret_cast<const char*>(userGivenDate.c_str()), dateLen);
}

void Task::getFromDataBase(std::ifstream& ifs)
{
	unsigned nameLen = 0, descrLen = 0, dateLen = 0;
	int status = 0;
	char* tempName;
	char* tempDescr;
	char* tempDate;

	ifs.read(reinterpret_cast<char*>(&nameLen), sizeof(unsigned));
	tempName = new char[nameLen];
	ifs.read(reinterpret_cast<char*>(tempName), nameLen);
	name = tempName;
	delete[] tempName;

	ifs.read(reinterpret_cast<char*>(&id), sizeof(unsigned));
	ifs.read(reinterpret_cast<char*>(&status), sizeof(int));
	s = (Status)(status);

	ifs.read(reinterpret_cast<char*>(&descrLen), sizeof(unsigned));
	tempDescr = new char[descrLen];
	ifs.read(reinterpret_cast<char*>(tempDescr), descrLen);
	description = tempDescr;
	delete[] tempDescr;

	ifs.read(reinterpret_cast<char*>(&dateLen), sizeof(unsigned));
	tempDate = new char[dateLen];
	ifs.read(reinterpret_cast<char*>(tempDate), dateLen);
	userGivenDate = tempDate;
	date = DatePool::getInstance().getDate(userGivenDate, name);
	delete[] tempDate;
	
}
