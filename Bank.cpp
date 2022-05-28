#include "Bank.h"

//void Personal_Account::SetAll(std::string a1, std::string a2, std::string a3, int b)
//{
//	Name = a1;
//	Surname = a2;
//	Personal_Number = a3;
//	Number_of_code = b;
//}

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

Personal_Account::Personal_Account()
{
	Number_of_code = 0;
	Name = "";
	Surname = "";
	Personal_Number = "";
}

void Personal_Account::Save_personal_account()
{
	std::string Main_file_name, Map_file_name;
	Main_file_name = Name + "_" + Surname + "_" + "Main_save.txt";
	Map_file_name = Name + "_" + Surname + "_" + "Mape_save.txt";
	std::ofstream out(Main_file_name, std::ios::binary), out_map(Map_file_name, std::ios::binary);
	std::map <int, std::string> Consructor_code_new;
	std::map <std::string, Account_of_money*> Case_my_money_new;
	std::string code = Name + " " + Surname + " " + Personal_Number + " " + std::to_string(Number_of_code);
	//std::cout << code << std::endl;
	out << code;
	//out.write((char*)&code, sizeof(code));

	out.close();
	if (!Consructor_code.empty()) {
		for (int i = 0; i < Consructor_code.size(); i++) {
			code = Consructor_code[i] + std::to_string(Case_my_money[Consructor_code[i]]->view_money(true));
			//std::cout << code << std::endl;
			out_map << code << std::endl;
			//out_map.write((char*)&code, sizeof(code));
		}
	}
	else {
		out_map.close();
	}
}

void Personal_Account::Load_personal_account(std::string Nam, std::string Surnam)
{
	std::string Main_file_name, Map_file_name;
	Main_file_name = Nam + "_" + Surnam + "_" + "Main_save.txt";
	Map_file_name = Nam + "_" + Surnam + "_" + "Mape_save.txt";
	std::ifstream in(Main_file_name, std::ios::binary), in_map(Map_file_name, std::ios::binary);
	std::string temporary_str;
	in >> temporary_str;
	int k = 0;
	while (std::getline(in, temporary_str, ' ')) {
		if (k == 0) {
			Name += temporary_str;
			k += 1;
		}
		else if (k == 1) {
			Surname += temporary_str;
			k += 1;
		}
		else if (k == 2) {
			Personal_Number += temporary_str;
			k += 1;
		}
		else 
		Number_of_code = atoi(temporary_str.c_str());
	};
	in.close();
	temporary_str = "";
	if (in_map.is_open()) {
		k = 0;
		while (std::getline(in_map, temporary_str)) {
			std::string code = temporary_str.substr(0, 5), money = temporary_str.substr(5);
			this->Consructor_code[k] = code;
			if (code[0] == '0') {
				Current_account* nw = new Current_account;
				nw->Set_Account_number("@0-1-0@", code);
				nw->put_money(atof(money.c_str()));
				this->Case_my_money[code] = nw;
			}
			else if (code[0] == '1') {
				Deposit_account* nw = new Deposit_account;
				nw->Set_Account_number("@0-1-0@", code);
				nw->put_money(atof(money.c_str()));
				this->Case_my_money[code] = nw;
			}
			else if (code[0] == '2') {
				Credit_account* nw = new Credit_account;
				nw->Set_Account_number("@0-1-0@", code);
				nw->put_money(atof(money.c_str()));
				this->Case_my_money[code] = nw;
			}
			else {
				std::cout << "ERROR";
			}
			k += 1;
		}
		/*for (int i = 0; i < this->Number_of_code; i++) {
			in.read((char*)&temporary_str, sizeof(std::string));
			std::string code = temporary_str.substr(0, 5), money = temporary_str.substr(5);
			this->Consructor_code[i] = code;
			if (code[0] == '0') {
				Current_account* nw = new Current_account;
				nw->Set_Account_number("@0-1-0@", code);
				nw->put_money(atof(money.c_str()));
				this->Case_my_money[code] = nw;
			}
			else if (code[0] == '1') {
				Deposit_account* nw = new Deposit_account;
				nw->Set_Account_number("@0-1-0@", code);
				nw->put_money(atof(money.c_str()));
				this->Case_my_money[code] = nw;
			}
			else if (code[0] == '2') {
				Credit_account* nw = new Credit_account;
				nw->Set_Account_number("@0-1-0@", code);
				nw->put_money(atof(money.c_str()));
				this->Case_my_money[code] = nw;
			}
			else {
				std::cout << "ERROR";
			}
		}*/
	}
	else
		in.close();
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
	Case_my_money[number]->view_money(false);
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
	Consructor_code[Number_of_code] = nw->GetAccount_number(true);
	Number_of_code += 1;

}

