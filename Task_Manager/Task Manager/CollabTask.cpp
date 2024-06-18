#include "CollabTask.h"

CollabTask::CollabTask(const String& _name, const String& due_date, const String& _description, const String& asignee): Task(_name,due_date,_description)
{
	this->asignee = asignee;
}


bool CollabTask::isCollabTask() const
{
	return true;
}

Task* CollabTask::clone() const
{
	return new CollabTask(*this);
}

void CollabTask::saveToDataBase(std::ofstream& ofs) const
{
	bool isCollab = 1;
	unsigned nameLen = name.getSize() + 1;
	unsigned descrLen = description.getSize() + 1;
	unsigned dateLen = userGivenDate.getSize() + 1;
	//unsigned asigneeLen = asignee.hasValue()?asignee.getValue().getName().getSize() + 1 : 0;
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

	/*ofs.write(reinterpret_cast<const char*>(&asigneeLen), sizeof(unsigned));
	if (asigneeLen != 0) {
		ofs.write(reinterpret_cast<const char*>(asignee.getValue().getName().c_str()), asigneeLen);
	}*/
}

void CollabTask::getFromDataBase(std::ifstream& ifs)
{
	unsigned nameLen, descrLen, dateLen, status, asigneeLen;
	char* tempName;
	char* tempDescr;
	char* tempDate;
	char* tempAsignee;

	ifs.read(reinterpret_cast<char*>(&nameLen), sizeof(unsigned));
	tempName = new char[nameLen];
	ifs.read(reinterpret_cast<char*>(tempName), nameLen);
	name = tempName;
	delete[] tempName;

	ifs.read(reinterpret_cast<char*>(&id), sizeof(unsigned));
	ifs.read(reinterpret_cast<char*>(&status), sizeof(unsigned));
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

	ifs.read(reinterpret_cast<char*>(&asigneeLen), sizeof(unsigned));
	if (asigneeLen == 0) return;
	tempAsignee = new char[asigneeLen];
	ifs.read(reinterpret_cast<char*>(tempAsignee), asigneeLen);
	//asignee.setValue(std::move(tempAsignee));
	delete[] tempAsignee;
}

void CollabTask::print() const
{
	std::cout << "Task name: " << name << std::endl;
	std::cout << "Task id: " << id << std::endl;

	std::cout << "Due date: ";
	if (date.hasValue()) std::cout << date.getValue() << std::endl;
	else std::cout << "No due date" << std::endl;

	std::cout << "Task description: " << description << std::endl;

	std::cout << "Status: ";
	switch (s) {
	case Status::ON_HOLD:
		std::cout << "ON_HOLD" << std::endl;
		break;
	case Status::DONE:
		std::cout << "DONE" << std::endl;
		break;
	case Status::IN_PROGRESS:
		std::cout << "IN PROGRESS" << std::endl;
		break;
	case Status::OVERDUE:
		std::cout << "OVERDUE" << std::endl;
		break;
	}

	std::cout << "Asignee: " << asignee << std::endl;
}
