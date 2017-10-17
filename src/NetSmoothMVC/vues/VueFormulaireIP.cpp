#include "VueFormulaireIP.h"

VueFormulaireIP::VueFormulaireIP(int numInterface, Entitee* modele, QWidget *parent)
        : m_modele(modele),m_numInterface(numInterface),QWidget(parent)
{

    QLabel* labelCable = new QLabel("connecté a :");
    QLabel* labelIpv4 = new QLabel("ipv4 :");
    QLabel* labelIpv6 = new QLabel("ipv6 :");
    QLabel* labelMask = new QLabel("Masque ipv4 :");
    QPushButton* valider = new QPushButton("valider");

    this->m_connexion = new QLabel("none");
    this->m_nomInterface = new QLabel();
    this->m_ipv4 = new QTextEdit();
    this->m_mask = new QTextEdit();
    this->m_ipv6 = new QTextEdit();
    this->m_layout = new QGridLayout();

    this->m_connexion->setFixedHeight(25);
    this->m_ipv4->setFixedHeight(25);
    this->m_mask->setFixedHeight(25);
    this->m_ipv6->setFixedHeight(25);

    this->m_layout->addWidget(labelCable,0,0);
    this->m_layout->addWidget(this->m_connexion,0,1);
    this->m_layout->addWidget(labelIpv4,1,0);
    this->m_layout->addWidget(this->m_ipv4,1,1);
    this->m_layout->addWidget(labelMask,2,0);
    this->m_layout->addWidget(this->m_mask,2,1);
    this->m_layout->addWidget(labelIpv6,3,0);
    this->m_layout->addWidget(this->m_ipv6,3,1);
    this->m_layout->addWidget(valider,4,2);

    this->setLayout(this->m_layout);

    new VueFormulaireIPControleur(this,valider);
}

Entitee* VueFormulaireIP::getModele()
{
    return this->m_modele;
}

void VueFormulaireIP::setModele(Entitee* e)
{
    this->m_modele = e;
}

void VueFormulaireIP::refresh()
{
    if(this->m_modele == NULL || this->m_numInterface > (int)this->m_modele->getIpConfig().size())
        perror("VueFormulaireIP refresh");
    else
    {
        struct paramIp* ip = this->m_modele->getIpConfig()[this->m_numInterface];


        vector<Cable*>* listCable=this->getModele()->getCables();

        for(int i=0 ; i<(int)listCable->size() ; i++)
                if((*listCable)[i]->getPort() == this->m_numInterface)
                {
                    this->m_connexion->setText(QString::fromStdString((*listCable)[i]->getHub()->getNom()));
                    break;
                }

        this->m_nomInterface->setText(QString::fromStdString(ip->interface));
        this->m_ipv4->setText(QString::fromStdString(ip->ipv4));
        this->m_mask->setText(QString::fromStdString(ip->maskv4));
        this->m_ipv6->setText(QString::fromStdString(ip->ipv6));
    }
}

void VueFormulaireIP::appliquerModification()
{

    if(this->m_modele == NULL || this->m_numInterface > (int)this->m_modele->getIpConfig().size())
        perror("VueFormulaireIP appliquerModification");
    else
    {
        /*
        struct paramIp* ip = this->m_modele->getIpConfig()[this->m_numInterface];

        ip->ipv4 = this->m_ipv4->toPlainText().toStdString();
        ip->maskv4 = this->m_mask->toPlainText().toStdString();
        ip->ipv6 = this->m_ipv6->toPlainText().toStdString();
        */
        struct paramIp* ip = new paramIp;

        std::cout << "interface = " << this->m_numInterface << std::endl;
        std::stringstream* ss = new std::stringstream();
        (*ss) << "eth" << this->m_numInterface;
        ip->interface = ss->str();
        ip->ipv4 = this->m_ipv4->toPlainText().toStdString();
        ip->maskv4 = this->m_mask->toPlainText().toStdString();
        ip->ipv6 = this->m_ipv6->toPlainText().toStdString();

        this->m_modele->setIpConfig(ip);

        this->m_modele->appliquerParamIp();

    }

}





































