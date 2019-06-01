#pragma once
#include <fstream>
#include <iostream>
#include "TTable.h"
using namespace std;

template <class TKey,class TVal>
class THashTable :public TTable<TKey, TVal> {
protected:
	int MaxSize;
	TRecord<TKey, TVal> *arr;
	int Curr, step;
	int HashFunc(TKey key);
	int NextPos(int cpos);
public:
	THashTable(int size = 100, int st = 11);
	~THashTable() { delete[] arr; }
	THashTable(const THashTable<TKey, TVal> &tmp);
	THashTable operator=(THashTable<TKey, TVal> &tmp);
	bool IsFull();
	void Reset();
	bool IsEnd();
	void GoNext();
	bool Find(TKey key);
	bool Insert(TRecord<TKey, TVal> rec);
	bool DeleteKey(TKey);
	TRecord<TKey, TVal> GetCurr() { return arr[Curr];}
	void Print();
	void Fill(char *s);
};

template <class TKey,class TVal>
int THashTable<TKey, TVal>::HashFunc(TKey key){
	return key % MaxSize;
}

template <class TKey, class TVal>
int THashTable<TKey, TVal>::NextPos(int pos) {
	return (pos + step) % MaxSize;
}

template <class TKey, class TVal>
THashTable<TKey, TVal>::THashTable(int size,int st) {
	MaxSize = size;
	step = st;
	DataCount = 0;
	arr = new TRecord<TKey, TVal>[MaxSize];
	Curr = 0;
	for (int i = 0; i < MaxSize; i++)arr[i].key = 0;
}

template <class TKey, class TVal>
THashTable<TKey, TVal>::THashTable(const THashTable<TKey, TVal> &tmp) {
	MaxSize = tmp.MaxSize;
	step = tmp.step;
	Curr = tmp.Curr;
	DataCount = tmp.DataCount;
	arr = new TRecord<TKey, TVal>[MaxSize];
	for (int i = 0; i < MaxSize; i++)
		arr[i] = tmp.arr[i];
}

template <class TKey, class TVal>
THashTable<TKey,TVal> THashTable<TKey, TVal>::operator=(THashTable<TKey,TVal> &tmp) {
	Curr = tmp.Curr;
	step = tmp.step;
	DataCount = tmp.DataCount;
	if (MaxSize != tmp.MaxSize) {
		MaxSize = tmp.MaxSize;
		delete[] arr;
		arr = new TRecord<TKey, TVal>[MaxSize];
	}
	for (int i = 0; i < MaxSize; i++)
		arr[i] = tmp.arr[i];
}

template <class TKey, class TVal>
bool THashTable<TKey, TVal>::IsFull() { return DataCount == MaxSize; }

template <class TKey, class TVal>
bool THashTable<TKey, TVal>::IsEnd() { return Curr == MaxSize; }

template <class TKey, class TVal>
void THashTable<TKey, TVal>::Reset() {
	if (DataCount > 0) {
		Curr = 0;
		while (IsEnd() && (arr[Curr].key == 0 || arr[Curr].key == -1))Curr++;
	}
}

template <class TKey, class TVal>
void  THashTable<TKey, TVal>::GoNext() { 
	Curr++;
	while (IsEnd()&&(arr[Curr].key == 0 || arr[Curr].key == -1))Curr++;
}

template <class TKey, class TVal>
bool  THashTable<TKey, TVal>::Find(TKey key) {
	Curr = HashFunc(key);
	int fPos = -1;
	for (int i = 0; i < MaxSize; i++)
	{
		Eff++;
		if (arr[Curr].key == key)return true;
		else if (arr[Curr].key == 0) {
			if (fPos != -1)Curr = fPos;
			return false;
		}
		else if (arr[Curr].key == -1) {
			if (fPos == -1)fPos = Curr;
		}
		Curr = NextPos(Curr);
	}
}

template <class TKey, class TVal>
bool  THashTable<TKey, TVal>::Insert(TRecord<TKey, TVal> rec) {
	if (IsFull() || Find(rec.key))return false;
	else {
		arr[Curr] = rec;
		DataCount++;
		return true;
	}
}

template <class TKey, class TVal>
bool  THashTable<TKey, TVal>::DeleteKey(TKey key) {
	if (isEmpty() || !Find(key))return false;
	else {
		arr[Curr].key = -1;
		DataCount--;
		return true;
	}
}

template <class TKey, class TVal>
void THashTable<TKey, TVal>::Fill(char *s) {
	ifstream ifs(s);
	TRecord<TKey, TVal> tmp1;
	while (!ifs.eof()) {
		ifs >> tmp1.key >> tmp1.val;
		Insert(tmp1);
	}
}

template <class TKey, class TVal>
void THashTable<TKey, TVal>::Print() {
	cout << "Hash Table" << endl;
	cout << "----------------------------------------" << endl;
	for (Reset(); !IsEnd(); GoNext()) {
		if (arr[Curr].key != 0) {
			if (arr[Curr].key != -1)
				cout << arr[Curr].key << " " << arr[Curr].val << endl;
		}
	}
}