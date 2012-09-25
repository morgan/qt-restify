#ifndef RESTIFY_H
#define RESTIFY_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QInputDialog;
class QGroupBox;
class QGridLayout;
class QLabel;
class QVBoxLayout;
QT_END_NAMESPACE

class Restify : public QWidget
{
	public:
	    Restify();

	private:
		QInputDialog *url;
		QLabel *urlLabel;
	    QGroupBox *optionsGroupBox;
	    QGridLayout *optionsGroupBoxLayout;   
	    QVBoxLayout *mainLayout;
};

#endif
