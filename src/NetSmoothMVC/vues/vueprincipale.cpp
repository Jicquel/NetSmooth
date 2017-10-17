#include "vueprincipale.h"

VuePrincipale* VuePrincipale::instance;

QWidget* VuePrincipale::ca = NULL;


VuePrincipale::VuePrincipale(QWidget *parent) : QWidget(parent)
{
    this->setAcceptDrops(true);

    this->largeurCase = LARGEUR_CASE_INI;
    this->hauteurCase = HAUTEUR_CASE_INI;

    this->m_nbrMachine = 0;
    this->m_nbrPasserelle = 0;

    for(int ligne = 0 ; ligne < NB_CASE_Y ; ligne++)
        for(int col = 0 ; col < NB_CASE_X ; col++)
            this->grille[ligne][col] = VIDE;

    this->setMinimumSize(NB_CASE_X*LARGEUR_CASE_MIN,NB_CASE_Y*HAUTEUR_CASE_MIN);
    this->setMaximumSize(NB_CASE_X*LARGEUR_CASE_MAX,NB_CASE_Y*HAUTEUR_CASE_MAX);

    this->m_scene = new QGraphicsScene(this);
    this->m_view = new DragAndDropGraphicsView(m_scene,this);
   this->m_view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    //this->m_view->setTransformationAnchor(QGraphicsView::AnchorViewCenter);

    this->m_vpc = new VuePrincipaleControleur(this);

    this->m_scene->setSceneRect(0,0,NB_CASE_X*LARGEUR_CASE_INI,NB_CASE_Y*HAUTEUR_CASE_INI);
    this->m_scene->setBackgroundBrush(Qt::white);

    this->m_view->show();
    this->ca=this;
    VuePrincipale::instance=this;
}

void VuePrincipale::mousePressEvent(QMouseEvent *e)
{
  if(Selection::getEnSelection()==CABLE){
    //Selection::setEnSelection(SOURIS);
    //VueCable::setPremiereSelection(NULL);
  }
  else if(Selection::getEnSelection()==SUPPRIMER)
  {
  }
  else if (e->buttons() == Qt::LeftButton)
  {
    QPoint p = this->mapFromGlobal(QCursor::pos());
    QPointF scenePoint = this->m_view->mapToScene(p);

    emit clickSouris(*new QPoint(trunc(scenePoint.x()),trunc(scenePoint.y())));
  }
  VueEntitee::setLabelEnSelection(NULL);

}

QWidget* VuePrincipale::getwidget()
{
  return ca;
}

VueEntitee *VuePrincipale::ajoutEntitee(int x, int y, int type)
{
  QPoint* newPos = this->getPosInGrille(*(new QPoint(x, y)));
  VueEntitee* e;
  if(type == TYPE_ORDINATEUR)
  {
        e = new VueMachine();
        new VueMachineControleur((VueMachine*)e);
        e->setOffset(x,y);
        e->setColGrille(newPos->x());
        e->setLigneGrille(newPos->y());
        this->m_scene->addItem(e);
  }
  if(type == TYPE_PASSERELLE)
  {
        e = new VuePasserelle();
        new VuePasserelleControleur((VuePasserelle*)e);
        e->setColGrille(newPos->x());
        e->setLigneGrille(newPos->y());
        e->setOffset(x,y);
        this->m_scene->addItem(e);
  }
  if(type == TYPE_HUB)
  {
    e = new VueHub();
    new VueHubControleur((VueHub*)e);
    e->setColGrille(newPos->x());
    e->setLigneGrille(newPos->y());
    e->setOffset(x,y);
    this->m_scene->addItem(e);
  }

  this->m_view->setScene(this->m_scene);
  this->m_view->show();

  return e;
}

void VuePrincipale::paintEntitee(QPoint m_posSouris)
{
  QPoint* newPos = this->getPosInGrille(m_posSouris);

  if(Selection::getEnSelection() == MACHINE)
  {
          VueMachine* e = new VueMachine();
          new VueMachineControleur(e);
          e->setOffset(newPos->x()*this->largeurCase,newPos->y()*this->hauteurCase);
          this->m_scene->addItem(e);
          e->setColGrille(newPos->x());
          e->setLigneGrille(newPos->y());
  }
  if(Selection::getEnSelection() == PASSERELLE)
  {
          VuePasserelle* e = new VuePasserelle();
          new VuePasserelleControleur(e);
          e->setOffset(newPos->x()*this->largeurCase,newPos->y()*this->hauteurCase);
          this->m_scene->addItem(e);
          e->setColGrille(newPos->x());
          e->setLigneGrille(newPos->y());
  }
  if(Selection::getEnSelection() == HUB)
  {
    VueHub* e = new VueHub();
    new VueHubControleur(e);
    e->setOffset(newPos->x()*this->largeurCase,newPos->y()*this->hauteurCase);
    this->m_scene->addItem(e);
    e->setColGrille(newPos->x());
    e->setLigneGrille(newPos->y());
  }

  this->m_view->setScene(this->m_scene);
  this->m_view->show();

}

QGraphicsScene* VuePrincipale::getScene()
{

  return this->m_scene;
}

DragAndDropGraphicsView* VuePrincipale::getView()
{
  return this->m_view;
}

VuePrincipale* VuePrincipale::getInstanceOf()
{
  if(VuePrincipale::instance == NULL)
    VuePrincipale::instance = new VuePrincipale();
  return VuePrincipale::instance;
}

bool VuePrincipale::deplacerEntitee(VueEntitee *v,QPoint* pos)
{
  QPoint* grillePos = this->getPosInGrille(*pos);
  int largeurCaseEntiere = this->getLargeurCaseEntiere();
  int hauteurCaseEntiere = this->getHauteurCaseEntiere();

  if(this->grille[grillePos->y()][grillePos->x()] == VIDE)
  {
    v->setOffset(grillePos->x()*largeurCaseEntiere,
                 grillePos->y()*hauteurCaseEntiere);
    this->grille[v->getLigneGrille()][v->getColGrille()]= VIDE;

    v->setLigneGrille(grillePos->y());
    v->setColGrille(grillePos->x());
    this->grille[grillePos->y()][grillePos->x()] = OCCUPE;
    return true;
  }
  return false;
}

int VuePrincipale::getHauteurCaseEntiere()
{
  return (int)trunc(this->hauteurCase);
}

int VuePrincipale::getLargeurCaseEntiere()
{
  return (int)trunc(this->largeurCase);
}

void VuePrincipale::setHauteurCase(double h)
{
  this->hauteurCase=h;
}

void VuePrincipale::setLargeurCase(double l)
{
  this->largeurCase=l;
}
QPoint* VuePrincipale::getPosInGrille(QPoint pos)
{
  return new QPoint(pos.x()/this->largeurCase,
                    pos.y()/this->hauteurCase);
}

int VuePrincipale::getNombreOrdinateurs()
{
    return this->m_nbrMachine;
}

void VuePrincipale::setNombreOrdinateurs(int n)
{
    this->m_nbrMachine = n;
}

int VuePrincipale::getNombrePasserelles()
{
    return this->m_nbrPasserelle;
}

void VuePrincipale::setNombrePasserelles(int n)
{
    this->m_nbrPasserelle = n;
}
void VuePrincipale::resizeEvent(QResizeEvent* e)
{
  this->m_view->setMinimumSize(this->width(),this->height());
  this->m_view->setMaximumSize(this->width(),this->height());
}

