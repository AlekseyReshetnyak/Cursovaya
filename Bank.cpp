#include "Bank.h"


void Personal_Account::Fill_history(std::string text)
{
	if (History[7] != "") {
		std::string dop;
		for (int i = 0; i < 8; i++) {
			dop = History[i];
			History[i] = text;
			text = dop;
		}
	}
	else
		for (int i = 0; i < 8; i++)
			if (History[i] == "") {
				History[i] = text;
				break;
			}
}

void Personal_Account::Out_history()
{
	system("cls");
	if (History[0] == "")
		std::cout << "История пуста\n";
	else {
		for (int i = 0; i < 8; i++)
			if (History[i] != "")
				std::cout << History[i] << std::endl;
			else
				break;
	}
	
}

void Personal_Account::Perevod(std::string numb1, std::string numb2, double mon)
{
	std::string vr = "Перевод с" + numb1 + " на " + numb2 + ": " + std::to_string(mon);
	Fill_history(vr);
}

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
	for (int i = 0; i < 8; i++)
		History[i] = "";
}

Personal_Account::Personal_Account()
{
	Number_of_code = 0;
	Name = "";
	Surname = "";
	Personal_Number = "";
	for (int i = 0; i < 8; i++)
		History[i] = "";
}

bool Personal_Account::Existence_of_an_account(std::string numb)
{
	for (int i = 0; i < Number_of_code; i++)
		if (Consructor_code[i] == numb)
			return false;
	return true;
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
	out << code;

	out.close();
	if (!Consructor_code.empty()) {
		for (int i = 0; i < Consructor_code.size(); i++) {
			if (Consructor_code[i][0] == '0') {
				code = Consructor_code[i] + std::to_string(Case_my_money[Consructor_code[i]]->view_money(true));
				out_map << code << std::endl;
			}
			else if (Consructor_code[i][0] == '1') {
				code = Consructor_code[i] + std::to_string(Case_my_money[Consructor_code[i]]->GetDate_of_accrual()) + std::to_string(Case_my_money[Consructor_code[i]]->view_money(true));
				out_map << code << std::endl;
			}
			else {
				if (Case_my_money[Consructor_code[i]]->GetDate_of_accrual() != 0)
					code = Consructor_code[i] + std::to_string(Case_my_money[Consructor_code[i]]->GetDate_of_accrual()) + std::to_string(Case_my_money[Consructor_code[i]]->view_money(true));
				else
					code = Consructor_code[i] + "0000000000" + std::to_string(Case_my_money[Consructor_code[i]]->view_money(true));
				out_map << code << std::endl;
			}
		}
	}
	else {
		out_map.close();
	}
}

