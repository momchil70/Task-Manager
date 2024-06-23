#pragma once
#include <fstream>
#include "Collaboration.h"
#include "Vector.hpp"
#include "Util.h"


class System
{
	MyVector<Collaboration> collabs;
	MyVector<User> users;

	bool systemRunning = true;
	int loggedIndex = -1;

	void loadData();
	void loadUsers();
	void loadUserTasks(std::ifstream& ifs);
	void loadCollabs();

	void saveToDataBase() const;
	void saveUsers() const;
	void saveUserTasks() const;
	void saveCollabs() const;

	unsigned findCollaboration(const String& name) const;

	unsigned findUser(const String& name) const;

	void saveCollabsToDatabase(std::ofstream& ofs) const;

	void getCollabsFromDatabase(std::ifstream& ifs);
	void getCollabTasks(unsigned collabIndex, std::ifstream& ifs);
	void getCollabParticipants(unsigned collabIndex, std::ifstream& ifs);
	User& getCreator(std::ifstream& ifs);
public:
	System();

	bool isTakenUsername(const String& name) const;

	void login(const String& name, unsigned pass);

	void register_user();

	void setTheRun(bool value);

	void addUser(const User& user);

	User& getActiveUser();

	unsigned getActiveIndex() const;

	void logout();

	unsigned findFreeId() const;

	Collaboration& getCollab(unsigned id);

	void listCollaborations() const;

	void createCollaboration(const String& name);

	void deleteCollaboration(const String& name);

	void listCollabTasks(const String& name) const;

	void addUser(const String& collaboration, const String& name);

	void asignTask(const String& collab, const String& user, const String& taskName, const String& due_date, const String& description);

	bool hasLoggedUser() const;

	bool isRunning() const;

	~System();
};

