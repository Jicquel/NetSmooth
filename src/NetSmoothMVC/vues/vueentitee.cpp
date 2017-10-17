#include "vueentitee.h"

VueEntitee* VueEntitee::labelEnSelection = NULL;// A quoi LabelEnSelection sert? Vincent

VueEntitee::VueEntitee(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    this->setFlag(QGraphicsItem::ItemIsFocusable,true);
    this->setFlag(QGraphicsItem::ItemIsSelectable,true);
    this->ligne=0;
    this->colonne=0;
    this->isDeleted=false;
    this->setZValue(5);
}

VueEntitee::~VueEntitee()
{
}


void VueEntitee::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    if(this->isDeleted)
        return;
    QGraphicsPixmapItem::paint(painter, option, widget);
    VuePrincipale* vp  = VuePrincipale::getInstanceOf();
    string nom = this->getModele()->getNom();

    QPen pen(QColor(0, 0, 0));
    pen.setWidth(10);
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(QColor(255,0,0,100));
    painter->drawText(vp->getLargeurCaseEntiere()*this->colonne+this->pixmap().width()/2-nom.size()*3.5,
                      vp->getHauteurCaseEntiere()*this->ligne+this->pixmap().height(),
                      *(new QString(nom.c_str())));

    vector<Cable*> *c = this->getModele()->getCables();
    for(int i=0 ; i<(int)c->size() ; i++)
        (*c)[i]->getVue()->updatePath();
}

int VueEntitee::getLigneGrille()
{
    return this->ligne;
}

void VueEntitee::setLigneGrille(int l)
{
    this->ligne = l;
}

int VueEntitee::getColGrille()
{
    return this->colonne;
}

void VueEntitee::setColGrille(int c)
{
    this->colonne=c;
}

void VueEntitee::setLabelEnSelection(VueEntitee* label)
{
    VueEntitee::labelEnSelection = label;
}

VueEntitee* VueEntitee::getLabelEnSelection()
{
    return VueEntitee::labelEnSelection;
}

void VueEntitee::moveOnCursor(){
    QPoint viewPoint = VuePrincipale::getInstanceOf()->getView()->mapFromGlobal(QCursor::pos());
    QPointF scenePoint = VuePrincipale::getInstanceOf()->getView()->mapToScene(viewPoint);
    this->scene()->update();

    VuePrincipale::getInstanceOf()->deplacerEntitee(this,
                                                    new QPoint(trunc(scenePoint.x()-this->pixmap().width()/2),
                                                               trunc(scenePoint.y()-this->pixmap().height()/2)));
}

void VueEntitee::detruire()
{
    this->isDeleted=true;
    std::vector<Cable*> cables = *(this->getModele()->getCables());
    for(int i = 0 ; i<(int)cables.size() ; i++)
    {
        Cable* c = cables[i];
        delete(c->getVue());
    }
    delete(this->getModele());

    this->deleteLater();
}

void VueEntitee::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    if (e->modifiers() != Qt::ControlModifier)
    {
        emit(leftClick());
        //QGraphicsItem::mousePressEvent(e);
    }
}

void VueEntitee::mouseMoveEvent(QGraphicsSceneMouseEvent *e)
{

    if (e->buttons() == Qt::LeftButton && e->modifiers() != Qt::ControlModifier)
    {
        emit moveLeftButton();
        //QGraphicsItem::mouseMoveEvent(e);
    }
}

void VueEntitee::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *e)
{
    emit doubleClick();
}

