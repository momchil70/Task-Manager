#pragma once
#include "User.h"
#include "Vector.hpp"


class System
{
	MyVector<User> users;

	int loggedIndex;

	void getUsersFromDatabase();

	void commandMode();

	void saveToDataBase() const;

public:
	System();

	void login();

	void register_user();

};

