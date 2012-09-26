#ifndef RESTIFY_H
#define RESTIFY_H

#include <QWidget>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>

class Restify : public QWidget
{
	public:
		Restify();

	private:
		void setupOptions();

		QHBoxLayout *requestLayout;
		QComboBox *method;
		QLineEdit *url;
		QPushButton *submit;
};

#endif
