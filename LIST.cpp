#include <iostream>
using namespace std;

class List
{
	public:

		List(){ // конструктор списка
			Size = 0;
			head = nullptr;
		}


		~List(){ // деструктор списка
			clear();
		}


		void popFront(){ // удалить первый элемент
			Node *temp = head;
			head = head->next;
			delete temp;
			Size--;
		}


		void append(int value){ // добавить элемент к списку справа
			if (head == nullptr)
			{
				head = new Node(value);
			}
			else
			{
				Node *current = this->head;
				while (current->next != nullptr)
				{
					current = current->next;
				}
				current->next = new Node(value);
			}
			Size++;
		}


		void clear(){ // удалить список
			while (Size)
			{
				popFront();
			}
		}


		void insertPrew(int value, int index){  // вставить элемент перед элемента с заданным индексом
			if (index == 0)
			{
				append(value);
			}
			else
			{
				Node *previous = this->head;
				for (int i = 0; i < index - 1; i++)
				{
					previous = previous->next;
				}
				Node *newNode = new Node(value, previous->next);
				previous->next = newNode;
				Size++;
			}

		}


		void insertNext(int value, int index){ // вставить элемент после элемента с заданным индексом
			if (index == 0)
			{
				append(value);
			}
			else
			{
				Node *next_next = this->head;
				for (int i = 0; i < index; i++)
				{
					next_next = next_next->next;
				}
				Node *newNode = new Node(value, next_next->next);
				next_next->next = newNode;
				Size++;
			}
		}


		void deleteNode(int index){ // удаляем элемент по индексу
			if (index == 0)
			{
				popFront();
			}
			else
			{
				Node *previous = this->head;
				for (int i = 0; i < index - 1; i++)
				{
					previous = previous->next;
				}
				Node *toDelete = previous->next;
				previous->next = toDelete->next;
				delete toDelete;
				Size--;
			}
		}
	

		bool isEmptyList(){ // проверка на пустоту
			return Size == 0;
		}


		void printList() { // печатаем список
        	if (isEmptyList()) return;
        	Node* elemNode = head;
			cout<<"List: ";
        	while (elemNode) {
            	cout << elemNode->value << " ";
            	elemNode = elemNode->next;
        	}
        	cout << endl;
    	}


		int findNode(int value){ // находим индекс по элементу
			if (isEmptyList()) return -1;
			Node* elemNode = head;
			for (int i = 0; i< Size; ++i){
				if (value == elemNode->value) return i;
				else if (i == Size - 1) return -1;
				else elemNode = elemNode->next;
			}
		
		} 


		int findPrev(int value){ // находим индекс предыдущего элемента по элементу
			if (isEmptyList()) return -1;
			int val = findNode(value);
			if (val <= 0) return false;
			int prevval = val - 1;
			return prevval;
		}


		int findNext(int value){ // находим индекс следующего элемента по элементу
			if (isEmptyList()) return -1;
			int val = findNode(value);
			if (val >= Size) return false;
			int nextval = val + 1;
			return nextval;
		}


		void printNode(int index){ // печатаеем элемент по индексу
			Node *elemNode = head;
			for (int i = 0; i < index; ++i){
				elemNode = elemNode->next;
			}
			cout<<"element: "<<""<< elemNode->value<<endl;
		} 


	private:


		class Node
		{
			public:
				Node * next; //следующий
				int value; // значение

				Node(int value, Node *next = nullptr) // конструктор узла
				{
					this->value = value;
					this->next = next;
				}
		
		};
		int Size; // размер
		Node *head; //голова
};




int main()
{
	List lst; // создаем список
	lst.append(1);
	lst.append(2);
	lst.append(3);
	lst.append(4);
	lst.append(5);
	lst.append(6);
	lst.printList();

	lst.printNode(lst.findNext(3)); // после 3
	lst.printNode(lst.findPrev(3)); // перед 3


	lst.append(6); //добавляем 6 в конец
	lst.printList();

	lst.insertNext(3, lst.findNode(3)); // ставим 3 после 3
	lst.printList();

	lst.insertPrew(4, lst.findNode(5)); // ставим 4 перед 5
	lst.printList();

	lst.deleteNode(lst.findNode(2)); // удаляем 2
	lst.printList();
	cout<<"deletion check: "<< endl;


	lst.~List(); // удаляем весь список
	lst.printList();


	return 0;
}