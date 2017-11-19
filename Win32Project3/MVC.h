#pragma once
#include "Massiv.h"
#include "Visitor.h"
#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <algorithm>
using namespace std;

class Subject;

template <typename T>
class KMyVector;

template<typename T>
class Visitor;

template<typename T>
class Sum;

class KObserver {
public:
	virtual ~KObserver() {}
	virtual void Update(Subject*) = 0;
protected:
	KObserver() {}

};

class Subject {
public:
	virtual ~Subject() {}
	virtual void Attach(KObserver* obs) {
		fObservers.push_back(obs);
	}
	virtual void Detach(KObserver* obs) {
		fObservers.remove(obs);
	}
	virtual void Notify() {
		for (list<KObserver*>::iterator it = fObservers.begin(); it != fObservers.end(); ++it) {
			(*it)->Update(this);
		}
	}

protected:
	Subject() {}
private:
	list<KObserver*> fObservers;
};

template <typename T>
class KMyVectorObserver : public KObserver {
public:
	KMyVectorObserver(KMyVector<T>* aVector, HWND* aEdit) : fVector(aVector), fEdit(aEdit) { fVector->Attach(this); }
	virtual ~KMyVectorObserver() { fVector->Detach(this); }
	virtual void Update(Subject* obj) {
		if (obj == fVector) {
			stringstream iost;
			string str;

			iost.clear();
			iost << *fVector;
			getline(iost, str);
			SetWindowText(*fEdit, str.c_str());
		}
	}

private:
	KMyVector<T>* fVector;
	HWND* fEdit;
};




template <typename T>
class KMyVectorController;

template <typename T>
class KMyVectorView : public KObserver {
public:
	KMyVectorView(KMyVector<T>* aVector, HWND* aEdit, HWND* aAddItemsEdit, KMyVectorController<T>* aController) :
		fVector(aVector), fEdit(aEdit), fAddItemsEdit(aAddItemsEdit), fController(aController)
	{
		fVector->Attach(this);
	}
	virtual ~KMyVectorView() { fVector->Detach(this); }
	virtual void Update(Subject* obj) {
		if (obj == fVector) {
			stringstream iost;
			string str;

			iost.clear();
			iost << *fVector;
			getline(iost, str);
			SetWindowText(*fEdit, str.c_str());
		}
	}
	virtual void SendNewItems() {
		T x;
		stringstream iost;
		char str1[50];

		GetWindowText(*fAddItemsEdit, str1, 50);
		iost.clear();
		iost << str1;

		while (iost >> x) {
			fController->PushBack(x);
		}

	}
	virtual void PopFront() {
		fController->PopFront();
	}
private:
	KMyVector<T>* fVector;
	HWND* fEdit;
	HWND* fAddItemsEdit;
	KMyVectorController<T>* fController;
};


template <typename T>
class KMyVectorController {
public:
	KMyVectorController(KMyVector<T>* aVector) : fVector(aVector) {}
	~KMyVectorController() {}
	void PushBack(T item) {
		fVector->PushBack(item);
	}
	void PopFront() {
		fVector->PopFront();
	}
private:
	KMyVector<T>* fVector;
};
