#ifndef RESTIFY_H
#define RESTIFY_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QButtonGroup;
class QHBoxLayout;
class QPushButton;
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE

class Restify : public QWidget
{
	public:
		Restify();

	private:
		void setupOptions();

		QPushButton *methodGet, *methodPost, *methodPut, *methodDelete;
		QButtonGroup *methodsGroup;
		QHBoxLayout *methods;
		QLineEdit *url;
		QPushButton *submit;
		QHBoxLayout *requestLayout;
};

#endif
