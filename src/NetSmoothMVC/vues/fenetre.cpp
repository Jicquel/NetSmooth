#include "vues/fenetre.h"

Fenetre::Fenetre(QWidget *parent) : QMainWindow(parent)
{
        QWidget *w = new QWidget();
        QToolBar* tb = new QToolBar();
        QAction* afichier = new QAction(NULL);
        QMenu* mfichier = new QMenu();
        QAction* aopt = new QAction(NULL);
        QMenu* mopt = new QMenu();
        Selection *s = new Selection();
        VuePrincipale *vp = VuePrincipale::getInstanceOf();
        QGridLayout *g = new QGridLayout();
        VueInformation *vi= VueInformation::getInstanceOf();
        VueErreur *ve = VueErreur::getInstanceOf();

        /*this->setStyleSheet("QDockWidget {background: black;}");

    tb->setStyleSheet("background-color: rgb(35,35,35); color: white");

    w->setStyleSheet("QWidget { background-color: rgb(35,35,35); color: white;}"
         "QPushButton { background-color: rgb(70,70,70); border-radius: 5px; padding: 2px;}"
         "QPushButton:pressed { background-color: rgb(50,50,50);}"
         "QTextEdit { background-color: rgb(220,220,220); color: black; border-radius: 3px; background-attachment:fixed}"
         "QScrollBar {background:none;}");

    vp->setStyleSheet("QWidget {background-color: rgb(200,200,200);}"
         "QScrollBar {background:none;}");

    ve->setStyleSheet("QLabel { color: #FF4040 }");*/

        this->show();

        QToolButton* toolButtonOpt = new QToolButton();
        QToolButton* toolButtonFile = new QToolButton();

        g->addWidget(s,0,0,0);
        g->addWidget(vp,0,1,0);
        g->addWidget(vi,0,2,0);
        g->addWidget(ve,1,1,0);
        w->setLayout(g);

        //OPTIONS
        mopt->addAction("Allumer tout",this,SLOT(startAll()));
        mopt->addAction("Éteindre tout",this,SLOT(stopAll()));
        toolButtonOpt->setMenu(mopt);
        toolButtonOpt->setPopupMode(QToolButton::InstantPopup);
        toolButtonOpt->setText("Options ");
        tb->addWidget(toolButtonOpt);

        //FILE
        mfichier->addAction("Sauvegarder",this,SLOT(save()));
        mfichier->addAction("Charger",this,SLOT(load()));
        mfichier->addAction("Quitter",this,SLOT(quit()));
        toolButtonFile->setMenu(mfichier);
        toolButtonFile->setPopupMode(QToolButton::InstantPopup);
        toolButtonFile->setText("Fichier ");
        tb->addWidget(toolButtonFile);

        this->setCentralWidget(w);
        this->addToolBar(tb);
}

void Fenetre::startAll()
{
        ElementListeChainee* ordis = DataBase::getListOrdinateur();
        ElementListeChainee* passes = DataBase::getListPasserelle();
        ElementListeChainee* hubs = DataBase::getListHub();

        QPixmap* img = new QPixmap();


        while (ordis != NULL)
        {
                if (ordis->entitee->getVue()->etat == false)
                {
                        ordis->entitee->getVue()->etat = true;
                        ordis->entitee->getVue()->getModele()->launchEntitee();
                        img->load(Fenetre::getImagesPath()+"ordinateuron.png");
                        *img = img->scaled(130,130);
                        ordis->entitee->getVue()->setPixmap(*img);
                }
                ordis = ordis->nextElement;
                while (passes != NULL)
                {
                        if (passes->entitee->getVue()->etat == false)
                        {
                                passes->entitee->getVue()->etat = true;
                                passes->entitee->getVue()->getModele()->launchEntitee();
                                img->load(Fenetre::getImagesPath()+"passerelleon.png");
                                *img = img->scaled(130,130);
                                passes->entitee->getVue()->setPixmap(*img);
                        }
                        passes = passes->nextElement;
                }
                while (hubs != NULL)
                {
                        if (hubs->entitee->getVue()->etat == false)
                        {
                                hubs->entitee->getVue()->etat = true;
                                hubs->entitee->getVue()->getModele()->launchEntitee();
                                img->load(Fenetre::getImagesPath()+"Hubon.png");
                                *img = img->scaled(130,130);
                                hubs->entitee->getVue()->setPixmap(*img);
                        }
                        hubs = hubs->nextElement;
                }
        }
}

