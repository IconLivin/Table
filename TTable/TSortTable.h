#pragma once
#include "TArrayTable.h"
#include "TScanTable.h"
#include <fstream>
#include <iostream>
using namespace std;

template <class TKey,class TVal>
class TSortTable :public TArrayTable<TKey, TVal> {
public:
	TSortTable(int size = 10) :TArrayTable<TKey, TVal>(size) {};
	TSortTable(TScanTable<TKey, TVal> &tmp);
	bool Find(TKey key);
	bool Insert(TRecord<TKey, TVal> rec);
	bool DeleteKey(TKey key);
	void Sort(int Start, int End);
	void Fill(char *s);
	void Print();
};

template <class TKey, class TVal>
TSortTable<TKey, TVal>::TSortTable(TScanTable<TKey, TVal> &tmp):TArrayTable<TKey,TVal>(tmp) {
	Sort(0, DataCount-1);
}

template <class TKey,class TVal>
bool TSortTable<TKey, TVal>::Find(TKey key) {
	int n = 0;
	int k = DataCount - 1,s;
	while (n <= k) {
		Eff++;
		s = (k + n) / 2;
		if (arr[s].key == key) {
			Curr = s;
			return true;
		}
		else if (arr[s].key > key)k = s - 1;
		else n = s + 1;
	}
	Curr = n;
	return false;
}

template <class TKey, class TVal>
bool TSortTable<TKey, TVal>::Insert(TRecord<TKey, TVal> rec) {
	if (Find(rec.key) || IsFull())return false;
	else {
		for (int i = DataCount - 1; i >= Curr; i -- ) {
			arr[i + 1] = arr[i];
			Eff++;
		}
		arr[Curr] = rec;
		Curr++;
		DataCount++;
		return true;
	}
}

template <class TKey, class TVal>
bool TSortTable<TKey, TVal>::DeleteKey(TKey key) {
	if (!Find(key) || !isEmpty())return false;
	else {
		for (int i = Curr; i < DataCount; i++) {
			arr[i] = arr[i + 1];
			Eff++;
		}
		DataCount--;
		return true;
	}
}

template <class TKey, class TVal>
void TSortTable<TKey, TVal>::Sort(int Start, int End) {
	TRecord<TKey,TVal> pivot; // разрешающий элемент
	int l_hold = Start; //левая граница
	int r_hold = End; // правая граница
	pivot = arr[Start];
	while (Start < End) // пока границы не сомкнутся
	{
		while ((arr[End].key >= pivot.key) && (Start < End))
			End--; // сдвигаем правую границу пока элемент [right] больше [pivot]
		if (Start != End) // если границы не сомкнулись
		{
			arr[Start] = arr[End]; // перемещаем элемент [right] на место разрешающего
			Start++; // сдвигаем левую границу вправо 
		}
		while ((arr[Start].key <= pivot.key) && (Start < End))
			Start++; // сдвигаем левую границу пока элемент [left] меньше [pivot]
		if (Start != End) // если границы не сомкнулись
		{
			arr[End] = arr[Start]; // перемещаем элемент [left] на место [right]
			End--; // сдвигаем правую границу вправо 
		}
	}
	arr[Start] = pivot; // ставим разрешающий элемент на место
	int t_pivot = Start;
	Start = l_hold;
	End = r_hold;
	if (Start < t_pivot) // Рекурсивно вызываем сортировку для левой и правой части массива
		Sort(Start, t_pivot - 1);
	if (End > t_pivot)
		Sort(t_pivot + 1, End);
}

template <class TKey, class TVal>
void TSortTable<TKey, TVal>::Fill(char *s) {
	ifstream f(s);
	TRecord<TKey, TVal> tmp1;
	while (!f.eof()) {
		f >> tmp1.key >> tmp1.val;
		Insert(tmp1);
	}
	
}

template <class TKey, class TVal>
void TSortTable<TKey, TVal>::Print() {
	cout << "Sort Table" << endl;
	cout << "----------------------------------------" << endl;
	for (Reset();!IsEnd(); GoNext())
		cout << arr[Curr].key <<" "<< arr[Curr].val << endl;
}

