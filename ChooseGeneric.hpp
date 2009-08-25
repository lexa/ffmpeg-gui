
#ifndef CHOOSE_GENERIC_MY_H_
#define CHOOSE_GENERIC_MY_H_

#include <QWidget>


class GenericChoose 
	:public QWidget
{
public:
	GenericChoose (QWidget *parent = 0);
	virtual QStringList getParams() const;
	virtual ~GenericChoose();
};

#endif //CHOOSE_GENERIC_MY_H_
