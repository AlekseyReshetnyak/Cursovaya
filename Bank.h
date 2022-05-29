#pragma once

#include <iostream>
#include <string>
#include <map>
#include <ctime>
#include <fstream>

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
	char buffer[32], month[3] = "";
	time_t seconds = time(NULL);
	tm timeinfo{};
	localtime_s(&timeinfo, &seconds);
	asctime_s(buffer, 32, &timeinfo);
	/*month[0] = buffer[4];
	month[1] = buffer[5];
	month[2] = buffer[6];*/
	std::string month_str;
	month_str += buffer[4];
	month_str += buffer[5];
	month_str += buffer[6];
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

//Возвращает день:месяц:год в типе int
//inline int Ret_date_of_accrual(char* buff)
//{
//	std::string str;
//	str += buff[8]; str += buff[9]; str += buff[5]; str += buff[6]; str += buff[20]; str += buff[21]; str += buff[22]; str += buff[23];
//	return atoi(str.c_str());
//}

int Interest_calculation(int, int, int);

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
	//void SetAll(std::string, std::string, std::string, int);
	std::map <std::string, Account_of_money*> Case_my_money;
public:
	Personal_Account(std::string, std::string);
	Personal_Account();
	void Save_personal_account();
	bool Load_personal_account(std::string, std::string);
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
	void Set_Account_number(std::string, std::string);
	Account_of_money();
	double view_money(bool);
	virtual void put_money(double) = 0;
	virtual void take_money(double) = 0;
	virtual void percentage() = 0;
	std::string GetAccount_number(bool);
	//~Account_of_money();
};

//Класс "текущий счёт"
class Current_account : public Account_of_money {
private:
	void percentage() {};
public:
	Current_account();
	void take_money(double);
	void put_money(double);
	//~Current_account();
	//Current_account& operator=(const Account_of_money*);
};

//Абстрактный класс для процентных счетов
class Percentage_account : public Account_of_money {
protected:
	int previous_date;
	int date_of_accrual;
public:
	virtual void percentage() = 0;
	//~Percentage_account();
};

//Класс "депозитный счёт"
class Deposit_account : public Percentage_account {
private:
	void percentage();
public:
	Deposit_account();
	void take_money(double);
	void put_money(double);
	//~Deposit_account();
};

//Класс "кредитный счёт"
class Credit_account : public Percentage_account {
private:
	void percentage();
public:
	//Credit_account(const Credit_account&);
	Credit_account();
	void take_money(double);
	void put_money(double);
	//~Credit_account();
};