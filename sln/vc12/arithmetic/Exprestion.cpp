#include "exprestion.h"

const string Exprestion::symb = "0123456789.+-*/()";				//Разрешённые символы
const string Exprestion::vari = "qwertyuiopasdfghjklzxcvbnm";  //Переменные
const string Exprestion::prior = "(_+-_*/";



void Exprestion::clrspace()												//Удаление пробелов
{
	int beg = 0;
	while (beg < expr.length())
	{
		if (expr[beg] == ' ')
			expr.erase(beg, 1);
		else beg++;
	}
}

void Exprestion::parse()													//Разбор на лексемы
{
	if (expr != "")
	{
		int tek = 0;
		int post = 0;
		int lexi = 0;
		while (tek < expr.length())
		{
			post = symb.find(expr[tek]);
			if (post == string::npos)
			{
				if ((vari.find(expr[tek]) >= 0) && (vari.find(expr[tek]) <= 25))
				{
					pLex[lexi].str = expr[tek]; 
					pLex[lexi].tp = VARIABLE;
					cout<<"The variable "<<pLex[lexi].str<<" have been seen in the exprestion"<<endl;
					if (hvar.find(pLex[lexi].str) == string::npos)
						hvar += pLex[lexi].str;
					lexi++;
					tek++;
				}
			}
			else
			if (post < 10)
			{
				pLex[lexi].tp = VALUE;
				while (((post <= 10) && (post != string::npos)) && (tek<expr.length()))
				{
					pLex[lexi].str += expr[tek];
					tek++;
					post = symb.find(expr[tek]);
				}
				lexi++;
			}
			else
				if (post <= 14)
				{
					pLex[lexi].str = expr[tek]; 
					pLex[lexi].tp = OPERATOR;
					lexi++;
					tek++;
				}
				else
					if (post == 15)
					{
						pLex[lexi].str = expr[tek]; 
						pLex[lexi].tp = LBRACKET;
						lexi++;
						tek++;
					}
					else
						if (post == 16)
						{
							pLex[lexi].str = expr[tek]; 
							pLex[lexi].tp = RBRACKET;
							lexi++;
							tek++;
						}
		}
		nLex = lexi;
		if ((nVar = hvar.length()) != 0)
		{
			cout<<"Please realise variables"<<endl;
			var = new Var[nVar];
			int* f = new int[hvar.length()];
			for (int i=0; i<hvar.length(); i++)
				f[i] = 0;
			for (int i=0;i<nLex;i++)
				if (pLex[i].tp == VARIABLE)
				{	
					if (f[hvar.find(pLex[i].str)] == 0)
					{
						var[hvar.find(pLex[i].str)].name = pLex[i].str;
						cout<<var[hvar.find(pLex[i].str)].name<<" = ";
						cin>>var[hvar.find(pLex[i].str)].val;
						cout<<endl;
						f[hvar.find(pLex[i].str)] = 1;
					}
				}
		}
	}
	else
		throw "the exprestion is empty";
}

Exprestion::Exprestion(const std::string i_expr)		//Конструктор
{
	expr = i_expr;
	clrspace();
	unmin();
	cout<<expr<<endl<<endl;;
	pLex = new Lexem[expr.length()];
	for (int i=0; i<expr.length(); i++)
		pLex[i].str = "";
	nLex = 0;
	nVar = 0;
}

Exprestion& Exprestion::operator=(const Exprestion& exp)
{
	expr = exp.expr;
	nLex = exp.nLex;
	delete[] pLex;
	pLex = new Lexem[nLex];
	for (int i = 0; i < nLex; i++)
		pLex[i] = exp.pLex[i];
	return *this;
}

void Exprestion::unmin()
{
	int k = 0;
	while (k < expr.length())
	{
		if (symb.find(expr[k]) == 12)
		{
			if (k == 0)
				expr.insert(k,"0");
			else
				if (symb.find(expr[k-1]) == 15)
					expr.insert(k,"0");
		}
		k++;
	}
}

