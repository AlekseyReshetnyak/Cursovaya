#include "Bank.h"

int main()
{
	setlocale(LC_ALL, "rus");
	int a, b;
	std::cout << "1. Создать аккаунт\n2. Войти в аккаунт\n";
	if (std::cin.get() == '1') {
		system("cls");
		std::cout << "Напишите своё имя и фамилию\n----------------------------------------" << std::endl;
		std::string Name_Surname, Name, Surname;
		bool Bool_flag = true;
		while (getline(std::cin, Name_Surname, ' ') && Bool_flag) {
			if (Name.length() == 0)
				Name = Name_Surname;
			else if (Surname.length() == 0) {
				Surname = Name_Surname;
				Bool_flag = false;
			}
			else 
				Bool_flag = true;
		}
	}
	else if (std::cin.get() == '2') {

	}
	else;
	Personal_Account NotMi{};
	NotMi.Load_personal_account();
	NotMi.GetMoney_on_account("12722");
	NotMi.GetMoney_on_account("02722");
	/*Personal_Account Mi{ "Any", "Ruf" };
	Mi.GetPersonal_Number();
	Mi.Create_Current_account();
	Mi.Create_Deposit_account();
	Mi.GetMoney_on_account("12722");
	Mi.PutMoney_on_account("02722", 20000);
	Mi.PutMoney_on_account("12722", 300000);
	Mi.TakeMoney_on_account("02722", 10000);
	Mi.GetMoney_on_account("12722");
	Mi.GetMoney_on_account("02722");
	Mi.Save_personal_account();*/
}