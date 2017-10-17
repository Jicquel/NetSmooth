#include "vueRoutes.h"

VueRoutes::VueRoutes(QWidget *parent) :
    QGridLayout(parent)
{
    this->m_source = NULL;
    this->routesVersion4 = new QWidget();
    this->routesVersion6 = new QWidget();

    /***SCROLLBAR***/
    QScrollArea *scroll4 = new QScrollArea();
    scroll4->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scroll4->setWidgetResizable(true);
    scroll4->setWidget(routesVersion4);

    QScrollArea *scroll6 = new QScrollArea();
    scroll6->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scroll6->setWidgetResizable(true);
    scroll6->setWidget(routesVersion6);

    this->routesVersion4->setLayout(new QGridLayout());
    this->routesVersion6->setLayout(new QGridLayout());

    this->controleur = new VueRoutesControleur(this);

    QLabel* paramRoute = new QLabel("Paramètres routage : ");

    /*** ROUTES VERSION 4 ***/
    QLabel* v4 = new QLabel("V4 :");
    QLabel* dest4 = new QLabel("destination");
    QLabel* pass4 = new QLabel("passerelle");
    QLabel* inter4 = new QLabel("interface");

    LigneRoute* newLine = new LigneRoute();
    QGridLayout* l = (QGridLayout*)this->routesVersion4->layout();
    l->addWidget(newLine,0,0);

    this->controleur->connect(newLine->getValider(),SIGNAL(clicked(bool)),this,SLOT(addRoute4()));

    this->addWidget(paramRoute,0,0); //!\\ mettre dans vue information pour centrer
    this->addWidget(v4,1,0);
    this->addWidget(dest4,2,0);
    this->addWidget(pass4,2,1);
    this->addWidget(inter4,2,2);

    this->addWidget(scroll4,3,0,1,4);

    /*** ROUTES VERSION 6 ***/
    QLabel* v6 = new QLabel("V6 :");
    QLabel* dest6 = new QLabel("destination");
    QLabel* pass6 = new QLabel("passerelle");
    QLabel* inter6 = new QLabel("interface");

    newLine = new LigneRoute();
    l = (QGridLayout*)this->routesVersion6->layout();
    l->addWidget(newLine,0,0);

    this->controleur->connect(newLine->getValider(),SIGNAL(clicked(bool)),this,SLOT(addRoute6()));

    this->addWidget(v6,4,0);
    this->addWidget(dest6,5,0);
    this->addWidget(pass6,5,1);
    this->addWidget(inter6,5,2);

    this->addWidget(scroll6,6,0,1,4);
}

void VueRoutes::refresh()
{
    this->deleteRoutes();
    this->addRoutes();
}


//delete view of routes version 4 and 6
void VueRoutes::deleteRoutes()
{
    /*** ROUTE VERSION 4 ***/
    QLayoutItem * child;
    QGridLayout* l = (QGridLayout*)this->routesVersion4->layout();
    while((child = l->takeAt(0)) != 0)
    {
        child->widget()->deleteLater();
        delete child;
    }

    /*** ROUTE VERSION 6 ***/
    l = (QGridLayout*)this->routesVersion6->layout();
    while((child = l->takeAt(0)) != 0)
    {
        child->widget()->deleteLater();
        delete child;
    }
}


//add view of routes version 4 and 6
void VueRoutes::addRoutes()
{
    if(VueEntitee::getLabelEnSelection()->getModele()->getType() == TYPE_HUB)
    {

    }
    else
    {
        QGridLayout* l = NULL;
        int numLine = 0;
        std::vector<struct paramRoutage> routeConf;
        LigneRoute* newLine;
        Machine* m = (Machine*)VueEntitee::getLabelEnSelection()->getModele();

        /*** ROUTE VERSION 4 ***/
        routeConf = m->getRouteConfig4();
        l = (QGridLayout*)this->routesVersion4->layout();

        for(numLine=0 ; numLine<(int)routeConf.size() ; numLine++)
        {
            newLine = new LigneRoute();
            const char* interface = routeConf[numLine].interface.c_str();
            const char* destination = routeConf[numLine].destination.c_str();
            const char* passerelle = routeConf[numLine].passerelle.c_str();
            newLine->getEdest()->setText(destination);
            newLine->getEpass()->setText(passerelle);
            newLine->getEinter()->setText(interface);
            newLine->setId(routeConf[numLine].id);
            newLine->bloquer();

            l->addWidget(newLine,numLine,0);
            this->controleur->connect(newLine->getValider(),SIGNAL(clicked(bool)),this,SLOT(deleteRoute4()));
        }

        newLine = new LigneRoute();
        l->addWidget(newLine,numLine,0);
        this->controleur->connect(newLine->getValider(),SIGNAL(clicked(bool)),this,SLOT(addRoute4()));


        /*** ROUTE VERSION 6 ***/
        routeConf = m->getRouteConfig6();
        l = (QGridLayout*)this->routesVersion6->layout();

        for(numLine=0 ; numLine<(int)routeConf.size() ; numLine++)
        {
            newLine = new LigneRoute();
            const char* interface = routeConf[numLine].interface.c_str();
            const char* destination = routeConf[numLine].destination.c_str();
            const char* passerelle = routeConf[numLine].passerelle.c_str();
            newLine->getEdest()->setText(destination);
            newLine->getEpass()->setText(passerelle);
            newLine->getEinter()->setText(interface);
            newLine->setId(routeConf[numLine].id);
            newLine->bloquer();

            l->addWidget(newLine,numLine,0);
            this->controleur->connect(newLine->getValider(),SIGNAL(clicked(bool)),this,SLOT(deleteRoute6()));
        }

        newLine = new LigneRoute();
        l->addWidget(newLine,numLine,0);
        this->controleur->connect(newLine->getValider(),SIGNAL(clicked(bool)),this,SLOT(addRoute6()));

    }
}

