#pragma once
#include "TRecord.h"

template <class TKey,class TVal>
class TTable {
protected:
	int DataCount;//число элементов
	int Eff;//эффективность
public:
	TTable() { DataCount = 0; Eff = 0; }
	virtual ~TTable() {};
	int GetDataCount() { return DataCount; }
	int GetEff() { return Eff; }
	bool isEmpty() { return DataCount == 0; }
	virtual bool IsFull() = 0;
	virtual bool Find(TKey key) = 0;
	virtual bool DeleteKey(TKey key) = 0;
	virtual bool Insert(TRecord<TKey,TVal> rec) = 0;
	virtual TRecord GetCurr() = 0;
	virtual void Reset() = 0;
	virtual void GoNext() = 0;
	virtual bool IsEnd() = 0;
};