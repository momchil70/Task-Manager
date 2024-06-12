#pragma once
#include "User.h"
#include "Vector.hpp"


class System
{
	MyVector<User> users;
	User logged;

	void getUsersFromDatabase();

	void commandMode();

	void saveToDataBase() const;

public:
	System();

	void login();

	void register_user();

};

