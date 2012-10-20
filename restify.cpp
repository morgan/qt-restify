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
	this->_setupLaunchPad();

	requestLayout = new QHBoxLayout;
	requestLayout->addWidget(method);
	requestLayout->addWidget(settings);
	requestLayout->addWidget(url);
	requestLayout->addWidget(submit);

	layout = new QVBoxLayout;
	layout->setAlignment(Qt::AlignTop);
	layout->addLayout(requestLayout);
	layout->addWidget(configLayout);
	layout->addWidget(message);
	layout->addWidget(responseLayout);
	layout->addWidget(launchPad);

	setLayout(layout);

	setWindowTitle(tr("Restify"));
	resize(800, 500);
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

	url = new QLineEdit;
	url->setProperty("placeholderText", "http://api.example.com/resource.json?key=value");

	submit = new QPushButton(tr("Request"));
	submit->connect(submit, SIGNAL(clicked()), this, SLOT(_request()));

	settings = new QPushButton(tr("Config"));
	settings->connect(settings, SIGNAL(clicked()), this, SLOT(_toggleConfig()));

	QStringList tableLabels;
	tableLabels << "Name" << "Value";

	configData = new QTableWidget(10, 2);
	configData->setHorizontalHeaderLabels(tableLabels);
	configData->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

	configHeaders = new QTableWidget(10, 2);
	configHeaders->setHorizontalHeaderLabels(tableLabels);
	configHeaders->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

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

	launchPad->hide();
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
	
	highlighter = new Highlighter(responseContent->document());

	responseHeadersReceived = new QTableWidget;
	responseHeadersReceived->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

	responseHeadersSent = new QTableWidget;
	responseHeadersSent->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

	responseLayout = new QTabWidget;
	responseLayout->addTab(responseContent, tr("Response"));
	responseLayout->addTab(responseHeadersReceived, tr("Headers Received"));
	responseLayout->addTab(responseHeadersSent, tr("Headers Sent"));
	responseLayout->hide();

	message = new QLabel(this);
	message->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	message->setMargin(10);
	message->setWordWrap(true);
	message->hide();
}

/**
 * Setup launchpad
 *
 * @access	private
 * @return	void
 */
void Restify::_setupLaunchPad()
{
	launchPad_Vimeo = new QLabel(this);
	launchPad_Vimeo->setOpenExternalLinks(true);
	launchPad_Vimeo->setTextFormat(Qt::RichText);
	launchPad_Vimeo->setText("<a href=\"http://vimeo.com/26659171\"><img src=\"media/launchpad_vimeo.png\"></a>");

	launchPad_GitHub = new QLabel(this);
	launchPad_GitHub->setOpenExternalLinks(true);
	launchPad_GitHub->setTextFormat(Qt::RichText);
	launchPad_GitHub->setText("<a href=\"https://github.com/morgan/qt-restify\"><img src=\"media/launchpad_github.png\"></a>");

	launchPad_Twitter = new QLabel(this);
	launchPad_Twitter->setOpenExternalLinks(true);
	launchPad_Twitter->setTextFormat(Qt::RichText);
	launchPad_Twitter->setText("<a href=\"https://twitter.com/michealmorgan\"><img src=\"media/launchpad_twitter.png\"></a>");

	launchPad_Samples = new QLabel(this);
	launchPad_Samples->setTextFormat(Qt::RichText);
	launchPad_Samples->setText("<img src=\"media/launchpad_samples.png\">");

	launchPad_Samples_1 = new QLabel(this);
	launchPad_Samples_1->setText("<a href=\"http://feeds.feedburner.com/KohanaModules?format=xml\">http://feeds.feedburner.com/KohanaModules?format=xml</a>");

	launchPad_Samples_2 = new QLabel(this);
	launchPad_Samples_2->setText("<a href=\"http://api.flickr.com/services/feeds/photos_public.gne?tags=cat&format=json\">http://api.flickr.com/services/feeds/photos_public.gne?tags=cat...</a>");

	launchPad_Samples_3 = new QLabel(this);
	launchPad_Samples_3->setText("<a href=\"http://restify.io/test\">http://restify.io/test</a>");

	connect(launchPad_Samples_1, SIGNAL(linkActivated(const QString&)), this, SLOT(_request_sample(const QString&)));
	connect(launchPad_Samples_2, SIGNAL(linkActivated(const QString&)), this, SLOT(_request_sample(const QString&)));
	connect(launchPad_Samples_3, SIGNAL(linkActivated(const QString&)), this, SLOT(_request_sample(const QString&)));

	launchPadLayout = new QVBoxLayout;
	launchPadLayout->addWidget(launchPad_Vimeo);	
	launchPadLayout->addWidget(launchPad_GitHub);
	launchPadLayout->addWidget(launchPad_Twitter);
	launchPadLayout->addWidget(launchPad_Samples);
	launchPadLayout->addWidget(launchPad_Samples_1);
	launchPadLayout->addWidget(launchPad_Samples_2);
	launchPadLayout->addWidget(launchPad_Samples_3);

	launchPad = new QWidget;
	launchPad->setLayout(launchPadLayout);
}

/**
 * Handle clicking of a launchpad sample
 *
 * @access	private
 * @param	const QString&
 * @return	void
 */
void Restify::_request_sample(const QString& link)
{
	url->setText(link);

	this->_request();
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
	launchPad->hide();

	if ( ! reply->error())
	{
		message->hide();

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
	else
	{
		message->setText("There was an error processing your request. " + reply->errorString());
		message->show();
	}
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