void VueRoutes::deleteRoute4()
{
    QPushButton* b = qobject_cast<QPushButton*>(sender());
    LigneRoute* parent = (LigneRoute*)b->parentWidget();

    if(VueEntitee::getLabelEnSelection()->getModele()->getType()!=TYPE_HUB)
    {
        Machine* m = (Machine*)VueEntitee::getLabelEnSelection()->getModele();
        std::cout << "id : " << parent->getId() << std::endl;
        m->removeParamRoute4(parent->getId());
    }

    this->refresh();

    VueEntitee* ve = VueEntitee::getLabelEnSelection();
    ve->getModele()->majIpContainer();
    ve->getModele()->majRouteContainer();
}

void VueRoutes::addRoute4()
{
    if (VueEntitee::getLabelEnSelection() != NULL)
    {
        std::cout << "addRoute" << std::endl;
        QPushButton* b = qobject_cast<QPushButton*>(sender());
        LigneRoute* parent = (LigneRoute*)b->parentWidget();

        if(VueEntitee::getLabelEnSelection()->getModele()->getType()!=TYPE_HUB)
        {
            Machine* m = (Machine*)VueEntitee::getLabelEnSelection()->getModele();
            struct paramRoutage route = {m->getNewIdRoute4(),
                                parent->getEinter()->toPlainText().toStdString(),
                                parent->getEdest()->toPlainText().toStdString(),
                                parent->getEpass()->toPlainText().toStdString()};

            m->addRouteConfig4(route);
            m->appliquerParamRoutage4();
        }
        this->refresh();
    }

    VueEntitee* ve = VueEntitee::getLabelEnSelection();
    ve->getModele()->majIpContainer();
    ve->getModele()->majRouteContainer();
}

void VueRoutes::deleteRoute6()
{
    QPushButton* b = qobject_cast<QPushButton*>(sender());
    LigneRoute* parent = (LigneRoute*)b->parentWidget();

    if(VueEntitee::getLabelEnSelection()->getModele()->getType()!=TYPE_HUB)
    {
        Machine* m = (Machine*)VueEntitee::getLabelEnSelection()->getModele();
        m->removeParamRoute6(parent->getId());
    }

    this->refresh();

    VueEntitee* ve = VueEntitee::getLabelEnSelection();
    ve->getModele()->majIpContainer();
    ve->getModele()->majRouteContainer();
}

void VueRoutes::addRoute6()
{
    if (VueEntitee::getLabelEnSelection() != NULL)
    {
        QPushButton* b = qobject_cast<QPushButton*>(sender());
        LigneRoute* parent = (LigneRoute*)b->parentWidget();

        if(VueEntitee::getLabelEnSelection()->getModele()->getType()!=TYPE_HUB)
        {
            Machine* m = (Machine*)VueEntitee::getLabelEnSelection()->getModele();
            struct paramRoutage route = {m->getNewIdRoute4(),
                                parent->getEinter()->toPlainText().toStdString(),
                                parent->getEdest()->toPlainText().toStdString(),
                                parent->getEpass()->toPlainText().toStdString()};

            m->addRouteConfig6(route);
            m->appliquerParamRoutage6();
        }
        this->refresh();
    }

    VueEntitee* ve = VueEntitee::getLabelEnSelection();
    ve->getModele()->majIpContainer();
    ve->getModele()->majRouteContainer();
}
