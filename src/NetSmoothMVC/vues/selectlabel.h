#ifndef SELECTLABEL_H
#define SELECTLABEL_H

#include <QLabel>

class SelectLabel;

#include "fenetre.h"

class SelectLabel : public QLabel
{
    Q_OBJECT
public:
    explicit SelectLabel(QString path, QString name0, QWidget *parent = nullptr);
    explicit SelectLabel(QWidget *parent = nullptr);
    QString getName();

private:
   QString name;
   QPixmap *img;

public slots:
};

#endif // SELECTLABEL_H
