#include "ligneroute.h"

LigneRoute::LigneRoute(QLabel *parent) : QLabel(parent)
{
    this->setMinimumSize(350,100);
    this->setFixedHeight(35);

    this->valider = new QPushButton();
    this->layout = new QGridLayout();
    this->edest = new QTextEdit();
    this->epass = new QTextEdit();
    this->einter = new QTextEdit();

    this->valider->setText("OK");
    this->valider->setFixedHeight(25);
    this->valider->setFixedWidth(25);
    this->edest->setFixedHeight(25);
    this->epass->setFixedHeight(25);
    this->einter->setFixedHeight(25);

    this->layout->addWidget(edest,0,0);
    this->layout->addWidget(epass,0,1);
    this->layout->addWidget(einter,0,2);
    this->layout->addWidget(valider,0,3);

    this->setLayout(layout);

}

QPushButton* LigneRoute::getValider()
{
    return this->valider;
}

QTextEdit* LigneRoute::getEdest()
{
    return this->edest;
}

QTextEdit* LigneRoute::getEpass()
{
    return this->epass;
}

QTextEdit* LigneRoute::getEinter()
{
    return this->einter;
}

void LigneRoute::bloquer()
{
    this->edest->setReadOnly(true);
    this->epass->setReadOnly(true);
    this->einter->setReadOnly(true);
    this->valider->setText("X");
}

void LigneRoute::debloquer()
{
    this->edest->setReadOnly(false);
    this->epass->setReadOnly(false);
    this->einter->setReadOnly(false);
    this->valider->setText("OK");
}

void LigneRoute::setId(int id)
{
    this->m_id=id;
}

int LigneRoute::getId() const
{
    return this->m_id;
}
