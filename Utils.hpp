#ifndef UTILS_H_
#define UTILS_H_

#include "Global.hpp"

#include <QWidget>
#include <QString>
#include <QLineEdit>
#include <QFileDialog>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStringList>
#include <QUrl>
#include <QList>





template <class T>
class Singleton 
{
private:
	static T *self_ptr;

public:
	inline static T* Instance() 
		{
			if (NULL == self_ptr )
				self_ptr = new T;
			return self_ptr;

		};
protected:
	Singleton() {}; //1
	
	virtual ~Singleton() {qDebug() << "singleton destroyed";};
//	virtual ~Singleton() {qDebug() << "singleton destroyed"; Singleton<T>::self_ptr = NULL;};
private:
	Singleton(T&);
	Singleton(T*);
	void operator= (T&);
};

template <class T>
T* Singleton<T>::self_ptr = NULL;


#endif //UTILS_H_
