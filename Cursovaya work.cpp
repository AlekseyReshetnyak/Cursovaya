#include "Bank.h"
#include "Interface.h"

int main()
{
	setlocale(LC_ALL, "rus");
	std::string Name_Surname, Name, Surname, stream = "00";
	std::cout << "1. Создать аккаунт\n2. Войти в аккаунт" << std::endl;
	while (stream.length() > 1 && (stream[0] != '2' || stream[0] != '1')) {
		std::cin >> stream;
		std::cin.clear();
	}
	if (stream[0] == '1') {
		bool Bool_flag = true;
		while (Bool_flag) {
			system("cls");
			std::cout << "Напишите своё имя и фамилию\n----------------------------------------" << std::endl;
			int k = 0;
			Name = "";
			Surname = "";
			getline(std::cin, Name_Surname);
			std::cin.clear();
			for (int i = 0; i < Name_Surname.length(); i++) {
				if (k == 0 && Name_Surname[i] != ' ')
					Name += Name_Surname[i];
				else if (k == 1 && Name_Surname[i] != ' ') {
					Surname += Name_Surname[i];
					Bool_flag = false;
				}
				else if (Name_Surname[i] == ' ') {
					k += 1;
				}
				else
					Bool_flag = true;
			}
		}
		Personal_Account Mi{ Name, Surname };
	}
	else if (stream[0] == '2') {
		bool Bool_flag = true;
		while (Bool_flag) {
			system("cls");
			std::cout << "Напишите своё имя и фамилию\n----------------------------------------" << std::endl;
			int k = 0;
			Name = "";
			Surname = "";
			getline(std::cin, Name_Surname);
			std::cin.clear();
			for (int i = 0; i < Name_Surname.length(); i++) {
				if (k == 0 && Name_Surname[i] != ' ')
					Name += Name_Surname[i];
				else if (k == 1 && Name_Surname[i] != ' ') {
					Surname += Name_Surname[i];
					Bool_flag = false;
				}
				else if (Name_Surname[i] == ' ') {
					k += 1;
				}
				else
					Bool_flag = true;
			}
		}
		Personal_Account Mi{};
		Mi.Load_personal_account( Name, Surname );
	}

	system("cls");
	std::cout << "Добро пожаловать " << Surname << " " << Name << "." << std::endl;
	Sleep(3000); //Задержка прораммы в миллисекундах

	system("cls");
	std::cout << "Какую операцию требуется выполнить?\n1.Внести деньги\n2.Снять деньги\n3.Перевод на другую карту\n4.Мои счета\n5.Информация о пользователе" << std::endl;
	//std::cout << Name << " " << Surname << " ";
	/*Personal_Account NotMi{};
	NotMi.Load_personal_account("Any", "Ruf");
	NotMi.GetMoney_on_account("12822");
	NotMi.GetMoney_on_account("02822");*/
	/*Personal_Account Mi{ "Any", "Ruf" };
	Mi.GetPersonal_Number();
	Mi.Create_Current_account();
	Mi.Create_Deposit_account();
	Mi.GetMoney_on_account("12822");
	Mi.PutMoney_on_account("02822", 20000);
	Mi.PutMoney_on_account("12822", 300000);
	Mi.TakeMoney_on_account("02822", 10000);
	Mi.GetMoney_on_account("12822");
	Mi.GetMoney_on_account("02822");
	Mi.Save_personal_account();*/
}