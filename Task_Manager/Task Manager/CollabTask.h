#pragma once
#include "Task.h"
#include "User.h"
#include "Optional.h"

class CollabTask: public Task
{
	Optional<User> asignee;

public:

	void asignUser(const User& user);
};