bool Exprestion::BracketsCheck() const										//Проверка на соответствие скобок
{
	Stack<int> a(expr.length());
	int fict;
	int fl = 0;
	int pfl = 0;
	for (int i=0; i<expr.length(); i++)
		if (expr[i] == '(')
		{
			a.push(1);

			if (fl = 0)
				pfl = i;

			if ((i-1) >= 0)
				if ((symb.find(expr[i-1]) == string::npos) || ((symb.find(expr[i-1]) < 11)/* || (symb.find(expr[i-1]) > 14)*/))
				{
					cout<<"Denied symbol before '(' pos: "<<i<<endl;
					return false;
				}
		}
		else
			if (expr[i] == ')')
			{
				if (!a.empty())
					fict = a.pop();
				else
				{
					cout<<"RBracket earlier than LBracket pos: "<<i<<endl;
					return false;
				}
				
			if ((i+1) < expr.length())
				if ((symb.find(expr[i+1]) == string::npos) || ((symb.find(expr[i+1]) < 11)/* || (symb.find(expr[i+1]) > 14)*/))
				{
					cout<<"Denied symbol after ')' pos: "<<i<<endl;
					return false;
				}
			}
	if (a.empty())
		return true;
	else
		return false;
	cout<<"RBrackets lesser than LBrackets"<<" pos: "<<pfl<<endl;
}

bool Exprestion::OperatorCheck() const										//Проверка на корректность операторов
{
	if ((symb.find(expr[0]) >= 11) && (symb.find(expr[0]) <=14))
	{
		cout<<"The operator can't be in start"<<endl;
		return false;
	}
	if ((symb.find(expr[expr.length()-1]) >= 11) && (symb.find(expr[expr.length()-1]) <=14))
	{
		cout<<"The operator can't be in end"<<endl;
		return false;
	}
	for (int i=1; i<expr.length()-1; i++)
		if ((symb.find(expr[i]) >=11) && (symb.find(expr[i]) <=14))
		{
			if ((symb.find(expr[i-1]) > 9) && (symb.find(expr[i-1]) != 16) && (vari.find(expr[i-1]) == string::npos))
			{
				cout<<"uncorrect area for an operator (left) pos: "<<i<<endl;
				return false;
			}
			if ((symb.find(expr[i+1]) > 9) && (symb.find(expr[i+1]) != 15) && (vari.find(expr[i+1]) == string::npos))
			{
				cout<<"uncorrect area for an operator (right) pos: "<<i<<endl;
				return false;
			}
		}
	return true;
}

bool Exprestion::SymbolsCheck() const										//Проверка на неразрешённые символы и точки
{
	if ((symb.find(expr[0]) == string::npos) && (vari.find(expr[0]) == string::npos))
		{
			cout<<"denied symbol "<<expr[0]<<endl;
			return false;
		}
	if ((symb.find(expr[expr.length()-1]) == string::npos) && (vari.find(expr[expr.length()-1]) == string::npos))
		{
			cout<<"denied symbol "<<expr[expr.length()]<<endl;
			return false;
		}
	for (int i=1; i<expr.length()-1; i++)
	{
		if (symb.find(expr[i]) == string::npos)
		{
			if (vari.find(expr[i]) == string::npos)
			{
				cout<<"denied symbol "<<expr[i]<<" pos: "<<i<<endl;
				return false;
			}
		}
		else
			if (symb.find(expr[i]) == 10)
			{
				if (((symb.find(expr[i-1]) > 9) && (symb.find(expr[i-1]) < 17)) || (vari.find(expr[i-1]) != string::npos))
				{
					cout<<"uncorrect area for a point (left) pos: "<<i<<endl;
					return false;
				}
				if (((symb.find(expr[i+1]) > 9) && (symb.find(expr[i-1]) < 17)) || (vari.find(expr[i+1]) != string::npos))
				{
					cout<<"uncorrect area for a point (right) pos: "<<i<<endl;
					return false;
				}
			}
			else 
			{
				if (vari.find(expr[i]) != string::npos)
					if ((i-1 >= 0) && (i+1 < expr.length()) && (vari.find(expr[i-1]) != string::npos))
					{
						if ((symb.find(expr[i-1]) == string::npos) || ((symb.find(expr[i-1]) < 11) && (symb.find(expr[i-1]) > 14)))
						{
							cout<<"uncorrect area for a variable"<<endl;
							return false;
						}
						if ((symb.find(expr[i+1]) == string::npos) || ((symb.find(expr[i+1]) < 11) && (symb.find(expr[i+1]) > 14)))
						{
							cout<<"uncorrect area for a variable"<<endl;
							return false;
						}
					}
			}
	}
	return true;
}

