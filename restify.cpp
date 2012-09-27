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

	url = new QLineEdit;
	url->setProperty("placeholderText", "http://api.example.com/resource.json?key=value");

	submit = new QPushButton(tr("Request"));
	submit->connect(submit, SIGNAL(clicked()), this, SLOT(_request()));
}

void Restify::_setupResponse()
{
	responseContent = new QTextEdit;
	responseContent->setProperty("readOnly", true);

	responseLayout = new QTabWidget;
	responseLayout->hide();
	responseLayout->addTab(responseContent, tr("Response"));
}

void Restify::_request()
{
	responseContent->setText(this->getMethod() + " " + this->getUrl());

	responseLayout->show();
}
