#include <string>

// ����� ����������
class stexcp :public std::exception
{
private:
	std::string errmsg;
public:
	stexcp(const std::string &msg) { errmsg = msg; }
};

// ������ ������ ����
template<class sType>
class Stack
{
private:
	int Size;
	int top;
	sType* StackMem;

public:
	Stack(int s = 1000);							// ����������� �� ���������
	~Stack();										// ����������
	Stack(const Stack<sType>& src);			// ���������� �����������
	int GetSize() const							// ������
	{return Size;}	
	void push(const sType& val);				// ��������� ������� �� ������� �����
	sType pop();									// ������� ������� �� �����
	sType peek() const;							// ������� ����� ��� ��������
	bool empty() const							// ���� �� ����
	{
		return (top == -1);
	}
};

template<class sType>
Stack<sType>::Stack(int s) : Size(s)
{
	if (s>0)
	{
		top = -1;
		StackMem = new sType[Size];
	}
	else
		throw "negative size";
}

template<class sType>
Stack<sType>::~Stack()
{
	delete[] StackMem;
}

template<class sType>		
Stack<sType>::Stack(const Stack<sType>& src)
{
	Size = src.Size;
	StackMem = new sType[Size];
	for (int i = 0; i < top+1; i++)
		StackMem[i] = src.StackMem[i];
	
}

template<class sType>
void Stack<sType>::push(const sType& val)
{
	if (top == Size - 1)
	{
		Size +=8;
		sType* tmp = new sType[Size];
		for (int i = 0; i < top + 1; i++)
			tmp[i] = StackMem[i];
		delete[] StackMem;
		StackMem = tmp;

	}
		top++;
		StackMem[top] = val;
}

template<class sType>
sType Stack<sType>::peek() const
{
	if (!empty())
		return StackMem[top];
	else
		throw "Stack is empty";
}
template<class sType>
sType Stack<sType>::pop()
{
	if (!empty())
		return StackMem[top--];
	else
		throw "Stack is empty";
}
