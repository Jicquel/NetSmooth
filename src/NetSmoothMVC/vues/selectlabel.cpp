#include "selectlabel.h"

SelectLabel::SelectLabel(QString path, QString name0, QWidget *parent) : QLabel(parent)
{
    QString s = Fenetre::getImagesPath()+path;
    img = new QPixmap();
    img->load(s);
    *img = img->scaled(90,90);
    this->setPixmap(*img);
    this->name=name0;
}

SelectLabel::SelectLabel(QWidget *parent) : QLabel(parent)
{}

QString SelectLabel::getName()
{
    return this->name;
}
