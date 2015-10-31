
#include <stdio.h>
#include <iostream>
#include "laba3.h"
//����� ������������� �������

int getNum(int* a, char* word)
{
	int data;
	std::cout << word << std::endl;
	std::cin >> data;
	if (!std::cin.good())
	{
		std::cout << "error" << std::endl;
		std::cin.clear();
		return -1;
	}
	*a = data;
	return 0;
}

int CTable::add_item(item_t Item)
{
	int res = 0;	//��������� 

	do {
		if (amnt >= M_SIZE)
		{
			std::cout << "full table" << std::endl;
			res = -1;
			break;
		}

		int cur_pos = 0;
		// ���� �������, ���� ���������
		while (cur_pos < amnt)
		{ 
			if (item[cur_pos].key >= Item.key)
				break;
			cur_pos++;
		}

		if (item[cur_pos].key == Item.key)
		{// ��������������
			memcpy(&item[cur_pos], &Item, sizeof(item_t));	// ���������
		}
		else
		{// ��������� �����
			for (int i = amnt - 1; i >= cur_pos; i--)
				memcpy(&item[i + 1], &item[i], sizeof(item_t));	// �������
			memcpy(&item[cur_pos], &Item, sizeof(item_t));	// ���������
			amnt++;
		}
		std::cout << "item added" << std::endl << std::endl;
	} while (0);
	
	return res;
}

int CTable::create_item()
{
	int res = 0;
	item_t item;
	do {
		if ((res = getkey(&(item.key))) < 0)
			break; // ����� ��� ������������ ���� � �� �������� ������ ����������
		if ((res = getinfo(item.info)) < 0)
			break;
		item.info_len = res;
		*this + item;
		res = 0;
	} while (0);
	return res;
}

//����� ����� ���� ��� -1
//�������� ����� �� �����
int CTable::findkey(int key)
{

	int L = 0; //����� �������
	int R = 0; //������ �������
	int m = 0; //�������� �������
		for (int i = 0; i < amnt; i++)
		{
			L = 0;
			R = amnt;
			while ( L < R ) //���� ����� ������� ������� ������ �������� �������
			{
				m = (L + R) / 2; // ����� ������ �������
				if ( item[m].key < key) //���� ������� ������� ������ ��������
					L = m + 1; //����� ����� �������� ������
				else //�����
					R = m; //������� ������ ��������� ������� ��������( ����� ����� �������� �������)
			}
		}
	

	if (item[R].key != key)
	{
		return -1;
	}
	return R;
}

//return -1 ,���� ���� �� ������
//return res>0 , res - ����� ����������
int CTable::del_item(int key)
{
	int res = findkey(key);

	if ( res < 0)
		std::cout << "There is no item in the table " << std::endl;

	else 
	{
		for (int i = res; i < amnt; i++)
			memcpy(&item[i], &item[i + 1], sizeof(item_t));	// �������
		std::cout << "item deleted " << std::endl;
		amnt--;
	}
	return res;
}

void CTable::print_item_by_key(int key)
{	
	std::cout << "key : " << key << std::endl;
	int i = CTable::findkey(key);
	if (i < 0)
		std::cout << "there is no key in the table" << std::endl;
	else		
		std::cout << "info : " << this->operator[](i) << std::endl;
}

void CTable::print_items()
{
	for (int i = 0; i < amnt; i++)
		print_item_by_key(item[i].key);
	std::cout << std::endl;
}

//����� 0 ��� ���������� ��������� �����,���� ��� ����������
//����� -1 ��� ������
int CTable::getkey(int* key)
{
	int res = 0;

	if (getNum(key, "Write key: ") < 0)
		while (getNum(key, "Write correct key: ") < 0) {};

	if (findkey(*key) >= 0)
	{ // ���� �� ��������
		std::cout << "key already exists, rewrite info? (y/n)";
		char answer;
		std::cin >> answer;
		if (answer != 'y')
			res = -1;
	}
	return res;
}

// return: < 0 - ������, >= 0 - ������ ��������� ������ 
int CTable::getinfo(char* info)
{
	std::cout << "write info" << std::endl;
	std::cin >> info;
	if (!std::cin.good())
	{
		std::cin.clear();
		std::cout << "error" << std::endl;
		return -1;
	}
	return strlen(info);
}

void print_menu()
{
	std::cout << "1 - create new table " << std::endl;
	std::cout << "2 - create default table" << std::endl;
	std::cout << "3 - add item" << std::endl;
	std::cout << "4 - add item by default" << std::endl;
	std::cout << "5 - print item" << std::endl;
	std::cout << "6 - print table" << std::endl;
	std::cout << "7 - del item" << std::endl;
	std::cout << "0 - exit" << std::endl;
}

int main()
{
	CTable table = CTable();

	print_menu();
	while (1)
	{
		// �������� � ��������� �������
		int res = 0;
		int menu = 0;
		res = getNum(&menu, "");
		if (res < 0)
			print_menu();
		else if (menu == 0)
			break;
		else if (menu == 1)
		{
			table = CTable();
			std::cout << "new table created" << std::endl << std::endl;
		}
		else if (menu == 2)
		{
			int size = 0;
			// �������� ���������� ���������
			getNum(&size, "size of table");
			table = CTable(size);
			std::cout << "new default table created" << std::endl << std::endl;
		}
		else if (menu == 3)
		{
			table.create_item();
				
		}
		else if (menu == 4)
		{
			int uniq_key = 0;
			while (table.findkey(uniq_key) >= 0) uniq_key++;
			item_t default_item;
			default_item.key = uniq_key;
			memcpy(default_item.info, DEFAULT_INFO, sizeof(DEFAULT_INFO));
			default_item.info_len = sizeof(DEFAULT_INFO);
			table + default_item;
		}
		else if (menu == 5)
		{
			int key = 0;
			getNum(&key, "Write key: ");
			table.print_item_by_key(key);
		}

		else if (menu == 6)
		{
			table.print_items();
			std::cout << std::endl << std::endl;
			for (int i = 0; i < table.get_amnt(); i++)
				std::cout << table[i] << std::endl;
			std::cout << std::endl << std::endl;
		}

		else if (menu == 7)
		{
			int key = 0;
			getNum(&key, "Write key: ");
			table - key;
		}
			print_menu();
			if (res < 0)
				break;
	}
	

	system("pause");
	return 0;
}