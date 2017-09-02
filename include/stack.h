#include <iostream>

using namespace std;

const int MAX_STACK_SIZE = 100000000;

// Шаблон вектора
template <class ValType>
class TStack {
protected:
	ValType *pVector;
	int Size;       // размер вектора
	int Index; // индекс первого элемента вектора
public:
	TStack(int s = 10, int si = 0);
	TStack(const TStack &v);                // конструктор копирования
	virtual ~TStack();
	int GetSize() const { return Size; } // размер вектора
	int GetIndex() const { return Index; } // индекс первого элемента
	void IncIndex() { Index += 1; }
	void DecIndex() { if (Index != 0) Index -= 1; else throw invalid_argument("Stack is empty"); }
	bool IsEmpty(void);
	bool IsFull(void);
	void SetElem(ValType n);
	ValType GetElem(void);
	template <class ValType>
	friend ostream& operator<<(ostream &out, const TStack &v) 
	{
		for (int i = 0; i < v.Size + v.Index; i++)
			out << v[i] << ' ';
		return out;
	}
};

template <class ValType>
TStack<ValType>::TStack(int s, int si = 0) 
{
	if (s > MAX_STACK_SIZE) 
		throw invalid_argument("CONSTRUCTOR: MAX_STACK_SIZE < SIZE");
	
	if (s < 0) 
		throw invalid_argument("CONSTRUCTOR: SIZE < 0");
	
	pVector = new ValType[s];
	Size = s;
	Index = si;

	for (int i = 0; i < Size; i++) 
		pVector[i] = ValType();
	
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TStack<ValType>::TStack(const TStack<ValType> &v) 
{
	Size = v.Size;
	Index = v.Index;
	pVector = new ValType[Size];

	for (int i = 0; i < Index; i++) 
		pVector[i] = ValType();

	for (int i = Index; i < Size; i++) 
		pVector[i] = v.pVector[i];
} /*-------------------------------------------------------------------------*/

template <class ValType>
TStack<ValType>::~TStack() 
{
	delete[] pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType>
bool TStack<ValType>::IsEmpty(void)
{
	if (GetIndex()==0)
		return true;
	else
		return false;
} /*-------------------------------------------------------------------------*/

template <class ValType>
bool TStack<ValType>::IsFull(void)
{
	if (GetIndex() == GetSize())
		return true;
	else
		return false;
} /*-------------------------------------------------------------------------*/

template <class ValType>
void TStack<ValType>::SetElem(ValType n)
{
	if (IsFull())
		throw invalid_argument("Stackowerflow");

	(*this).pVector[GetIndex()] = n;
	IncIndex();
} /*-------------------------------------------------------------------------*/

template <class ValType>
ValType TStack<ValType>::GetElem(void)
{
	if (IsEmpty())
		throw invalid_argument("Stack is empty");

	ValType temp;
	DecIndex();
	temp = (*this).pVector[GetIndex()];
	(*this).pVector[GetIndex()] = ValType();

	return temp;
} /*-------------------------------------------------------------------------*/


