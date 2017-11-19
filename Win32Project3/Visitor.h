#pragma once
#include "Massiv.h"
template <typename T>
class KMyVector;

template<typename T>
class Visitor {
public:
	virtual void Visit(KMyVector<T>& ð) = 0;
};


template<typename T>
class Sum : public Visitor<T> {
public:
	Sum() : sum(0) {}

	void Visit(KMyVector<T>& p) {
		for (auto it = p.begin(); it != p.end(); ++it) {
			sum += (*it);
		}
	}
	T GetSum() {
		return sum;
	}
private:
	T sum;
};
