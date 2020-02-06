#include<iostream>

class Forwardlist
{
	class Element
	{
		int Data;
		Element* pNext;
		static int count; //����������� ���������� (���������������� �� �������)
	public:
		// Constructor:
		Element(int Data, Element* pNext = nullptr)
		{
			this->Data = Data;
			this->pNext = pNext;
			count++;
			std::cout << "EConstructor:\t" << this << std::endl;
		}
		// Destructor:
		~Element()
		{
			count--;
			std::cout << "EDestructor:\t" << this << std::endl;
		}
		friend class Forwardlist;
	};

	int size;
	Element* Head;
public:
	// Constructor:
	Forwardlist()
	{
		this->Head = nullptr;
		std::cout << "LConstructor:\t" << this << std::endl;
		this->size = 0;
	}

	Forwardlist(std::initializer_list<int>il) :Forwardlist() // Container (���������) - ��� ������ � ������� ����� ������� ������ 
	{
		std::cout << typeid(il.begin()).name() << std::endl; // ������ ���������� int const*
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
		std::cout << "ILConstructor" << std::endl;
	}

	// �������� ����� �� ������������ ���������� ���������
	explicit Forwardlist(int number) :Forwardlist() // ������������� ������������� (�� ���� ��� ������ �������� ���� ����������� ���������� ������) 
	// explicit ��������� ������� �������������� ���� Forwardlist list1 = 5
	{
		while (number--) push_front(0);
		std::cout << "LConstructor:\t" << this << std::endl;
	}

	Forwardlist(Forwardlist&& other)  // ������� �������� ������ ������ � ������� �������� � ���� other
	{
		this->size = other.size;
		this->Head = other.Head;
		other.Head = nullptr; // ��������� ��������� (���� ����� ����������� �� ��������� ������� ������ �� ������� ������ ��������� this->str)
		std::cout << "MoveConstructor" << this << std::endl;
	}

	// Destructor:
	~Forwardlist()
	{
		while (Head) pop_front();
		std::cout << "LDestructor:\t" << this << std::endl;
	}


	//////////////////////////	METODS: ///////////////////////////////////
	void push_front(int Data) // ���������� �������� � ������ ������
	{
		Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;
		size++;
	}

	void push_back(int Data) // ���������� �������� � ����� ������
	{
		Element* Temp = Head;

		if (Head == nullptr)
		{
			push_front(Data);
			return;
		}
		while (Temp->pNext != nullptr)
		{
			Temp = Temp->pNext;// ������� � ����������
		}
		Element* New = new Element(Data);
		Temp->pNext = New;
		size++;
	}

	void pop_front() // �������� �������� � ������ ������
	{
		Element* Temp = Head;
		Head = Temp->pNext;
		delete Temp;
		size--;
	}

	void pop_back() // �������� �������� � ����� ������
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	void insert(int index, int Data) // ���������� �� �������
	{
		if (index == 0)
		{
			push_front(Data);
			return;
		}
		if (index >= this->size)
		{
			push_back(Data);
			return;
		}
		Element* Temp = Head;
		//1) ������� �������
		Element* New = new Element(Data);
		//2) ������� �� ������ ������� � ������
		Temp = Head;
		for (int i = 0; i < index - 1; i++)
		{
			Temp = Temp->pNext;
		}
		//3)��������� ����� ������� � ������
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
	}

	void erase(int index) // �������� �� �������
	{
		Element* Temp = Head;
		if (index == 0)
		{
			pop_front();
			return;
		}

		if (index == size - 1)
		{
			pop_back();
			return;
		}

		if (index >= size)
		{
			std::cout << std::endl << "Error" << std::endl;
			return;
		}

		for (int i = 0; i < index - 1; i++)
		{
			Temp = Temp->pNext;
		}
		Element* buffer = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete buffer;
		size--;
	}

	void print() // ����� ������ �� �����
	{
		Element* Temp = Head; // Temp - ��������(��������� ��� ������ �������� ����� �������� 
		//������ � ��������� ��������� ������)
		int coun = 0;
		std::cout << "-------------------------------------------------------------" << std::endl;
		std::cout << "�" << "\t" << "Address" << "\t\t" << "Data" << "\t" << "pNext" << std::endl;
		std::cout << "-------------------------------------------------------------" << std::endl;
		while (Temp)
		{
			std::cout << coun << "\t" << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << std::endl;
			std::cout << "-------------------------------------------------------------" << std::endl;
			Temp = Temp->pNext;// ������� �� ��������� �������
			coun++;
		}
		std::cout << "\tcount = " << size << std::endl;
	}
	/************************* OPERATORS ***************************/
	int& operator [](int index)
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)
		{
			Temp = Temp->pNext;
		}
		return Temp->Data;
	}

};


//#define OTLADKA1
#define OTLADKA2
int Forwardlist::Element::count = 0;// ������������� ����������� ����������

void main()
{
	system("color 0A");
	setlocale(LC_ALL, "");

#ifdef OTLADKA1
	int n;
	std::cout << "Input List size:"; std::cin >> n;
	Forwardlist fl;
	for (int i = 0; i < n; i++)
	{
		fl.push_front(rand() % 100);
	}
	int index;
	fl.print();

	std::cout << "-----------------POP_BACK----------------" << std::endl;
	fl.pop_back();
	fl.print();

	std::cout << "-----------------ERASE----------------" << std::endl;
	std::cout << "Input Index: "; std::cin >> index;
	fl.erase(index);
	fl.print();

	std::cout << "-----------------INSERT----------------" << std::endl;
	std::cout << "Input Index: "; std::cin >> index;
	fl.insert(index, 1230);
	fl.print();

#endif

#ifdef OTLADKA2

	//int n = 5;
	//Forwardlist list1(n);

	/////////////////// �������� ������ ��������� ��������	
	//for (int i = 0; i < n; i++)
	//{
	//	list1[i] = rand() % 100;
	//}
	/////////////////// �������� ��������� []
	//for (int i = 0; i < n; i++)
	//{
	//	std::cout << list1[i] << "\t";
	//}
	//std::cout << std::endl;

	Forwardlist list1 = { 2,3,4,5,5 };
	Forwardlist list2;
	list1.print();
	list2.print();
#endif

}

