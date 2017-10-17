#include "draganddropgraphicsview.h"

DragAndDropGraphicsView::DragAndDropGraphicsView(QGraphicsScene *scene,QWidget *parent) : QGraphicsView(scene, parent)
{
    this->m_scene = scene;
}


void DragAndDropGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if(event->modifiers()==Qt::ControlModifier && event->buttons() == Qt::LeftButton)
    {
        QPointF oldP = mapToScene(this->previousCursorPosition->x(),this->previousCursorPosition->y());
        QPointF newP = mapToScene(event->pos());
        QPointF translation = newP - oldP;

        QScrollBar* hScrollBar = this->horizontalScrollBar();
        QScrollBar* vScrollBar = this->verticalScrollBar();

        int dx = (int)(translation.x()*((hScrollBar->maximum()-hScrollBar->minimum()+hScrollBar->pageStep())/(hScrollBar->pageStep()*COEFF_CTRL_LEFT_CLICK_MOVE)));
        int dy = (int)(translation.y()*((vScrollBar->maximum()-vScrollBar->minimum()+vScrollBar->pageStep())/(vScrollBar->pageStep()*COEFF_CTRL_LEFT_CLICK_MOVE)));

        hScrollBar->setValue(hScrollBar->value()-dx);
        vScrollBar->setValue(vScrollBar->value()-dy);
    }
    else
    {
        QGraphicsView::mouseMoveEvent(event);
    }

    this->previousCursorPosition =  new QPointF(event->x(),event->y());
}


void DragAndDropGraphicsView::wheelEvent(QWheelEvent *e)
{
    int numDegrees = e->delta() / 8;

    //if(e->modifiers()==Qt::ControlModifier)
    //{
        if(numDegrees > 0)
        {
            this->scale(1.1,1.1);

        }
        else
        {
            this->scale(0.9,0.9);
        }
        VuePrincipale::getInstanceOf()->setLargeurCase(this->sceneRect().width()/NB_CASE_X);
        VuePrincipale::getInstanceOf()->setHauteurCase(this->sceneRect().height()/NB_CASE_Y);

    //}
}
void DragAndDropGraphicsView::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasFormat("application/x-dnditemdata"))
    {
        if (e->source() == this)
        {
            e->setDropAction(Qt::MoveAction);
            e->accept();
        }
        else
        {
            e->acceptProposedAction();
        }
    }
    else
    {
        e->ignore();
    }
}

void DragAndDropGraphicsView::dragMoveEvent(QDragMoveEvent *e)
{
    if (e->mimeData()->hasFormat("application/x-dnditemdata"))
    {
        if (e->source() == this)
        {
            e->setDropAction(Qt::MoveAction);
            e->accept();
        }
        else
        {
            e->acceptProposedAction();
        }
    }
    else
    {
        e->ignore();
    }
}

void DragAndDropGraphicsView::dropEvent(QDropEvent *e)
{
    if (e->mimeData()->hasFormat("application/x-dnditemdata"))
    {
        QPoint p = this->mapFromGlobal(QCursor::pos());
        QPointF sceneP = this->mapToScene(p);
        emit(drop(*new QPoint(trunc(sceneP.x()),trunc(sceneP.y()))));
    }
}
