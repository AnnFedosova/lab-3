#include <stdio.h>
#include <iostream>

//класс упорядоченная таблица
#define M_SIZE 32	// размер массива
#define I_SIZE 128	// размер информации

#define DEFAULT_INFO "INFO"

typedef struct Item {
	int key;
	int info_len;
	char info[I_SIZE];
}item_t;

class CTable
{
private:
	item_t item[M_SIZE];
	int amnt;	//количество заполненных item
public:
	CTable() { item_t item[M_SIZE] = { 0 }; amnt = 0; };
	CTable(int size) 
	{
		if (size >= M_SIZE)
			size = M_SIZE;
		for (int i = 0; i < size; i++)
			creat_item(i, i, DEFAULT_INFO, sizeof(DEFAULT_INFO));
		amnt = size;
	};
	//CDecartovList(int _n) {n = _n; };
	int get_amnt()
	{
		return amnt;
	}
	void creat_item(int item_idx)
	{
		item[item_idx].key = item_idx; item[item_idx].info_len = 0; item[item_idx].info[0] = 0;
	};
	void creat_item(int item_idx, int key, char* info, int info_len)
	{
		item[item_idx].key = key; item[item_idx].info_len = info_len; memcpy(item[item_idx].info, info, info_len);
	};
	int findkey(int key);
	int getkey(int* key);
	int getinfo(char* info);
	void print_item_by_key(int key);
	void print_items();
	int add_item(item_t item);
	int create_item();
	int del_item(int key);

	CTable &operator-(int key)
	{
		del_item(key);
		return *this;
	}

	CTable &operator+(item_t new_item)
	{
		add_item(new_item);
		return *this;
	}

	char* operator [](int idx)
	{
		return item[idx].info;
	}
};