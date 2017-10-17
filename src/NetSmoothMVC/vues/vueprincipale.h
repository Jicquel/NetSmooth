#ifndef VUEPRINCIPALE_H
#define VUEPRINCIPALE_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPen>
#include <iostream>
#include <QMouseEvent>
#include <QKeyEvent>
#include <math.h>

class VuePrincipale;

#include "vues/vueentitee.h"
#include "vues/draganddropgraphicsview.h"
#include "controleurs/vueentiteecontroleur.h"
#include "controleurs/vueprincipalecontroleur.h"

#include "vues/constantes.h"


class VuePrincipale : public QWidget
{
    Q_OBJECT
public:
    static QWidget* getwidget();
    void paintEntitee(QPoint posSouris);
    VueEntitee *ajoutEntitee(int x, int y, int type);
    QGraphicsScene* getScene();
    DragAndDropGraphicsView* getView();
    static VuePrincipale* getInstanceOf();
    bool deplacerEntitee(VueEntitee* v,QPoint* posRelativeToparent);

    int getHauteurCaseEntiere();
    int getLargeurCaseEntiere();

    void setLargeurCase(double l);
    void setHauteurCase(double h);

    int getNombreOrdinateurs();
    void setNombreOrdinateurs(int);

    int getNombrePasserelles();
    void setNombrePasserelles(int);

protected:
    void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *e);

private:
    static QWidget* ca;
    QGraphicsScene *m_scene;
    DragAndDropGraphicsView *m_view;

    VuePrincipaleControleur *m_vpc;
    static VuePrincipale* instance;
    explicit VuePrincipale(QWidget *parent = 0);

    int grille[NB_CASE_Y][NB_CASE_X];
    double largeurCase;
    double hauteurCase;
    QPoint* getPosInGrille(QPoint pos);

    int m_nbrMachine;
    int m_nbrPasserelle;



signals:
    void clickSouris(QPoint pos);

};

#endif // VUEPRINCIPALE_H
