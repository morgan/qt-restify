#include "restify.h"

/**
 * Setup environment
 *
 * @access	public
 */
Restify::Restify()
{
	this->_setupRequest();
	this->_setupResponse();

	requestLayout = new QHBoxLayout;
	requestLayout->addWidget(method);
	requestLayout->addWidget(settings);
	requestLayout->addWidget(url);
	requestLayout->addWidget(submit);

	layout = new QVBoxLayout;
	layout->setAlignment(Qt::AlignTop);
	layout->addLayout(requestLayout);
	layout->addWidget(configLayout);
	layout->addWidget(responseLayout);

	setLayout(layout);

	setWindowTitle(tr("Restify"));
	resize(800, 50);
}

/**
 * Get selected HTTP method
 *
 * @access	private
 * @return	QString
 */
QString Restify::getMethod()
{
	return method->currentText();
}

/**
 * Get user input for URL
 *
 * @access	private
 * @return	QString
 */
QString Restify::getUrl()
{
	return url->text();
}

/**
 * Setup layout for request
 *
 * @access	private
 * @return	void
 */
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

	settings = new QPushButton(tr("Config"));
	settings->connect(settings, SIGNAL(clicked()), this, SLOT(_toggleConfig()));

	QStringList tableLabels;
	tableLabels << "Name" << "Value";

	configData = new QTableWidget(10, 2);
	configData->setHorizontalHeaderLabels(tableLabels);

	configHeaders = new QTableWidget(10, 2);
	configHeaders->setHorizontalHeaderLabels(tableLabels);

	configSettings = new QTextEdit;

	configLayout = new QTabWidget;
	configLayout->addTab(configData, tr("Data"));
	configLayout->addTab(configHeaders, tr("Headers"));
	configLayout->addTab(configSettings, tr("Settings"));
	configLayout->hide();
}

/**
 * Handle toggle configuration layout
 *
 * @access	private
 * @return	void
 */
void Restify::_toggleConfig()
{
	configLayout->isVisible() ? configLayout->hide() : configLayout->show();
}

/**
 * Setup UI for response, hide until needed.
 *
 * @access	private
 * @return	void
 */
void Restify::_setupResponse()
{
	responseContent = new QTextEdit;
	responseContent->setProperty("readOnly", true);

	responseHeadersReceived = new QTableWidget;
	responseHeadersSent = new QTableWidget;

	responseLayout = new QTabWidget;
	responseLayout->addTab(responseContent, tr("Response"));
	responseLayout->addTab(responseHeadersReceived, tr("Headers Received"));
	responseLayout->addTab(responseHeadersSent, tr("Headers Sent"));
	responseLayout->hide();
}

/**
 * Build request and send it
 *
 * @access	private
 * @return	void
 */
void Restify::_request()
{
	networkAccess = new QNetworkAccessManager(this);
	connect(networkAccess, SIGNAL(finished(QNetworkReply*)), this, SLOT(_requestReply(QNetworkReply*)));

	QNetworkRequest networkRequest = QNetworkRequest(QUrl(this->getUrl()));

	for (int i = 0; i < configHeaders->rowCount(); ++i)
	{
		if (configHeaders->item(i, 0) && configHeaders->item(i, 1))
		{
			QString key = configHeaders->item(i, 0)->text();
			QString value = configHeaders->item(i, 1)->text();

			if ( ! key.isEmpty() && ! value.isEmpty())
			{
				networkRequest.setRawHeader(key.toLocal8Bit(), value.toLocal8Bit());
			}
		}
	}

	networkAccess->sendCustomRequest
	(
		networkRequest, 
		QByteArray(this->getMethod().toLatin1())
	);
}

/**
 * Handle request reply
 *
 * @access	private
 * @param	*QNetworkReply
 * @return	void
 */
void Restify::_requestReply(QNetworkReply *reply)
{
	QNetworkRequest request = reply->request();

	QList<QPair<QByteArray, QByteArray> > sentHeadersPaired;
	QList<QByteArray> sentHeaders = request.rawHeaderList();

	// Create pair for `QNetworkRequest` to simulate `QNetworkReply::rawHeaderPairs`
	for (int i = 0; i < sentHeaders.count(); ++i)
		sentHeadersPaired.append(qMakePair(sentHeaders[i], request.rawHeader(sentHeaders[i])));

	this->_setHeaders(sentHeadersPaired, responseHeadersSent);
	this->_setHeaders(reply->rawHeaderPairs(), responseHeadersReceived);

	QByteArray bytes = reply->readAll();
	QString string(bytes); 

	responseContent->setText(bytes);

	responseLayout->show();
}

/**
 * Set QTableWidget data using provided QList
 *
 * @access	private
 * @param	QList
 * @param	QTableWidget
 * @return	void
 */
void Restify::_setHeaders(const QList<QPair<QByteArray, QByteArray> > headers, QTableWidget *table)
{
	QStringList tableLabels;
	tableLabels << "Name" << "Value";

	table->clear();
	table->setRowCount(headers.count());
	table->setColumnCount(2);
	table->setHorizontalHeaderLabels(tableLabels);

	for (int i = 0; i < headers.count(); ++i)
	{
		QPair<QByteArray, QByteArray> pair = headers[i];

		table->setItem(i, 0, new QTableWidgetItem(pair.first.constData()));
		table->setItem(i, 1, new QTableWidgetItem(pair.second.constData()));
	}
}
