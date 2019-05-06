#pragma once
#include "TArrayTable.h"

template <class TKey,class TVal>
class TScanTable :public TArrayTable<TKey, TVal> {
public:
	TScanTable(int size) :TArrayTable<TKey,TVal>(size) {};
	bool Find(TKey key);
	bool Insert(TRecord<TKey,TVal> rec);
	bool DeleteKey(TKey key);
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

