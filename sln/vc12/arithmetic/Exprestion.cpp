#include "exprestion.h"

const string Exprestion::symb = "0123456789.+-*/()";				//����������� �������
const string Exprestion::vari = "qwertyuiopasdfghjklzxcvbnm";  //����������
const string Exprestion::prior = "(_+-_*/";



void Exprestion::clrspace()												//�������� ��������
{
	int beg = 0;
	while (beg < expr.length())
	{
		if (expr[beg] == ' ')
			expr.erase(beg, 1);
		else beg++;
	}
}

void Exprestion::parse()													//������ �� �������
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
					nVar++;
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
		/*if (nVar != 0)
		{
			cout<<"Please realise variables"<<endl;
			var = new double[nVar];
			int j=0;
			for (int i=0;i<nLex;i++)
				if (pLex[i].tp == VARIABLE)
				{
					cout<<pLex[i].str<<" = ";
					cin>>var[j];
					j++;
					cout<<endl;
				}
		}*/
	}
	else
		throw "the exprestion is empty";
}

Exprestion::Exprestion(const std::string i_expr)		//�����������
{
	expr = i_expr;
	clrspace();
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

bool Exprestion::BracketsCheck() const										//�������� �� ������������ ������
{
	Stack<int> a(expr.length());
	int fict;
	for (int i=0; i<expr.length(); i++)
		if (expr[i] == '(')
		{
			a.push(1);

			if ((i-1) >= 0)
				if ((symb.find(expr[i-1]) == string::npos) || ((symb.find(expr[i-1]) < 11) || (symb.find(expr[i-1]) > 14)))
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
				if ((symb.find(expr[i+1]) == string::npos) || ((symb.find(expr[i+1]) < 11) || (symb.find(expr[i+1]) > 14)))
				{
					cout<<"Denied symbol after ')' pos: "<<i<<endl;
					return false;
				}
			}
	if (a.empty())
		return true;
	else
		return false;
	cout<<"RBrackets lesser than LBrackets"<<endl;
}

bool Exprestion::OperatorCheck() const										//�������� �� ������������ ����������
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

bool Exprestion::SymbolsCheck() const										//�������� �� ������������� ������� � �����
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

bool Exprestion::GlobalCheck() const									//�������� ������������ ���������
{
	return (BracketsCheck() && OperatorCheck() && SymbolsCheck());
}

bool Exprestion::priority(Lexem in1, Lexem in2) const				//����������� ���������� in1>=in2
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


void Exprestion::toPZ() 									//������� � ��
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
		if (pLex[tek].tp == VALUE)
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
					else
						if (pLex[tek].tp == VARIABLE)
						{
							double vr;
							cout<<"Please set the value of variable "<<pLex[tek].str<<" = ";
							cin>>vr;
							cout<<endl;
							pLex[tek].tp = VALUE;
							std::ostringstream h;
							h << vr;
							pLex[tek].str = h.str();
							view += pLex[tek].str;
							res[ires++] = pLex[tek++];
						}
	}

	while (!st.empty());
	{
		x = st.pop();
		res[ires++] = x;
	}

	delete[] pLex;
	nLex = ires;
	pLex = new Lexem [nLex];
	for (int i=0; i<nLex; i++)
		pLex[i] = res[i];

	cout<<view<<endl;
}

double Exprestion::Calc()													//������� ����������
{
	toPZ();
	return 0;
}