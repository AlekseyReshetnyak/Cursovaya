#pragma once

#include <iostream>
#include <string>
#include <map>
#include <ctime>

//Минимум из двух
template<class Type>
Type min(Type left, Type right) {
	if (left > right)
		return right;
	else
		return left;
}

//Максимум из двух
template<class Type>
Type max(Type left, Type right) {
	if (left > right)
		return left;
	else
		return right;
}

//Получение текущего локального времени
inline char* TakeTime() {
	char buffer[32], month[3];
	time_t seconds = time(NULL);
	tm timeinfo{};
	localtime_s(&timeinfo, &seconds);
	asctime_s(buffer, 32, &timeinfo);
	month[0] = buffer[4];
	month[1] = buffer[5];
	month[2] = buffer[6];
	std::string month_str = month;
	if (month_str == "Jan") {
		buffer[4] = '0';
		buffer[5] = '0';
		buffer[6] = '1';
	}
	if (month_str == "Feb") {
		buffer[4] = '0';
		buffer[5] = '0';
		buffer[6] = '2';
	}
	if (month_str == "Mar") {
		buffer[4] = '0';
		buffer[5] = '0';
		buffer[6] = '3';
	}
	if (month_str == "Apr") {
		buffer[4] = '0';
		buffer[5] = '0';
		buffer[6] = '4';
	}
	if (month_str == "May") {
		buffer[4] = '0';
		buffer[5] = '0';
		buffer[6] = '5';
	}
	if (month_str == "Jun") {
		buffer[4] = '0';
		buffer[5] = '0';
		buffer[6] = '6';
	}
	if (month_str == "Jul") {
		buffer[4] = '0';
		buffer[5] = '0';
		buffer[6] = '7';
	}
	if (month_str == "Aug") {
		buffer[4] = '0';
		buffer[5] = '0';
		buffer[6] = '8';
	}
	if (month_str == "Sep") {
		buffer[4] = '0';
		buffer[5] = '0';
		buffer[6] = '9';
	}
	if (month_str == "Oct") {
		buffer[4] = '0';
		buffer[5] = '1';
		buffer[6] = '0';
	}
	if (month_str == "Nov") {
		buffer[4] = '0';
		buffer[5] = '1';
		buffer[6] = '1';
	}
	if (month_str == "Dec") {
		buffer[4] = '0';
		buffer[5] = '1';
		buffer[6] = '2';
	}
	char* buf = new char[32];
	for (int i = 0; i < 32; i++)
		buf[i] = buffer[i];
	return buf;
};

class Account_of_money;
class Current_account;
class Percentage_account;
class Deposit_account;
class Credit_account;

//Класс "пользователь"
class Personal_Account {
private:
	std::string Name;
	std::string Surname;
	std::string Personal_Number = "";
	std::map <int, std::string> Consructor_code;
	int Number_of_code;
protected:
	std::map <std::string, Account_of_money*> Case_my_money;
public:
	Personal_Account(std::string, std::string);
	void GetName();
	void GetSurname();
	void GetPersonal_Number();
	void GetMoney_on_account(std::string);
	void PutMoney_on_account(std::string, double);
	void TakeMoney_on_account(std::string, double);
	void Create_Current_account();
	void Create_Deposit_account();
	void Create_Credit_account();
	~Personal_Account();
};

//Абстрактный базовый класс для всех счетов
class Account_of_money {
protected:
	double Amount_of_money_in_account;
	std::string Account_number;
public:
	Account_of_money();
	void view_money();
	void put_money(double);
	virtual void take_money(double) = 0;
	virtual void percentage() = 0;
	std::string GetAccount_number(bool);
};

//Класс "текущий счёт"
class Current_account : public Account_of_money {
private:
	void percentage() {};
public:
	Current_account();
	void take_money(double);
};

//Абстрактный класс для процентных счетов
class Percentage_account : public Account_of_money {
protected:
	int date_of_accrual;
public:
	virtual void percentage() = 0;
};

//Класс "депозитный счёт"
class Deposit_account : public Percentage_account {
public:
	void percentage();
	Deposit_account();
	void take_money(double);
};

//Класс "кредитный счёт"
class Credit_account : public Percentage_account {
public:
	void percentage();
	Credit_account();
	void take_money(double);
};