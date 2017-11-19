#include <cstdlib>
#include "stack.h"
#include <iostream>
#include <sstream>

using namespace std;

enum LexemType {LBRACKET, RBRACKET, OPERATOR, VALUE, VARIABLE, UNKNOWN};	

struct Lexem										//�������
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
	static const string symb;						//����������� �������
	static const string vari;						//����������
	static const string prior;						//���������
	double* var;										//����������
	int nVar;											//���������� ����������
	string expr;										//���������
	Lexem* pLex;										//������ ������
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
		for (int i=0;i<nLex;i++)
			cout<<pLex[i].str<<" "<<pLex[i].tp<<endl;
		cout<<endl;
	}
};
