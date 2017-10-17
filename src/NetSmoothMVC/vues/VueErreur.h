#ifndef VUEERREUR_H
#define VUEERREUR_H

#include <QWidget>
#include <QLabel>


class VueErreur : public QLabel
{
    Q_OBJECT
public:
    VueErreur(QWidget *parent=0);
    static VueErreur* getInstanceOf();


private:
    static VueErreur* m_instance;
};

#endif
