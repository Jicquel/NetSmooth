#ifndef VUEENTITEE_H
#define VUEENTITEE_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QCoreApplication>
#include <math.h>
#include <lxc/lxccontainer.h>

class VueEntitee;

class VueHub;
class VueMachine;
class VuePasserelle;

#include "modeles/Entitee.h"


class VueEntitee : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    ~VueEntitee();
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    explicit VueEntitee(QGraphicsItem *parent = 0);
    explicit VueEntitee(int x, int y, QGraphicsItem *parent = 0);
    bool etat;

    virtual Entitee* getModele()=0;
    static VueEntitee* getLabelEnSelection();

    int getLigneGrille();
    void setLigneGrille(int l);
    int getColGrille();
    void setColGrille(int c);
    void detruire();

    static void setLabelEnSelection(VueEntitee* label);
    void moveOnCursor();



private:
    static VueEntitee* labelEnSelection;
    int colonne;
    int ligne;
    bool isDeleted;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *e) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *e) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* e) override;

signals:
    void leftClick();
    void rightClick();
    void doubleClick();
    void moveLeftButton();
};

#include "vues/vuemachine.h"
#include "vues/vuepasserelle.h"
#include "vues/vuehub.h"

#endif // VUEENTITEE_H
