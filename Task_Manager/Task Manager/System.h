#pragma once
#include "User.h"
#include "Collaboration.h"
#include "Vector.hpp"
#include "Command.h"
#include "CommandFactory.h"


class System
{
	MyVector<User> users;
	MyVector<Collaboration> collabs;

	bool systemRunning = true;
	int loggedIndex = -1;

	void getUsersFromDatabase();

	void commandMode();

	void saveToDataBase() const;

	bool isTakenUsername(const String& name) const;
public:
	System();

	void login(const String& name, unsigned pass);

	void register_user();

	void setTheRun(bool value);

	void addUser(const User& user);

	User& getActiveUser();

	~System();
};

