#pragma once
#include "TTable.h"

template <class TKey,class TVal>
class TArrayTable :public TTable<TKey, TVal> {
protected:
	TRecord<TKey,TVal> *arr;
	int Max_Size;
	int Curr;
public:
	TArrayTable(int MS) { Max_Size = MS; arr = new TRecord[Max_Size]; curr = -1; }
	~TArrayTable() { delete[] arr; }
	TArrayTable(TArrayTable &tb);
	bool IsFull();
	void Reset();
	void GoNext();
	bool IsEnd();
	TRecord GetCurr();
};

template<class TKey,class TVal>
TArrayTable<TKey, TVal>::TArrayTable(TArrayTable &tb) {
	Max_Size = tb.Max_Size;
	arr = new arr[Max_Size];
	DataCount = tb.DataCount;
	Curr = tb.Curr;
	for (int i = 0; i < Max_Size; i++)arr[i] = tb.arr[i];
}

template<class TKey,class TVal>
bool TArrayTable<TKey, TVal>::IsFull() {
	return DataCount == Max_Size;
}

template<class TKey, class TVal>
void TArrayTable<TKey, TVal>::Reset() { Curr = 0; }

template<class TKey, class TVal>
void TArrayTable<TKey, TVal>::GoNext() { Curr++; }

template<class TKey, class TVal>
bool TArrayTable<TKey, TVal>::IsEnd() { return Curr == DataCount; }

template<class TKey, class TVal>
TRecord<TKey,TVal> TArrayTable<TKey, TVal>::GetCurr() { return arr[curr]; }