void Fenetre::stopAll()
{
        ElementListeChainee* ordis = DataBase::getListOrdinateur();
        ElementListeChainee* passes = DataBase::getListPasserelle();
        ElementListeChainee* hubs = DataBase::getListHub();

        QPixmap* img = new QPixmap();


        while (ordis != NULL)
        {
                if (ordis->entitee->getVue()->etat == true)
                {
                        ordis->entitee->getVue()->etat = false;
                        ordis->entitee->getVue()->getModele()->stopEntitee();
                        img->load(Fenetre::getImagesPath()+"ordinateuroff.png");
                        *img = img->scaled(130,130);
                        ordis->entitee->getVue()->setPixmap(*img);
                }
                ordis = ordis->nextElement;
        }
        while (passes != NULL)
        {
                if (passes->entitee->getVue()->etat == true)
                {
                        passes->entitee->getVue()->etat = false;
                        passes->entitee->getVue()->getModele()->stopEntitee();
                        img->load(Fenetre::getImagesPath()+"passerelleoff.png");
                        *img = img->scaled(130,130);
                        passes->entitee->getVue()->setPixmap(*img);
                }
                passes = passes->nextElement;
        }
        while (hubs != NULL)
        {
                if (hubs->entitee->getVue()->etat == true)
                {
                        hubs->entitee->getVue()->etat = false;
                        hubs->entitee->getVue()->getModele()->stopEntitee();
                        img->load(Fenetre::getImagesPath()+"Huboff.png");
                        *img = img->scaled(130,130);
                        hubs->entitee->getVue()->setPixmap(*img);
                }
                hubs = hubs->nextElement;
        }
}

void Fenetre::save()
{
        QFileDialog* fl = new QFileDialog();
        fl->setDefaultSuffix(*(new QString("ns")));
        fl->setDirectory(*(new QString("../saves")));
        fl->setViewMode(QFileDialog::List);
        fl->setAcceptMode(QFileDialog::AcceptSave);
        QString bob = fl->getSaveFileName();
        Save::save_session(bob.toStdString());
}

void Fenetre::load()
{
        QFileDialog* fl = new QFileDialog();
        fl->setDirectory(*(new QString("../saves")));
        fl->setViewMode(QFileDialog::List);
        fl->setAcceptMode(QFileDialog::AcceptOpen);
        QString bob = fl->getOpenFileName();
        Save::load_session(bob.toStdString());
}

void Fenetre::quit()
{
        ElementListeChainee* ordis = DataBase::getListOrdinateur();
        ElementListeChainee* passes = DataBase::getListPasserelle();
        ElementListeChainee* hubs = DataBase::getListHub();

        while (ordis != NULL)
        {
                ordis->entitee->stopEntitee();
                ordis = ordis->nextElement;
        }
        while (passes != NULL)
        {
                passes->entitee->stopEntitee();
                passes = passes->nextElement;
        }
        while (hubs != NULL)
        {
                hubs->entitee->stopEntitee();
                hubs = hubs->nextElement;
        }
        exit(0);
}

void Fenetre::closeEvent(QCloseEvent *e)
{
        ElementListeChainee* ordis = DataBase::getListOrdinateur();
        ElementListeChainee* passes = DataBase::getListPasserelle();
        ElementListeChainee* hubs = DataBase::getListHub();

        while (ordis != NULL)
        {
                ordis->entitee->deleteAllParams();
                ordis->entitee->stopEntitee();
                ordis = ordis->nextElement;
        }
        while (passes != NULL)
        {
                passes->entitee->deleteAllParams();
                passes->entitee->stopEntitee();
                passes = passes->nextElement;
        }
        while (hubs != NULL)
        {
                hubs->entitee->deleteAllParams();
                hubs->entitee->stopEntitee();
                hubs = hubs->nextElement;
        }
}

QString Fenetre::getImagesPath()
{
        QString path = "/usr/share/NetSmooth/images/";
        return path;
}
