#include "Bank.h"

//Конструктор персонального аккаунта
Personal_Account::Personal_Account(std::string name, std::string surname)
{
	srand(__noop(time));
	Name = name;
	Surname = surname;
	for (int i = 0; i < (min(name.length(), surname.length()) > 2 ? 2 : min(name.length(), surname.length())); i++) {
		Personal_Number += std::to_string(int(char(name[i])) % 1000) + std::to_string(int(char(surname[i])) - rand() % 10);
	}
	if (Personal_Number.length() < 12)
		for (int i = Personal_Number.length(); i < 12; i++)
			Personal_Number += "0";
	Number_of_code = 0;
}

//Получение имени польователя аккаунта
void Personal_Account::GetName()
{
	std::cout << Name << std::endl;
}

//Получение фамилии пользователя аккаунта
void Personal_Account::GetSurname()
{
	std::cout << Surname << std::endl;
}

//Получение номера аккаунта
void Personal_Account::GetPersonal_Number()
{
	std::cout << Personal_Number << std::endl;
}

//Узнать сколько денег на счету с заданным номером
void Personal_Account::GetMoney_on_account(std::string number)
{
	Case_my_money[number]->view_money();
}

//Положить деньги на счёт с заданным номером
void Personal_Account::PutMoney_on_account(std::string number, double money)
{
	Case_my_money[number]->put_money(money);
}

//Взять деньги со счёта с заданным номером
void Personal_Account::TakeMoney_on_account(std::string number, double money)
{
	Case_my_money[number]->take_money(money);
}

//Создать текущий счёт
void Personal_Account::Create_Current_account()
{
	Current_account* nw = new Current_account;
	Case_my_money[nw->GetAccount_number(true)] = nw;
	Number_of_code += 1;
}

void Personal_Account::Create_Deposit_account()
{
	Deposit_account* nw = new Deposit_account;
	Case_my_money[nw->GetAccount_number(true)] = nw;
	Number_of_code += 1;
}

void Personal_Account::Create_Credit_account()
{
	Credit_account* nw = new Credit_account;
	Case_my_money[nw->GetAccount_number(true)] = nw;
	Number_of_code += 1;
}

Personal_Account::~Personal_Account()
{
	for (int i = 0; i < Number_of_code; i++)
		delete Case_my_money[Consructor_code[i]];
}

//Конструктор денежного счёта
Account_of_money::Account_of_money()
{
	Amount_of_money_in_account = 0;
}

//Просмотреть количество денег на счету
void Account_of_money::view_money()
{
	std::cout << Amount_of_money_in_account << std::endl;
}

//Положить деньги на счёт
void Account_of_money::put_money(double size)
{
	Amount_of_money_in_account += size;
}

//Конструктор текущего счёта
Current_account::Current_account()
{
	char* buff = TakeTime();
	char new_buffer[8] = {'0', buff[8] , buff[9] , /*buff[17] , buff[18] ,*/ buff[22] ,buff[23]};
	for (int i = 0; i < 5; i++)
		Account_number += new_buffer[i];
	std::cout << Account_number << std::endl;
	delete buff;
}

//Взять деньги со сщёта
void Current_account::take_money(double a)
{
	if (Amount_of_money_in_account >= a)
		Amount_of_money_in_account -= a;
	else
		std::cout << "Not enough money!\n";
}

//Получить номер счёта
std::string Account_of_money::GetAccount_number(bool flag)
{
	if (flag)
		return Account_number;
	else {
		std::cout << Account_number << std::endl;
		return "";
	}
}

void Deposit_account::percentage()
{
}

//Конструктор депозитного счёта
Deposit_account::Deposit_account()
{
	char* buff = TakeTime();
	char new_buffer[8] = { '1', buff[8] , buff[9] , buff[17] , buff[18] , buff[22] ,buff[23] };
	for (int i = 0; i < 7; i++)
		Account_number += new_buffer[i];
	std::cout << Account_number << std::endl;
	char new_new_buffer[] = { buff[8], buff[9], buff[5], buff[6], buff[20], buff[21], buff[22], buff[23]};
	date_of_accrual = (int)new_new_buffer;
	delete buff;
}

void Deposit_account::take_money(double a)
{
	if (Amount_of_money_in_account >= a)
		Amount_of_money_in_account -= a;
	else
		std::cout << "Not enough money!\n";
}

void Credit_account::percentage()
{
}

//Конструктор кредитного счёта
Credit_account::Credit_account()
{
	char* buff = TakeTime();
	char new_buffer[8] = { '2', buff[8] , buff[9] , buff[17] , buff[18] , buff[22] ,buff[23] };
	for (int i = 0; i < 7; i++)
		Account_number += new_buffer[i];
	std::cout << Account_number << std::endl;
	date_of_accrual = 0;
	delete buff;
}

void Credit_account::take_money(double a)
{
	Amount_of_money_in_account -= a;
	char* buff = TakeTime();
	char new_new_buffer[] = { buff[8], buff[9], buff[5], buff[6], buff[20], buff[21], buff[22], buff[23] };
	if (Amount_of_money_in_account < 0)
		date_of_accrual = (int)new_new_buffer;
	delete buff;
}
