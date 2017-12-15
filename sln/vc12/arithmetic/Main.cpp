#include "Exprestion.h"

void main()
{

	string s;
	int go=1;
	double result;
	cout<<"Welcome to my program"<<endl<<"give me an exprestion and i will try to give you a correct result"<<endl;
	cout<<"For Example: 12*3+10/(15-2)+1.12"<<endl<<endl;
	while (go)
	{
		cout<<"Your exprestion: "<<endl;
		getline(cin,s);
		Exprestion temp(s);
		if (temp.GlobalCheck()) 
		{
			temp.parse();
			temp.printLex();
			cout<<"All right, I am starting to calculate this..."<<endl;
			result = temp.Calc();
			temp.printLex();
			cout<<"The calculating have done"<<endl<<"Result: "<<result<<endl;
		}
		else
			cout<<"The exprestion isn't correct, please try again"<<endl;
		/*cout<<"Do you want to calculate an other exprestion?"<<endl;
		cout<<"1 = yes, 0 = no"<<endl;
		cin>>go;*/
		go = 0;
	}
}