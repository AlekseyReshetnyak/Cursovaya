#include "Bank.h"
#include "Interface.h"

int main()
{
	setlocale(LC_ALL, "rus");
	std::string Name_Surname, Name, Surname, stream = "00";
	std::cout << "1. Создать аккаунт\n2. Войти в аккаунт" << std::endl;
	Personal_Account Mi{};
	while (stream.length() > 1 && (stream[0] != '2' || stream[0] != '1')) {
		std::cin >> stream;
		std::cin.clear();
	}
	if (stream[0] == '1') {
		bool Bool_flag = true;
		while (Bool_flag) {
			system("cls");
			std::cout << "Напишите ваше имя и фамилию\n----------------------------------------" << std::endl;
			int k = 0;
			Name = "";
			Surname = "";
			getline(std::cin, Name_Surname);
			std::cin.clear();
			for (unsigned int i = 0; i < Name_Surname.length(); i++) {
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
		Personal_Account NotMi{ Name, Surname };
		Mi = NotMi;
	}
	else if (stream[0] == '2') {
		bool Bool_flag_second = true, Bool_flag_first = false;
		while (!Bool_flag_first) {
			Bool_flag_second = true;
			while (Bool_flag_second) {
				system("cls");
				std::cout << "Напишите ваше имя и фамилию\n----------------------------------------" << std::endl;
				int k = 0;
				Name = "";
				Surname = "";
				getline(std::cin, Name_Surname);
				std::cin.clear();
				for (unsigned int i = 0; i < Name_Surname.length(); i++) {
					if (k == 0 && Name_Surname[i] != ' ')
						Name += Name_Surname[i];
					else if (k == 1 && Name_Surname[i] != ' ') {
						Surname += Name_Surname[i];
						Bool_flag_second = false;
					}
					else if (Name_Surname[i] == ' ') {
						k += 1;
					}
					else
						Bool_flag_second = true;
				}
			}
			Bool_flag_first = Mi.Load_personal_account(Name, Surname);
			if (!Bool_flag_first)
				std::cout << "Данный пользователь не зарегистрирован.\n";
		}
	}
	else {
		std::cout << "Something wrong!";
		return -1;
	}
	stream = "00";

	system("cls");
	std::cout << "Добро пожаловать, " << Surname << " " << Name << "." << std::endl;
	Sleep(3000); //Задержка прораммы в миллисекундах

	bool while_flag = true;
	while (while_flag) {
		stream = "00";
		system("cls");
		std::cout << "Какую операцию требуется выполнить?\n1.Внести деньги\n2.Снять деньги\n3.Перевод на другую карту\n4.Открыть новый счет\n5.Информация о пользователе\n6.Выйти" << std::endl;
		while (stream.length() > 1 && (stream[0] != '5' || stream[0] != '4' || stream[0] != '3' || stream[0] != '2' || stream[0] != '1' || stream[0] != '6')) {
			std::cin >> stream;
			std::cin.clear();
		}
		switch (stream[0]) {
		case '1': {
			std::string numb;
			bool Flag = true;
			while (Flag) {
				system("cls");
				std::cout << "Введите номер счёта, на который желаете положить деньги: ";
				std::cin >> numb;
				std::cin.clear();
				Flag = Mi.Existence_of_an_account(numb);
			}
			system("cls");
			std::cout << "Какую сумму желаете внести: ";
			std::string operation_stream;
			Flag = true;
			while (Flag) {
				std::cin >> operation_stream;
				for (int i = 0; i < operation_stream.length(); i++)
					if ((int)operation_stream[i] < 0 && (int)operation_stream[i] > 9) {
						Flag = true;
						break;
					}
					else
						Flag = false;
				if (!Flag)
					Mi.PutMoney_on_account(numb, atof(operation_stream.c_str()));
			}
			std::cout << "Операция выполнена\n";
			Sleep(3000);
			break;
		}
		case '2': {
			std::string numb;
			bool Flag = true;
			while (Flag) {
				system("cls");
				std::cout << "Введите номер счёта, с которого желаете снять деньги: ";
				std::cin >> numb;
				std::cin.clear();
				Flag = Mi.Existence_of_an_account(numb);
			}
			system("cls");
			std::cout << "Какую сумму желаете снять: ";
			std::string operation_stream;
			Flag = true;
			while (Flag) {
				std::cin >> operation_stream;
				for (int i = 0; i < operation_stream.length(); i++)
					if ((int)operation_stream[i] < 0 && (int)operation_stream[i] > 9) {
						Flag = true;
						break;
					}
					else
						Flag = false;
				if (!Flag) {
					double mon = atof(operation_stream.c_str());
					if ((Mi.GetMoney_on_account(numb) - mon >= 0 && (numb[0] == '0' || numb[0] == '1')) || (numb[0] == '2'))
						Mi.TakeMoney_on_account(numb, mon);
				}
			}
			std::cout << "Операция выполнена\n";
			Sleep(3000);
			break;
		}
		case '3': {
			std::string numb1, numb2;
			bool Flag = true;
			while (Flag) {
				system("cls");
				std::cout << "Введите номер счёта, на который желаете перевести деньги: ";
				std::cin >> numb1;
				std::cin.clear();
				Flag = Mi.Existence_of_an_account(numb1);
			}
			Flag = true;
			while (Flag) {
				system("cls");
				std::cout << "Введите номер счёта, с которого желаете снять деньги: ";
				std::cin >> numb2;
				std::cin.clear();
				Flag = Mi.Existence_of_an_account(numb2);
			}
			system("cls");
			std::cout << "Какую сумму желаете перевести: ";
			std::string operation_stream;
			Flag = true;
			while (Flag) {
				std::cin >> operation_stream;
				for (int i = 0; i < operation_stream.length(); i++)
					if ((int)operation_stream[i] < 0 && (int)operation_stream[i] > 9) {
						Flag = true;
						break;
					}
					else
						Flag = false;
				if (!Flag) {
					double mon = atof(operation_stream.c_str());
					if ((Mi.GetMoney_on_account(numb2) - mon >= 0 && (numb2[0] == '0' || numb2[0] == '1')) || (numb2[0] == '2')) {
						Mi.PutMoney_on_account(numb1, mon);
						Mi.TakeMoney_on_account(numb2, mon);
					}
				}
			}
			std::cout << "Операция выполнена\n";
			Sleep(3000);
			break;
		}
		case '4': {
			system("cls");
			std::cout << "Какой счет вы желаете открыть:\n    1.Текущий счет\n    2.Дипозитный счет\n    3.Кредитный счет\n";
			std::string stream_stream = "00";
			while (stream_stream.length() > 1 && (stream_stream[0] != '1' || stream_stream[0] != '2' || stream_stream[0] != '3')) {
				std::cin >> stream_stream;
				std::cin.clear();
			}
			switch (stream_stream[0])
			{
			case '1': {
				Mi.Create_Current_account();
				break;
			}
			case '2': {
				Mi.Create_Deposit_account();
				break;
			}
			case '3': {
				Mi.Create_Credit_account();
				break;
			}
			default:
				std::cout << "ERROR case4";
				return -1;
			}
			std::cout << "Операция выполнена\n";
			Sleep(3000);
			break;
		}
		case '5': {
			system("cls");
			std::cout << "Имя: " << Mi.GetName() << "\nФамилия: " << Mi.GetSurname() << "\nНомер аккаунта: " << Mi.GetPersonal_Number() << std::endl;
			std::string* arr_string = Mi.GetNumbers_of_account_money();
			for (int i = 0; i < Mi.GetNumber_of_Code(); i++) {
				if (arr_string[i][0] == '0')
					std::cout << "    Текущий счёт:\n        Номер счёта: " << arr_string[i] << "\n        Денег на счету: " << Mi.GetMoney_on_account(arr_string[i]) << std::endl;
				if (arr_string[i][0] == '1')
					std::cout << "    Депозитный счёт:\n        Номер счёта: " << arr_string[i] << "\n        Денег на счету: " << Mi.GetMoney_on_account(arr_string[i]) << std::endl;
				if (arr_string[i][0] == '2')
					std::cout << "    Кредитный счёт:\n        Номер счёта: " << arr_string[i] << "\n        Денег на счету: " << abs(Mi.GetMoney_on_account(arr_string[i])) << std::endl;
			}
			std::cout << "Операция выполнена\n";
			system("pause");
			break;
		}
		case '6': {
			while_flag = false;
			break;
		}
		default: {
			std::cout << "ERROR switch";
			return -1;
		}
		}
	}

	Mi.Save_personal_account();
	system("cls");
	std::cout << "Досвидания\nУдачи\nХорошего дня\nПриятного времяпрепровождения\nПриятного аппетита\nЖелаю счастья\n" << std::endl;
	Sleep(6000);
}