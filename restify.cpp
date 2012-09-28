#include "restify.h"

Restify::Restify()
{
	this->_setupRequest();
	this->_setupResponse();

	requestLayout = new QHBoxLayout;
	requestLayout->addWidget(method);
	requestLayout->addWidget(url);
	requestLayout->addWidget(submit);

	layout = new QVBoxLayout;
	layout->addLayout(requestLayout);
	layout->addWidget(responseLayout);

	setLayout(layout);

	setWindowTitle(tr("Restify"));
	resize(800, 50);
}

QString Restify::getMethod()
{
	return method->currentText();
}

QString Restify::getUrl()
{
	return url->text();
}

void Restify::_setupRequest()
{
	method = new QComboBox;
	method->addItem("GET");
	method->addItem("POST");
	method->addItem("PUT");
	method->addItem("PATCH");
	method->addItem("DELETE");

	url = new QLineEdit("http://feeds.feedburner.com/KohanaModules?format=xml");
	url->setProperty("placeholderText", "http://api.example.com/resource.json?key=value");

	submit = new QPushButton(tr("Request"));
	submit->connect(submit, SIGNAL(clicked()), this, SLOT(_request()));
}

void Restify::_setupResponse()
{
	responseContent = new QTextEdit;
	responseContent->setProperty("readOnly", true);

	responseHeadersReceived = new QTableWidget;

	responseLayout = new QTabWidget;
	responseLayout->addTab(responseContent, tr("Response"));
	responseLayout->addTab(responseHeadersReceived, tr("Headers Received"));
	responseLayout->hide();
}

void Restify::_request()
{
	request = new QNetworkAccessManager(this);
	connect(request, SIGNAL(finished(QNetworkReply*)), this, SLOT(_requestReply(QNetworkReply*)));

	request->get(QNetworkRequest(QUrl(this->getUrl())));
}

void Restify::_requestReply(QNetworkReply *reply)
{
	QByteArray bytes = reply->readAll();
	QString string(bytes); 

	responseContent->setText(bytes);

	QList<QByteArray> replyHeaders = reply->rawHeaderList();

	QStringList tableLabels;
	tableLabels << "Name" << "Value";

	responseHeadersReceived->clear();
	responseHeadersReceived->setRowCount(replyHeaders.count());
	responseHeadersReceived->setColumnCount(2);	
	responseHeadersReceived->setHorizontalHeaderLabels(tableLabels);

	for (int i = 0; i < replyHeaders.count(); ++i)
	{
		QString key = replyHeaders[i].constData();
		QString value = reply->rawHeader(replyHeaders[i]).constData();

		responseHeadersReceived->setItem(i, 0, new QTableWidgetItem(key));
		responseHeadersReceived->setItem(i, 1, new QTableWidgetItem(value));
	}

	responseLayout->show();
}
