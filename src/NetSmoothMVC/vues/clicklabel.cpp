#include "clicklabel.h"
#include "vueprincipale.h"

ClickLabel* ClickLabel::LabelEnSelection = NULL;

ClickLabel::ClickLabel(QLabel *parent) : QLabel(parent)
{

}

void ClickLabel::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        ClickLabel::setLabelEnSelection(this);
    }
}

void ClickLabel::mouseMoveEvent(QMouseEvent *e)
{
    QWidget* vp=VuePrincipale::getwidget();
    QWidget* vq=vp->parentWidget();

    if (e->buttons() == Qt::LeftButton)
    {
        int x = e->globalPos().x()-vp->pos().x()-vq->pos().x();
        int y = e->globalPos().y()-vp->pos().y()-vq->pos().y();
        y-=this->height()/2+35;	/*35 = hauteur bandeau en haut fenetre*/
        x-=this->width()/2;
        this->move(x, y);
        cout << "x:" << x << "y:" << y << endl;
    }

}

void ClickLabel::mouseDoubleClickEvent(QMouseEvent *e)
{
    emit doubleClick();
}

void ClickLabel::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->buttons() == Qt::LeftButton)
        this->move(e->globalPos());
    ClickLabel::setLabelEnSelection(NULL);
    QPalette* palette = new QPalette();
    palette->setColor(QPalette::Background,Qt::white);
    this->setPalette(*palette);
}

void ClickLabel::setLabelEnSelection(ClickLabel* label)
{
    ClickLabel::LabelEnSelection = label;
}

ClickLabel* ClickLabel::getLabelEnSelection()
{
    return LabelEnSelection;
}