void Personal_Account::Create_Deposit_account()
{
	Deposit_account* nw = new Deposit_account;
	Case_my_money[nw->GetAccount_number(true)] = nw;
	Consructor_code[Number_of_code] = nw->GetAccount_number(true);
	Number_of_code += 1;
}

void Personal_Account::Create_Credit_account()
{
	Credit_account* nw = new Credit_account;
	Case_my_money[nw->GetAccount_number(true)] = nw;
	Consructor_code[Number_of_code] = nw->GetAccount_number(true);
	Number_of_code += 1;
}

Personal_Account::~Personal_Account()
{
	for (int i = 0; i < Number_of_code; i++)
		delete Case_my_money[Consructor_code[i]];
	//std::cout << "Pers\n";
}

void Account_of_money::Set_Account_number(std::string a, std::string b)
{
	if (a == "@0-1-0@") {
		Account_number = b;
	}
}

//Конструктор денежного счёта
Account_of_money::Account_of_money()
{
	Amount_of_money_in_account = 0;
}

//Просмотреть количество денег на счету
double Account_of_money::view_money(bool flag)
{
	if (flag)
		return Amount_of_money_in_account;
	else {
		std::cout << Amount_of_money_in_account << std::endl;
		return 0;
	}
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

//Current_account::~Current_account()
//{
//	std::cout << "Curracc";
//}

//Current_account& Current_account::operator=(const Account_of_money* a)
//{
//	this->Account_number = a->;
//
//}

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

//Account_of_money::~Account_of_money()
//{
//	std::cout << "AccMoney\n";
//}

//Доделать*****************************
void Deposit_account::percentage()
{
	
}

//Конструктор депозитного счёта
Deposit_account::Deposit_account()
{
	char* buff = TakeTime();
	char new_buffer[8] = { '1', buff[8] , buff[9] ,/* buff[17] , buff[18] ,*/ buff[22] ,buff[23]};
	for (int i = 0; i < 5; i++)
		Account_number += new_buffer[i];
	std::cout << Account_number << std::endl;
	char new_new_buffer[] = { buff[8], buff[9], buff[5], buff[6], buff[20], buff[21], buff[22], buff[23]};
	//date_of_accrual = (int)new_new_buffer;
	delete buff;
}

//Взять деньги с депозитного счёта
void Deposit_account::take_money(double a)
{
	if (Amount_of_money_in_account >= a)
		Amount_of_money_in_account -= a;
	else
		std::cout << "Not enough money!\n";
}

//Deposit_account::~Deposit_account()
//{
//	std::cout << "Depos\n";
//}

//Доделать****************************
void Credit_account::percentage()
{
}

//Конструктор кредитного счёта
Credit_account::Credit_account()
{
	char* buff = TakeTime();
	char new_buffer[8] = { '2', buff[8] , buff[9] ,/* buff[17] , buff[18] ,*/ buff[22] ,buff[23]};
	for (int i = 0; i < 7; i++)
		Account_number += new_buffer[i];
	std::cout << Account_number << std::endl;
	date_of_accrual = 0;
	delete buff;
}

//Взять деньги с кредитного счёта
void Credit_account::take_money(double a)
{
	Amount_of_money_in_account -= a;
	char* buff = TakeTime();
	char new_new_buffer[] = { buff[8], buff[9], buff[5], buff[6], buff[20], buff[21], buff[22], buff[23] };
	if (Amount_of_money_in_account < 0)
		date_of_accrual = (int)new_new_buffer;
	delete buff;
}

//Credit_account::~Credit_account()
//{
//	std::cout << "Credacc\n";
//}

//Percentage_account::~Percentage_account()
//{
//	std::cout << "Peracc\n";
//}
