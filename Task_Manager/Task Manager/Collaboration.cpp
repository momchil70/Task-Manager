#include "Collaboration.h"

unsigned Collaboration::findTask(unsigned id) const
{
	for (int i = 0; i < capacity; i++) {
		if (tasks[i] != nullptr && tasks[i]->getId() == id) return i;
	}
	return -1;
}

void Collaboration::resize(int newCap)
{
	Task** temp = new Task * [newCap] {nullptr};
	for (int i = 0; i < capacity; i++) {
		temp[i] = tasks[i];
	}

	delete[] tasks;
	tasks = temp;
	capacity = newCap;
}

void Collaboration::free()
{
	if (tasks) {
		for (int i = 0; i < capacity; i++) {
			delete tasks[i];
			tasks[i] = nullptr;
		}
	}

	delete[] tasks;
}

void Collaboration::copyFrom(const Collaboration& other)
{
	tasks = new Task * [other.capacity];

	for (int i = 0; i < other.capacity; i++) {
		if (other.tasks[i])
			tasks[i] = other.tasks[i]->clone();
	}

	count = other.count;
	capacity = other.capacity;
	name = other.name;
	creator = other.creator;
	id = other.id;
	participants = other.participants;
}

void Collaboration::moveFrom(Collaboration&& other)
{
	name = other.name;
	creator = other.creator;
	id = other.id;
	tasks = other.tasks;
	other.tasks = nullptr;

	participants = std::move(other.participants);

	count = other.count;
	capacity = other.capacity;

	other.count = other.capacity = 0;
}

int Collaboration::findFreeIndex() const
{
	for (int i = 0; i < capacity; i++) {
		if (tasks[i] == nullptr) return i;
	}
	return -1;
}

Collaboration::Collaboration()
{
	tasks = new Task * [capacity] {nullptr};
}

Collaboration::Collaboration(const Collaboration& other)
{
	copyFrom(other);
}

Collaboration::Collaboration(Collaboration&& other)
{
	moveFrom(std::move(other));
}

Collaboration& Collaboration::operator=(const Collaboration& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Collaboration& Collaboration::operator=(Collaboration&& other)
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Collaboration::~Collaboration()
{
	free();
}

bool Collaboration::isUserIn(const User& u) const
{
	if (u == *creator) return true;
	int size = participants.size();
	for (int i = 0; i < size; i++) {
		if (u == *participants[i]) return true;
	}
	return false;
}

Collaboration::Collaboration(const User& creator, const String& name, unsigned _id)
{
	tasks = new Task * [capacity] {nullptr};
	this->creator = &creator;
	this->name = name;
	id = _id;
}

void Collaboration::listTasks() const
{
	for (int i = 0; i < capacity; i++) {
		if (tasks[i]) {
			std::cout << std::endl;
			tasks[i]->print();
			std::cout << std::endl;
		}
	}
}

void Collaboration::addUser(User& user)
{
	participants.push_back(&user);
}

void Collaboration::addTask(Task*& t)
{
	int firstFreeIndex = findFreeIndex();
	if (firstFreeIndex == -1) resize(capacity * 2);
	firstFreeIndex = findFreeIndex();

	
	tasks[firstFreeIndex] = t;
	count++;
}

const String& Collaboration::getName() const
{
	return name;
}

unsigned Collaboration::getId() const
{
	return id;
}

unsigned Collaboration::getTasksCapacity() const
{
	return capacity;
}

const Task* Collaboration::getTask(unsigned index) const
{
	return tasks[index];
}

Task* Collaboration::getTaskById(unsigned id)
{
	unsigned index = findTask(id);

	return tasks[index];
}


const User& Collaboration::getCreator() const
{
	return *creator;
}

void Collaboration::removeTask(unsigned id)
{
	unsigned index = findTask(id);

	if (index == -1) throw std::exception("No such task in this collaboration!");

	delete tasks[index];
	tasks[index] = nullptr;

	count--;
}

void Collaboration::saveToDatabase(std::ofstream& ofs) const
{
	unsigned nameLen = name.getSize() + 1;
	ofs.write(reinterpret_cast<const char*>(&nameLen), sizeof(unsigned));
	ofs.write(reinterpret_cast<const char*>(name.c_str()), nameLen);
	//saving id
	ofs.write(reinterpret_cast<const char*>(&id), sizeof(unsigned));
	//saving creator
	nameLen = creator->getName().getSize() + 1;
	ofs.write(reinterpret_cast<const char*>(&nameLen), sizeof(unsigned));
	ofs.write(reinterpret_cast<const char*>(creator->getName().c_str()), nameLen);
	//saving participants
	unsigned participantsCount = participants.size();
	ofs.write(reinterpret_cast<const char*>(&participantsCount), sizeof(unsigned));
	for (int i = 0; i < participantsCount; i++) {
		nameLen = participants[i]->getName().getSize() + 1;
		ofs.write(reinterpret_cast<const char*>(&nameLen), sizeof(unsigned));
		ofs.write(reinterpret_cast<const char*>(participants[i]->getName().c_str()), nameLen);
	}
	//saving tasks

	ofs.write(reinterpret_cast<const char*>(&count), sizeof(unsigned));
	for (int i = 0; i < count; i++) {
		if (tasks[i]) tasks[i]->saveToDataBase(ofs);
	}
}
