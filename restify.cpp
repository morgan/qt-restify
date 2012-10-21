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
	requestLayout->addWidget(loading);

	layout = new QVBoxLayout;
	layout->setAlignment(Qt::AlignTop);
	layout->addLayout(requestLayout);
	layout->addWidget(configLayout);
	layout->addWidget(message);
	layout->addWidget(responseLayout);
	layout->addWidget(launchPad);
	layout->addWidget(gettingStarted);

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
	url->setStyleSheet("QWidget{font-family: Courier;}");

	submit = new QPushButton(tr("Request"));
	submit->connect(submit, SIGNAL(clicked()), this, SLOT(_request()));

	loadingMovie = new QMovie("media/loading.gif");
	loadingMovie->start();

	loading = new QLabel(this);
	loading->setMovie(loadingMovie);
	loading->hide();

	settings = new QLabel(this);
	settings->setTextFormat(Qt::RichText);
	settings->setText("<a href=\"#\"><img src=\"media/gear.png\"></a>");
	connect(settings, SIGNAL(linkActivated(const QString&)), this, SLOT(_toggleConfig()));

	QStringList tableLabels;
	tableLabels << "Name" << "Value";

	configData = new QTableWidget(10, 2);
	configData->setHorizontalHeaderLabels(tableLabels);
	configData->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

	configHeaders = new QTableWidget(10, 2);
	configHeaders->setHorizontalHeaderLabels(tableLabels);
	configHeaders->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

	configLayout = new QTabWidget;
	configLayout->addTab(configData, tr("Data"));
	configLayout->addTab(configHeaders, tr("Headers"));
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
	if (configLayout->isVisible())
	{
		configLayout->hide();

		if ( ! responseLayout->isVisible())
		{
			launchPad->show();
			gettingStarted->hide();
		}
	}
	else
	{
		configLayout->show();
		launchPad->hide();
		gettingStarted->show();
	}
}

/**
 * Handle toggle of launchpad
 *
 * @access	private
 * @return	void
 */
void Restify::_toggleLaunchPad()
{
	if (launchPad->isVisible())
	{
		launchPad->hide();
		gettingStarted->show();
	}
	else
	{
		responseLayout->hide();
		configLayout->hide();
		gettingStarted->hide();
		launchPad->show();
	}
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
	gettingStarted = new QPushButton(tr("Getting Started"));
	gettingStarted->setFixedSize(gettingStarted->sizeHint().width(), gettingStarted->sizeHint().height());
	gettingStarted->hide();
	connect(gettingStarted, SIGNAL(clicked()), this, SLOT(_toggleLaunchPad()));

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

	QString sampleWidgetStyle = "QWidget{background-color: #F1F1F1; padding: 10px;}";
	QString sampleLinkStyle = "style=\"color: #666666;font-size: 11px; font-family: Courier; text-decoration: none;\"";

	launchPad_Samples_1 = new QLabel(this);
	launchPad_Samples_1->setStyleSheet(sampleWidgetStyle);
	launchPad_Samples_1->setText("<a href=\"https://github.com/morgan.atom\" " + sampleLinkStyle + ">https://github.com/morgan.atom</a>");

	launchPad_Samples_2 = new QLabel(this);
	launchPad_Samples_2->setStyleSheet(sampleWidgetStyle);
	launchPad_Samples_2->setText("<a href=\"http://api.flickr.com/services/feeds/photos_public.gne?tags=cat&format=json\" " + sampleLinkStyle + ">http://api.flickr.com/services/feeds/photos_public.gne?tags=cat...</a>");

	launchPad_Samples_3 = new QLabel(this);
	launchPad_Samples_3->setStyleSheet(sampleWidgetStyle);
	launchPad_Samples_3->setText("<a href=\"http://www.npr.org/rss/rss.php?id=1001\" " + sampleLinkStyle + ">http://www.npr.org/rss/rss.php?id=1001</a>");

	connect(launchPad_Samples_1, SIGNAL(linkActivated(const QString&)), this, SLOT(_requestSample(const QString&)));
	connect(launchPad_Samples_2, SIGNAL(linkActivated(const QString&)), this, SLOT(_requestSample(const QString&)));
	connect(launchPad_Samples_3, SIGNAL(linkActivated(const QString&)), this, SLOT(_requestSample(const QString&)));

	launchPadLayout = new QVBoxLayout;
	launchPadLayout->addWidget(launchPad_Vimeo);	
	launchPadLayout->addWidget(launchPad_GitHub);
	launchPadLayout->addWidget(launchPad_Twitter);
	launchPadLayout->addWidget(launchPad_Samples);

	launchPadLayout->addWidget(launchPad_Samples_1);
	launchPadLayout->addWidget(launchPad_Samples_2);
	launchPadLayout->addWidget(launchPad_Samples_3);

	launchPad = new QWidget;
	launchPad->setStyleSheet("QWidget{background-color: #ffffff; margin: 0px 100px 0 100px; }");
	launchPad->setLayout(launchPadLayout);
}

/**
 * Handle clicking of a launchpad sample
 *
 * @access	private
 * @param	const QString&
 * @return	void
 */
void Restify::_requestSample(const QString& link)
{
	url->setText(link);

	launchPad->hide();

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
	submit->hide();
	loading->show();

	launchPad->hide();

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

	loading->hide();
	submit->show();

	gettingStarted->show();	
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
