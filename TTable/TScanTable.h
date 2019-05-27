#pragma once
#include "TArrayTable.h"
#include <fstream>
#include <iostream>
using namespace std;

template <class TKey,class TVal>
class TScanTable :public TArrayTable<TKey, TVal> {
public:
	TScanTable(int size = 10) :TArrayTable<TKey, TVal>(size) {};
	bool Find(TKey key);
	bool Insert(TRecord<TKey,TVal> rec);
	bool DeleteKey(TKey key);
	void Fill(char *s);
	void Print();
};

template <class TKey,class TVal>
bool TScanTable<TKey, TVal>::Find(TKey key) {
	for (int i = 0; i < DataCount; i++) {
		if (arr[i].key == key) {
			Curr = i;
			return true;
		}
	}
	Curr = DataCount;
	return false;
}

template <class TKey, class TVal>
bool TScanTable<TKey, TVal>::Insert(TRecord<TKey, TVal> rec) {
	if (Find(rec.key) || IsFull())return false;
	else {
		arr[Curr] = rec;
		Eff++;
		DataCount++;
		return true;
	}
}

template <class TKey, class TVal>
bool TScanTable<TKey, TVal>::DeleteKey(TKey key) {
	if (Find(key)) {
		arr[Curr] = arr[DataCount - 1];
		DataCount--;
		Eff++;
		return true;
	}
	else return false;
}

template <class TKey,class TVal>
void TScanTable<TKey, TVal>::Fill(char *s) {
	ifstream ifs(s);
	TRecord<TKey, TVal> tmp1;
	while (!ifs.eof()) {
		ifs >> tmp1.key >> tmp1.val;
		Insert(tmp1);
	}
}

template <class TKey, class TVal>
void TScanTable<TKey, TVal>::Print() {
	cout << "Scan Table" << endl;
	cout << "----------------------------------------" << endl;
	for (int i = 0; i < DataCount; i++)
		cout << arr[i].key << " " << arr[i].val << endl;
}