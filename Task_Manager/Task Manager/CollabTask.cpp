#include "CollabTask.h"

CollabTask::CollabTask(const String& _name, const String& due_date, const String& _description, unsigned id, 
	const String& asignee, unsigned collabID) : Task(_name, due_date, _description, id)
{
	this->asignee = asignee;
	this->collaborationID = collabID;
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
	unsigned asigneeLen = asignee.getSize() + 1;

	Task::saveToDataBase(ofs);

	ofs.write(reinterpret_cast<const char*>(&asigneeLen), sizeof(unsigned));
	ofs.write(reinterpret_cast<const char*>(asignee.c_str()), asigneeLen);

	ofs.write(reinterpret_cast<const char*>(&collaborationID), sizeof(unsigned));
}

void CollabTask::getFromDataBase(std::ifstream& ifs)
{
	unsigned asigneeLen;
	char* tempAsignee;

	Task::getFromDataBase(ifs);

	ifs.read(reinterpret_cast<char*>(&asigneeLen), sizeof(unsigned));
	tempAsignee = new char[asigneeLen];
	ifs.read(reinterpret_cast<char*>(tempAsignee), asigneeLen);
	asignee = tempAsignee;
	delete[] tempAsignee;

	ifs.read(reinterpret_cast<char*>(&collaborationID), sizeof(unsigned));
}

void CollabTask::print() const
{
	Task::print();

	std::cout << "Asignee: " << asignee << std::endl;
}

const String& CollabTask::getAsignee() const
{
	return asignee;
}

unsigned CollabTask::getCollabId() const
{
	return collaborationID;
}
