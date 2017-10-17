#include "vueinformation.h"

VueInformation* VueInformation::instance = NULL;

VueInformation* VueInformation::getInstanceOf()
{
    if(VueInformation::instance==NULL)
        VueInformation::instance=new VueInformation();
    return VueInformation::instance;
}

VueInformation::VueInformation(QWidget *parent) : QWidget(parent)
{
    this->setBaseSize(400,500);
    this->setMaximumWidth(500);

    this->m_layout = new QGridLayout();

    m_name = new QTextEdit();
    QPushButton* okName = new QPushButton(*(new QString("OK")));
    m_name->setFixedHeight(25);

    this->m_routes = new VueRoutes();

    this->m_vueIP = new VueIP();

    this->m_layout->addWidget(m_name, 0, 0, 1, 1);
    this->m_layout->addWidget(okName, 0, 1, 1, 1);
    this->m_layout->addWidget(this->m_vueIP, 1, 0, 1, 2);
    this->m_layout->addLayout(m_routes,2,0, 1, 2);

    this->m_allumer = new QPushButton("Allumer");
    QPushButton* rafraichir = new QPushButton("Rafraichir");

    QGridLayout* buttons = new QGridLayout();
    buttons->addWidget(rafraichir, 0, 0, Qt::AlignHCenter);
    buttons->addWidget(m_allumer,0,1,Qt::AlignHCenter);
    this->m_layout->addLayout(buttons,3, 0);

    this->setLayout(this->m_layout);
    new VueInformationControleur(this, m_allumer, rafraichir, okName);

    this->m_etatBoutonAllumer=true;
}

bool VueInformation::getEtatBoutonAllumer()
{
    return this->m_etatBoutonAllumer;
}

void VueInformation::setEtatBoutonAllumer(bool etat)
{
    this->m_etatBoutonAllumer=etat;
}

string VueInformation::getName()
{
    return this->m_name->toPlainText().toStdString();
}

void VueInformation::addNewInfos()
{
    if(VueEntitee::getLabelEnSelection()==NULL)
        return;

    VueEntitee* vueE = VueEntitee::getLabelEnSelection();
    vueE->getModele()->majIpContainer();
    vueE->getModele()->majRouteContainer();
    vueE->getModele()->lireModifContainer();

    this->m_routes->refresh();
    this->m_vueIP->refresh();
}

void VueInformation::refresh(QGraphicsPixmapItem *s)
{
    this->setSource(s);
    this->m_routes->refresh();
    this->m_vueIP->refresh();
    this->m_name->setText(*(new QString(VueEntitee::getLabelEnSelection()->getModele()->getNom().c_str())));
    if(VueEntitee::getLabelEnSelection()->getModele()->getEtatEntitee() == true)
        this->m_allumer->setText(*(new QString("Éteindre")));
    else
        this->m_allumer->setText(*(new QString("Allumer")));
}

void VueInformation::allumer()
{
    setEtatBoutonAllumer(false);

    QPixmap* img = new QPixmap();
    VueEntitee* vueE = VueEntitee::getLabelEnSelection();
    if (vueE == NULL)
    {
        cout << "erreur selection" << endl;
        return;
    }
    if(vueE->getModele()->getType()==TYPE_ORDINATEUR)
    {
        if (vueE->etat == false)
        {
            vueE->etat = true;

            //TODO ajouter les nouvelles ip rentrées

            vueE->getModele()->launchEntitee();
            img->load(Fenetre::getImagesPath()+"ordinateuron.png");
            *img = img->scaled(130,130);
            vueE->setPixmap(*img);
        }
        else
        {
            vueE->etat = false;
            vueE->getModele()->stopEntitee();
            img->load(Fenetre::getImagesPath()+"ordinateuroff.png");
            *img = img->scaled(130,130);
            vueE->setPixmap(*img);
        }
    }
    else if(vueE->getModele()->getType()==TYPE_PASSERELLE)
    {
        if (vueE->etat == false)
        {
            vueE->etat = true;

            //TODO ajouter les nouvelles ip rentrées

            vueE->getModele()->launchEntitee();
            img->load(Fenetre::getImagesPath()+"passerelleon.png");
            *img = img->scaled(130,130);
            vueE->setPixmap(*img);
        }
        else
        {
            vueE->etat = false;
            vueE->getModele()->stopEntitee();
            img->load(Fenetre::getImagesPath()+"passerelleoff.png");
            *img = img->scaled(130,130);
            vueE->setPixmap(*img);
        }
    }
    else if(vueE->getModele()->getType()==TYPE_HUB)
    {
        if (vueE->etat == false)
        {
            vueE->etat = true;
            vueE->getModele()->launchEntitee();
            img->load(Fenetre::getImagesPath()+"Hubon.png");
            *img = img->scaled(130,130);
            vueE->setPixmap(*img);
        }
        else
        {
            vueE->etat = false;
            vueE->getModele()->stopEntitee();
            img->load(Fenetre::getImagesPath()+"Huboff.png");
            *img = img->scaled(130,130);
            vueE->setPixmap(*img);
        }
    }
    if(VueEntitee::getLabelEnSelection()->getModele()->getEtatEntitee() == true)
        this->m_allumer->setText(*(new QString("Eteindre")));
    else
        this->m_allumer->setText(*(new QString("Allumer")));
    setEtatBoutonAllumer(true);
}

void VueInformation::setSource(QGraphicsPixmapItem *s)
{
    this->m_source = s;
}
QGraphicsPixmapItem* VueInformation::getSource()
{
    return this->m_source;
}

void VueInformation::setAllumer(QPushButton * p)
{
    this->m_allumer = p;
}

QPushButton* VueInformation::getAllumer()
{
    return this->m_allumer;
}

VueRoutes* VueInformation::getRoutes()
{
    return this->m_routes;
}

void VueInformation::setRoutes(VueRoutes *v)
{
    this->m_routes = v;
}

VueIP* VueInformation::getVueIP()
{
    return this->m_vueIP;
}

void VueInformation::setVueIP(VueIP *v)
{
    this->m_vueIP = v;
}
