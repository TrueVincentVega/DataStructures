#include<iostream>

class Forwardlist
{
	class Element
	{
		int Data;
		Element* pNext;
		static int count; //статическая переменная (инициализируется за классом)
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

	Forwardlist(std::initializer_list<int>il) :Forwardlist() // Container (Контейнер) - это объект в котором можно хранить данные 
	{
		std::cout << typeid(il.begin()).name() << std::endl; // запрос возвращает int const*
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
		std::cout << "ILConstructor" << std::endl;
	}

	// Создание листа на определенное количества элементов
	explicit Forwardlist(int number) :Forwardlist() // Делегирование конструкторов (до того как начнет работать один конструктор отработает другой) 
	// explicit запрещает неявное преобразование типа Forwardlist list1 = 5
	{
		while (number--) push_front(0);
		std::cout << "LConstructor:\t" << this << std::endl;
	}

	Forwardlist(Forwardlist&& other)  // Создает буферный объект класса и побитно копирует в него other
	{
		this->size = other.size;
		this->Head = other.Head;
		other.Head = nullptr; // Обнуление указателя (чтоб после деструктора не затерлась область памяти на которую сейчас указывает this->str)
		std::cout << "MoveConstructor" << this << std::endl;
	}

	// Destructor:
	~Forwardlist()
	{
		while (Head) pop_front();
		std::cout << "LDestructor:\t" << this << std::endl;
	}


	//////////////////////////	METODS: ///////////////////////////////////
	void push_front(int Data) // добавление элемента в начало списка
	{
		Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;
		size++;
	}

	void push_back(int Data) // добавление элемента в конец списка
	{
		Element* Temp = Head;

		if (Head == nullptr)
		{
			push_front(Data);
			return;
		}
		while (Temp->pNext != nullptr)
		{
			Temp = Temp->pNext;// переход к следующему
		}
		Element* New = new Element(Data);
		Temp->pNext = New;
		size++;
	}

	void pop_front() // удаление элемента с начала списка
	{
		Element* Temp = Head;
		Head = Temp->pNext;
		delete Temp;
		size--;
	}

	void pop_back() // удаление элемента с конца списка
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

	void insert(int index, int Data) // добавление по индексу
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
		//1) Создаем элемент
		Element* New = new Element(Data);
		//2) Доходим до нужной позиции в списке
		Temp = Head;
		for (int i = 0; i < index - 1; i++)
		{
			Temp = Temp->pNext;
		}
		//3)Вставляем новый элемент в список
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
	}

	void erase(int index) // удаление по индексу
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

	void print() // метод вывода на экран
	{
		Element* Temp = Head; // Temp - итератор(указатель при помощи которого можно получить 
		//доступ к элементам структуры данных)
		int coun = 0;
		std::cout << "-------------------------------------------------------------" << std::endl;
		std::cout << "№" << "\t" << "Address" << "\t\t" << "Data" << "\t" << "pNext" << std::endl;
		std::cout << "-------------------------------------------------------------" << std::endl;
		while (Temp)
		{
			std::cout << coun << "\t" << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << std::endl;
			std::cout << "-------------------------------------------------------------" << std::endl;
			Temp = Temp->pNext;// Переход на следующий элемент
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
int Forwardlist::Element::count = 0;// инициализация статической переменной

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

	/////////////////// Проверка записи случайных значений	
	//for (int i = 0; i < n; i++)
	//{
	//	list1[i] = rand() % 100;
	//}
	/////////////////// Проверка оператора []
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

