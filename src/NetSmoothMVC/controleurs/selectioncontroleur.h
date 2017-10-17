#ifndef SELECTIONCONTROLEUR_H
#define SELECTIONCONTROLEUR_H

#include <QObject>
#include <iostream>

#include <QApplication>
#include <QApplication>
#include <QPainter>
#include <iostream>

class SelectionControleur;

#include "vues/selection.h"
#include "vues/constantes.h"


class SelectionControleur : public QObject
{
    Q_OBJECT
public:
    explicit SelectionControleur(Selection *vue, QObject *parent = 0);

private:
    Selection *vue;

signals:

public slots:
    void changeEnSelection(SelectLabel*);
};

#endif // SELECTIONCONTROLEUR_H
