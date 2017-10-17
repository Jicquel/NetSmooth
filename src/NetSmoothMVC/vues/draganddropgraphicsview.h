#ifndef DRAGANDDROPGRAPHICSVIEW_H
#define DRAGANDDROPGRAPHICSVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QWheelEvent>
#include <QtGui>
#include <QLabel>
#include <QScrollBar>

class DragAndDropGraphicsView;

#include "vues/vueprincipale.h"

#include "vues/constantes.h"

class DragAndDropGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit DragAndDropGraphicsView(QGraphicsScene *scene, QWidget *parent = 0);

signals:
    void drop(QPoint pos);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *e);
    void dragMoveEvent(QDragMoveEvent *e);
    void dropEvent(QDropEvent *e);
    void wheelEvent(QWheelEvent *e);

private:
    QGraphicsScene *m_scene;
    QPointF* previousCursorPosition;

public slots:
};

#endif // DRAGANDDROPGRAPHICSVIEW_H
