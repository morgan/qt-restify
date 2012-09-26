#include <QtGui>
#include "restify.h"

Restify::Restify()
{
	setupOptions();

	url = new QLineEdit;

	submit = new QPushButton("Request");

	requestLayout = new QHBoxLayout;
	requestLayout->addLayout(methods);
	requestLayout->addWidget(url);
	requestLayout->addWidget(submit);

	setLayout(requestLayout);

	setWindowTitle(tr("Restify"));
	resize(800, 200);    
}

void Restify::setupOptions()
{
	methodGet = new QPushButton(tr("GET"));
	methodGet->setCheckable(true);
	methodGet->setChecked(true);

	methodPost = new QPushButton(tr("POST"));
	methodPost->setCheckable(true);

	methodPut = new QPushButton(tr("PUT"));
	methodPut->setCheckable(true);

	methodDelete = new QPushButton(tr("DELETE"));
	methodDelete->setCheckable(true);

	methodsGroup = new QButtonGroup(this);
	methodsGroup->addButton(methodGet);
	methodsGroup->addButton(methodPost);
	methodsGroup->addButton(methodPut);
	methodsGroup->addButton(methodDelete);
	methodsGroup->setExclusive(true);

	methods = new QHBoxLayout;
	methods->addWidget(methodGet);
	methods->addWidget(methodPost);
	methods->addWidget(methodPut);
	methods->addWidget(methodDelete);
	methods->setSpacing(0);
}
