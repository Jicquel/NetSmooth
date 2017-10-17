#include "selection.h"

using namespace std;

Selection::Selection(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(150,600);

    m_selections = new SelectLabel*[6];
    m_pixmaps = new QPixmap[6];

    m_selections[SELECT_SOURIS] = new SelectLabel(tr("curseur"),tr("souris"),this);
    m_selections[SELECT_SOURIS]->move(10,10);
    m_pixmaps[SELECT_SOURIS] = *m_selections[SELECT_SOURIS]->pixmap();
    m_selections[SELECT_MACHINE] = new SelectLabel(tr("ordinateuroff"),tr("machine"),this);
    m_selections[SELECT_MACHINE]->move(10,100);
    m_pixmaps[SELECT_MACHINE] = *m_selections[SELECT_MACHINE]->pixmap();
    m_selections[SELECT_PASSERELLE] = new SelectLabel(tr("passerelleoff"),tr("passerelle"),this);
    m_selections[SELECT_PASSERELLE]->move(10,190);
    m_pixmaps[SELECT_PASSERELLE] = *m_selections[SELECT_PASSERELLE]->pixmap();
    m_selections[SELECT_HUB] = new SelectLabel(tr("Huboff"),tr("hub"),this);
    m_selections[SELECT_HUB]->move(10,280);
    m_pixmaps[SELECT_HUB] = *m_selections[SELECT_HUB]->pixmap();
    m_selections[SELECT_CABLE] = new SelectLabel(tr("cable"),tr("cable"),this);
    m_selections[SELECT_CABLE]->move(10,370);
    m_pixmaps[SELECT_CABLE] = *m_selections[SELECT_CABLE]->pixmap();
    m_selections[SELECT_SUPPRIMER] = new SelectLabel(tr("croix"),tr("supprimer"),this);
    m_selections[SELECT_SUPPRIMER]->move(10,460);
    m_pixmaps[SELECT_SUPPRIMER] = *m_selections[SELECT_SUPPRIMER]->pixmap();

    this->m_sc = new SelectionControleur(this);

    this->setEnSelection(SOURIS);
}

void Selection::dragEnterEvent(QDragEnterEvent *e)
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

void Selection::dragMoveEvent(QDragMoveEvent *e)
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

void Selection::mousePressEvent(QMouseEvent *e)
{
    SelectLabel *child = static_cast<SelectLabel*>(childAt(e->pos()));
    if (!child)
        return;

    emit click(child);
    if (child->getName() == "souris" || child->getName() == "supprimer" || child->getName() == "cable")
        return;
    QPixmap pix = *child->pixmap();
    QByteArray itemData;
    QDataStream dataStream(&itemData,QIODevice::WriteOnly);
    dataStream << pix << QPoint(e->pos() - child->pos());

    QMimeData *mimeData = new QMimeData();
    mimeData->setData("application/x-dnditemdata", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pix);
    drag->setHotSpot(e->pos() - child->pos());

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction)
        child->close();
    else
        child->show();
}

int Selection::getEnSelection()
{
    return m_enSelection;
}

SelectLabel** Selection::getSelections()
{
    return m_selections;
}

QPixmap* Selection::getPixmaps()
{
    return m_pixmaps;
}

void Selection::setEnSelection(int es)
{

    QPixmap pixmap;
    QPainter painter;

    SelectLabel** tmp = Selection::getSelections();
    QPixmap* pix = Selection::getPixmaps();
    Selection::m_enSelection = es;

    for (int i=0;i<6;i++)
    {
        tmp[i]->setPixmap(pix[i]);
    }

    if(Selection::m_enSelection==SOURIS)
    {
        pixmap = pix[SELECT_SOURIS];
        QApplication::setOverrideCursor(Qt::ArrowCursor);
    }
    if(Selection::m_enSelection==MACHINE)
    {
        pixmap = pix[SELECT_MACHINE];
    }
    if(Selection::m_enSelection==PASSERELLE)
    {
        pixmap = pix[SELECT_PASSERELLE];
    }
    if(Selection::m_enSelection==HUB)
    {
        pixmap = pix[SELECT_HUB];
    }
    if(Selection::m_enSelection==CABLE)
    {
        pixmap = pix[SELECT_CABLE];
    }
    if(Selection::m_enSelection==SUPPRIMER)
    {
        pixmap = pix[SELECT_SUPPRIMER];
        QApplication::setOverrideCursor(Qt::CrossCursor);
    }

    painter.begin(&pixmap);
    painter.fillRect(pixmap.rect(),QColor(0,0,50,75));
    painter.end();
    tmp[es]->setPixmap(pixmap);
}
