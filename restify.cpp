#include <QtGui>
#include "restify.h"

Restify::Restify()
{
	requestGroup = new QGroupBox(tr("Options"));

	url = new QInputDialog;
	urlLabel = new QLabel(tr("URL"));

	requestGroupLayout = new QGridLayout; 
	requestGroupLayout->addWidget(url, 0, 1);
	requestGroupLayout->addWidget(urlLabel, 0, 0);
	requestGroup->setLayout(requestGroupLayout);

	layout = new QVBoxLayout;
	layout->addWidget(requestGroup);
	setLayout(layout);	

	setWindowTitle(tr("Restify"));
	resize(500, 200);    
}