bool Exprestion::GlobalCheck() const									//Проверка корректности выражения
{
	return (BracketsCheck() && OperatorCheck() && SymbolsCheck());
}

bool Exprestion::priority(Lexem in1, Lexem in2) const				//Определение приоритета in1>=in2
{
	int p1,p2;
	p1 = prior.find(in1.str);
	p2 = prior.find(in2.str);
	if (abs(p1 - p2) < 1)
		return true;
	else
		if((p1-p2) > 0)
			return true;
		else
			return false;
}


void Exprestion::toPZ() 									//Перевод в ПЗ
{
	string view;
	int tek = 0;
	int ires = 0;
	int per = 0;
	Lexem* res = new Lexem[nLex];
	Lexem x;
	Stack<Lexem> st;

	while (tek < nLex)
	{
		if ((pLex[tek].tp == VALUE) || (pLex[tek].tp == VARIABLE))
		{
			view += pLex[tek].str;
			res[ires++] = pLex[tek++];
		}
		else
			if (pLex[tek].tp == LBRACKET)
				st.push(pLex[tek++]);
			else
				if (pLex[tek].tp == RBRACKET)
				{
					x=st.pop();
					while (x.str != "(")
					{
						view += x.str;
						res[ires++] = x;
						x=st.pop();
					}
					tek++;
				}
				else
					if (pLex[tek].tp == OPERATOR)
					{
						if (st.empty())
							st.push(pLex[tek++]);
						else
						{
							x=st.peek();
							while ((!st.empty())&& (priority(x,pLex[tek])))
							{
								x=st.pop();
								view += x.str;
								res[ires++] = x;
								if (!st.empty())
									x=st.peek();
							}
							st.push(pLex[tek++]);
						}
					}
	}

	while (!st.empty())
	{
		x = st.pop();
		view += x.str;
		res[ires++] = x;
	}

	delete[] pLex;
	nLex = ires;
	pLex = new Lexem [nLex];
	for (int i=0; i<nLex; i++)
		pLex[i] = res[i];
}

double Exprestion::Calc()													//Подсчёт результата
{
	Stack<double> st;
	int k = 0;
	double lop = 0, 
			 rop = 0, 
			 nop = 0;

	toPZ();

	while (k < nLex)
	{
		if (pLex[k].tp == VARIABLE)
		{
			st.push(var[hvar.find(pLex[k].str)].val);
			k++;
		}	
		else
			if (pLex[k].tp == VALUE)
			{
				st.push(stod(pLex[k].str));
				k++;
			}
			else
				if ((pLex[k].tp == OPERATOR) && (!st.empty()))
				{
					rop = st.pop();
					if (!st.empty())
						lop = st.pop();
					else
						throw "WTF";
					if (pLex[k].str == "+")
						nop = lop + rop;
					else
						if (pLex[k].str == "-")
							nop = lop - rop;
						else
							if (pLex[k].str == "*")
								nop = lop * rop;
							else
								if (pLex[k].str == "/")
									nop = lop / rop;
					st.push(nop);
					k++;
				}
	}
	if (!st.empty())
		{
			nop = st.pop();
			if (st.empty())
				return nop;
			else
				throw "WTF 2";
		}
}