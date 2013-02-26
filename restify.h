#ifndef RESTIFY_H
#define RESTIFY_H

#include <QtWidgets>
#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTableWidget>
#include "highlighter.h"

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
		void _toggleConfig();
		void _toggleLaunchPad();
		void _requestSample(const QString& link);

	private:
		void _setupRequest();
		void _setupResponse();
		void _setupLaunchPad();

		void _setHeaders(const QList<QPair<QByteArray, QByteArray> > headers, QTableWidget *table);

		QHBoxLayout *requestLayout;
		QLabel *message;
		QVBoxLayout *layout;
		QComboBox *method;
		QLineEdit *url;
		QPushButton *submit;
		QMovie *loadingMovie;
		QLabel *loading;

		QWidget *launchPad;
		QVBoxLayout *launchPadLayout;
		QLabel *launchPad_Vimeo;
		QLabel *launchPad_GitHub;
		QLabel *launchPad_Twitter;
		QLabel *launchPad_Samples;
		QLabel *launchPad_Samples_1;
		QLabel *launchPad_Samples_2;
		QLabel *launchPad_Samples_3;
		QPushButton *gettingStarted;

		QLabel *settings;
		QTableWidget *configData;
		QTableWidget *configHeaders;
		QTabWidget *configLayout;

		QTabWidget *responseLayout;
		QTextEdit *responseContent;
		Highlighter *highlighter;
		QTableWidget *responseHeadersReceived, *responseHeadersSent;
		QNetworkAccessManager *networkAccess;
		QNetworkReply *requestReply;
};

#endif
