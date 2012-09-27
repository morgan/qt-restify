#ifndef RESTIFY_H
#define RESTIFY_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTabWidget>
#include <QTextEdit>

class Restify : public QWidget
{
	Q_OBJECT

	public:
		Restify();
		QString getMethod();
		QString getUrl();

	private slots:
		void _request();

	private:
		void _setupRequest();
		void _setupResponse();

		QHBoxLayout *requestLayout;
		QVBoxLayout *layout;
		QComboBox *method;
		QLineEdit *url;
		QPushButton *submit;
		QTabWidget *responseLayout;
		QTextEdit *responseContent;
};

#endif
