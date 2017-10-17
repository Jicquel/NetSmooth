#ifndef VUEROUTESCONTROLEUR_H
#define VUEROUTESCONTROLEUR_H

#include <QObject>
#include <iostream>

class VueRoutesControleur;

#include "vues/vueRoutes.h"

using namespace std;

class VueRoutesControleur : public QObject
{
    Q_OBJECT
public:
    explicit VueRoutesControleur(VueRoutes* vue, QObject *parent = 0);

private:
    VueRoutes* vue;

signals:

public slots:
};

#endif
