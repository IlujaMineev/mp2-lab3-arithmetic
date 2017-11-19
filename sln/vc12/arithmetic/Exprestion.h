#include <cstdlib>
#include "stack.h"
#include <iostream>
#include <sstream>

using namespace std;

enum LexemType {LBRACKET, RBRACKET, OPERATOR, VALUE, VARIABLE, UNKNOWN};	

struct Lexem										//Лексема
{
	std::string str; 
	LexemType tp;
public:
	Lexem(string src = "", LexemType lt = UNKNOWN)
		{str = src; tp = lt;};
	~Lexem()
	{str = ""; tp = UNKNOWN;}
};

class Exprestion
{
private:
	static const string symb;						//Разрешённые символы
	static const string vari;						//Переменные
	static const string prior;						//Приоритет
	double* var;										//Переменные
	int nVar;											//Количество переменных
	string expr;										//Выражение
	Lexem* pLex;										//Массив лексем
	int nLex;											//Количество лексем
	void clrspace();									//Удаление пробелов
	void toPZ();										//Перевод в ПЗ
	bool priority(Lexem in1, Lexem in2) const;//Определение приоритета
public:
	Exprestion(const string i_expr);				//Конструктор
	Exprestion& operator=(const Exprestion& exp);
	~Exprestion()										//Деструктор
	{ delete[] pLex; }
	void parse();										//Разбор на лексемы
								// ПРОВЕРКИ	//
	bool BracketsCheck() const;					//Проверка на соответствие скобок
	bool OperatorCheck() const;					//Проверка на корректность операторов
	bool SymbolsCheck() const;						//Проверка на неразрешённые символы
   bool GlobalCheck() const;						//Проверка корректности выражения
								// ВЫЧИСЛЕНИЯ //
	double Calc();										//Подсчёт результата

	static void SetVar(int p, double val)		//Установить значение переменной
	{ /*var[p] = val; */}
	static double GetVar(int p)					//Получить значение переменной
	{ /*return var[p]; */}

								// ПОМОЩЬ //
	void printLex()
	{
		for (int i=0;i<nLex;i++)
			cout<<pLex[i].str<<" "<<pLex[i].tp<<endl;
		cout<<endl;
	}
};
