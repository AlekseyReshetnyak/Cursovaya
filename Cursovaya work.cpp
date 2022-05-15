#include "Bank.h"

int main()
{
	Personal_Account Mi{ "Any", "Ruf" };
	Mi.GetPersonal_Number();
	Mi.Create_Current_account();
	Mi.GetMoney_on_account("01522");
	Mi.PutMoney_on_account("01522", 20000);
	Mi.TakeMoney_on_account("01522", 10000);
	Mi.GetMoney_on_account("01522");
	char* buf = TakeTime();
	std::cout << buf;
}