bool Personal_Account::Load_personal_account(std::string Nam, std::string Surnam)
{
	std::string Main_file_name, Map_file_name;
	Main_file_name = Nam + "_" + Surnam + "_" + "Main_save.txt";
	Map_file_name = Nam + "_" + Surnam + "_" + "Mape_save.txt";
	std::ifstream in(Main_file_name, std::ios::binary), in_map(Map_file_name, std::ios::binary);
	std::string temporary_str;
	if (in.is_open()) {
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
				std::string code = temporary_str.substr(0, 7);
				this->Consructor_code[k] = code;
				if (code[0] == '0') {
					std::string money = temporary_str.substr(7);
					Current_account* nw = new Current_account;
					nw->Set_Account_number("@0-1-0@", code);
					nw->put_money(atof(money.c_str()));
					this->Case_my_money[code] = nw;
				}
				else if (code[0] == '1') {
					std::string date = temporary_str.substr(7, 10), money = temporary_str.substr(17);
					Deposit_account* nw = new Deposit_account;
					nw->Set_Account_number("@0-1-0@", code);
					nw->put_money(atof(money.c_str()));
					nw->SetPrevious_date("@@02-11-20@@", atof(date.c_str()));
					this->Case_my_money[code] = nw;
				}
				else if (code[0] == '2') {
					std::string date = temporary_str.substr(7, 10), money = temporary_str.substr(17);
					Credit_account* nw = new Credit_account;
					nw->Set_Account_number("@0-1-0@", code);
					nw->put_money(atof(money.c_str()));
					nw->SetPrevious_date("@@02-11-20@@", atof(date.c_str()));
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
			in_map.close();
		return true;
	}
	else
		return false;
}

//Получение имени польователя аккаунта
std::string Personal_Account::GetName()
{
	return Name;
}

//Получение фамилии пользователя аккаунта
std::string Personal_Account::GetSurname()
{
	return Surname;
}

//Получение номера аккаунта
std::string Personal_Account::GetPersonal_Number()
{
	return Personal_Number;
}

int Personal_Account::GetNumber_of_Code()
{
	return Number_of_code;
}

//Узнать сколько денег на счету с заданным номером
double Personal_Account::GetMoney_on_account(std::string number)
{
	return Case_my_money[number]->view_money(true);
}

//Положить деньги на счёт с заданным номером
void Personal_Account::PutMoney_on_account(std::string number, double money)
{
	std::cout << money;
	Case_my_money[number]->put_money(money);
	std::string vr = "Пополнение на счет " + number + ": " + std::to_string(money);
	Fill_history(vr);
}

//Взять деньги со счёта с заданным номером
void Personal_Account::TakeMoney_on_account(std::string number, double money)
{
	Case_my_money[number]->take_money(money);
	std::string vr = "Снятие со счета " + number + ": " + std::to_string(money);
	Fill_history(vr);
}

//Создать счета
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

std::string* Personal_Account::GetNumbers_of_account_money()
{
	std::string* arr_string_number = new std::string[Number_of_code];
	for (int i = 0; i < Number_of_code; i++)
		arr_string_number[i] = Consructor_code[i];
	return arr_string_number;
}

Personal_Account& Personal_Account::operator=(Personal_Account& now)
{
	Name = now.Name;
	Surname = now.Surname;
	Personal_Number = now.Personal_Number;
	Number_of_code = now.Number_of_code;
	Consructor_code = now.Consructor_code;
	std::string code;
	for (int i = 0; i < Number_of_code; i++) {
		code = now.Consructor_code[i];
		if (code[0] == '0') {
			Current_account* nw = new Current_account;
			nw->Set_Account_number("@0-1-0@", code);
			nw->put_money(now.Case_my_money[now.Consructor_code[i]]->view_money(false));
			Case_my_money[code] = nw;
		}
		else if (code[0] == '1') {
			Deposit_account* nw = new Deposit_account;
			nw->Set_Account_number("@0-1-0@", code);
			nw->put_money(now.Case_my_money[now.Consructor_code[i]]->view_money(false));
			Case_my_money[code] = nw;
		}
		else if (code[0] == '2') {
			Credit_account* nw = new Credit_account;
			nw->Set_Account_number("@0-1-0@", code);
			nw->put_money(now.Case_my_money[now.Consructor_code[i]]->view_money(false));
			Case_my_money[code] = nw;
		}
	}
	return *this;
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

//Конструктор текущего счёта
Current_account::Current_account()
{
	char* buff = TakeTime();
	if (buff[8] == ' ')
		buff[8] = '0';
	char new_buffer[8] = {'0', buff[8] , buff[9] ,buff[17] , buff[18] , buff[22] ,buff[23]};
	for (int i = 0; i < 7; i++)
		Account_number += new_buffer[i];
	std::cout << Account_number << std::endl;
	delete buff;
}

//Взять деньги со счёта
void Current_account::take_money(double a)
{
	if (Amount_of_money_in_account >= a)
		Amount_of_money_in_account -= a;
	else
		std::cout << "Not enough money!\n";
}

void Current_account::put_money(double size)
{
	Amount_of_money_in_account += size;
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

//Account_of_money::~Account_of_money()
//{
//	std::cout << "AccMoney\n";
//}

void Deposit_account::SetPrevious_date(std::string code, int date)
{
	if (code == "@@02-11-20@@")
		date_of_accrual = date;
	percentage();
}

//Доделать*****************************
void Deposit_account::percentage()
{
	if (time(NULL) - date_of_accrual > 2592000) {
		Amount_of_money_in_account = Interest_calculation(Amount_of_money_in_account, 16, date_of_accrual);
		date_of_accrual += int((time(NULL) - date_of_accrual) / 2592000) * 2592000;
	}
}

//Конструктор депозитного счёта
Deposit_account::Deposit_account()
{
	char* buff = TakeTime();
	if (buff[8] == ' ')
		buff[8] = '0';
	char new_buffer[8] = { '1', buff[8] , buff[9] ,buff[17] , buff[18] , buff[22] ,buff[23]};
	for (int i = 0; i < 7; i++)
		Account_number += new_buffer[i];
	std::cout << Account_number << std::endl;
	date_of_accrual = time(NULL);
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

void Deposit_account::put_money(double size)
{
	Amount_of_money_in_account += size;
}

//Deposit_account::~Deposit_account()
//{
//	std::cout << "Depos\n";
//}

void Credit_account::SetPrevious_date(std::string code, int date)
{
	if (code == "@@02-11-20@@")
		date_of_accrual = date;
	percentage();
}

//Начисление процентов на кредитный счёт
void Credit_account::percentage()
{
	if (time(NULL) - date_of_accrual > 2592000) {
		Amount_of_money_in_account = Interest_calculation(Amount_of_money_in_account, 17, date_of_accrual);
		date_of_accrual += int((time(NULL) - date_of_accrual) / 2592000) * 2592000;
	}
}

//Конструктор кредитного счёта
Credit_account::Credit_account()
{
	char* buff = TakeTime();
	if (buff[8] == ' ')
		buff[8] = '0';
	char new_buffer[8] = { '2', buff[8] , buff[9] ,buff[17] , buff[18] , buff[22] ,buff[23]};
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
	if (Amount_of_money_in_account < 0 && date_of_accrual == 0)
		date_of_accrual = time(NULL);
}

void Credit_account::put_money(double size)
{
	if (Amount_of_money_in_account < 0 && Amount_of_money_in_account < size) {
		Amount_of_money_in_account += size;
		date_of_accrual = 0;
	}
	else
		Amount_of_money_in_account += size;
}

int Interest_calculation(int money, int percent, int previous_date)
{
	for (int i = 1; i <= int((time(NULL) - previous_date) / 2592000); i++)
		money += money * percent / 100 * 30 / 365;
	return money;
}

int Percentage_account::GetDate_of_accrual()
{
	return date_of_accrual;
}
