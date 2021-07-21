#include "iuser.h"

int main()
{
	User& instance = User::GetUserInstance();
	instance.Run();
}