#ifndef RESTIFY_H
#define RESTIFY_H

#include <QtGui>
#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
class QHBoxLayout;
class QVBoxLayout;
class QTabWidget;
class QComboBox;
class QLineEdit;
class QPushButton;
class QTextEdit;
QT_END_NAMESPACE

class Restify : public QWidget
{
	Q_OBJECT

	public:
		Restify();
		QString getMethod();
		QString getUrl();

	private slots:
		void _request();
		void _requestReply(QNetworkReply *reply);

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
		QNetworkAccessManager *request;
		QNetworkReply *requestReply;
};

#endif
