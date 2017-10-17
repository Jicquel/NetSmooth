#ifndef VUECABLE_H
#define VUECABLE_H

#include <iostream>
#include <QWidget>
#include <QGraphicsPathItem>
#include <QGraphicsView>
#include <qpainter.h>

class VueCable;

#include "vueentitee.h"

class VueCable : public QObject, QGraphicsPathItem
{
    Q_OBJECT
public:
    explicit VueCable(VueHub* vh, VueMachine *vm, QGraphicsItem *parent = 0);
    ~VueCable();
    Cable* getModele(void);

    static VueEntitee* getPremiereSelection();
    static void setPremiereSelection(VueEntitee* v);
    void updatePath();


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *e);

private:
    VueHub* m_vuehub = NULL;
    VueMachine* m_vuemac = NULL;
    Cable* m_cable = NULL;
    bool isSeq(int xinit, int yinit, double coef, int x1, int y1, int x2, int y2);
    static VueEntitee* PremiereSelection;//Pour créer cables

signals:
    void deleteCableSignal();


};

#endif // VUECABLE_H
