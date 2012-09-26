#include "restify.h"

Restify::Restify()
{
	setupOptions();

	requestLayout = new QHBoxLayout;
	requestLayout->addWidget(method);
	requestLayout->addWidget(url);
	requestLayout->addWidget(submit);

	setLayout(requestLayout);

	setWindowTitle(tr("Restify"));
	resize(800, 50);    
}

void Restify::setupOptions()
{
	method = new QComboBox;
	method->addItem("GET");
	method->addItem("POST");
	method->addItem("PUT");
	method->addItem("PATCH");
	method->addItem("DELETE");

	url = new QLineEdit;
	url->setProperty("placeholderText", "http://api.example.com/resource.json?key=value");

	submit = new QPushButton("Request");
}
