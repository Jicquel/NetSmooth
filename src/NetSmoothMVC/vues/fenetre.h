#ifndef FENETRE_H
#define FENETRE_H

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QToolBar>
#include <QToolButton>
#include <QMenu>
#include <QFileDialog>
#include <QDockWidget>

class Fenetre;

#include "vues/selection.h"
#include "modeles/DataBase.h"
#include "modeles/Save.h"
#include "vues/vueprincipale.h"
#include "vues/vueinformation.h"
#include "controleurs/vueinformationcontroleur.h"
#include "vues/VueErreur.h"


class Fenetre : public QMainWindow
{
        Q_OBJECT
public:
        explicit Fenetre(QWidget *parent = 0);
        static QString getImagesPath();

private:
        void closeEvent(QCloseEvent *e);

signals:

public slots:
        void save();
        void load();
        void startAll();
        void stopAll();
        void quit();
};

#endif // FENETRE_H
