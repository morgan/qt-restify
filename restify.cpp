#include <QtGui>
#include "restify.h"

Restify::Restify()
{
	optionsGroupBox = new QGroupBox(tr("Options"));

    url = new QInputDialog;
    urlLabel = new QLabel(tr("URL"));

	optionsGroupBoxLayout = new QGridLayout; 
    optionsGroupBoxLayout->addWidget(urlLabel, 0, 0);
    optionsGroupBoxLayout->addWidget(url, 0, 1);
	optionsGroupBox->setLayout(optionsGroupBoxLayout);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(optionsGroupBox);
    setLayout(mainLayout);	

    setWindowTitle(tr("Restify"));
    resize(500, 200);    
}
