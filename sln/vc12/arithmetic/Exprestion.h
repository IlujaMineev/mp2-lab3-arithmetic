#include <cstdlib>
#include "stack.h"
#include <iostream>
#include <sstream>

using namespace std;

enum LexemType {LBRACKET, RBRACKET, OPERATOR, VALUE, VARIABLE, UNKNOWN};	

struct Var
{
	string name;
	double val;
public:
	Var(string n = "", double v = 0)
		{name = n; val = v;}
	~Var()
		{name = ""; val = 0;}
};

struct Lexem										//�������
{
	string str; 
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
	static const string symb;						//����������� �������
	static const string vari;						//����������
	static const string prior;						//���������
	string expr;										//���������
	Lexem* pLex;										//������ ������
	Var* var;
	int nVar;
	string hvar;
	int nLex;											//���������� ������
	void clrspace();									//�������� ��������
	void toPZ();										//������� � ��
	bool priority(Lexem in1, Lexem in2) const;//����������� ����������
public:
	Exprestion(const string i_expr);				//�����������
	Exprestion& operator=(const Exprestion& exp);
	~Exprestion()										//����������
	{ delete[] pLex; }
	void parse();										//������ �� �������
	void unmin();
								// ��������	//
	bool BracketsCheck() const;					//�������� �� ������������ ������
	bool OperatorCheck() const;					//�������� �� ������������ ����������
	bool SymbolsCheck() const;						//�������� �� ������������� �������
   bool GlobalCheck() const;						//�������� ������������ ���������
								// ���������� //
	double Calc();										//������� ����������

	static void SetVar(int p, double val)		//���������� �������� ����������
	{ /*var[p] = val; */}
	static double GetVar(int p)					//�������� �������� ����������
	{ /*return var[p]; */}

								// ������ //
	void printLex()
	{
		cout<<"pLex: \"";
		for (int i=0;i<nLex;i++)
			cout<<pLex[i].str<<" ";
		cout<<"\""<<endl;
	}
	string GetExpr()
	{
		return expr;	
	}
};
