#ifndef VUEIP_H
#define VUEIP_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QTextEdit>
#include <QLabel>
#include <QLayout>
#include <QTabWidget>

class VueIP;

#include "vues/VueFormulaireIP.h"
#include "controleurs/VueIPControleur.h"

class VueIP : public QWidget
{
    Q_OBJECT
public:
    explicit VueIP(QWidget *parent=0);
    void refresh();
    void setSource(Entitee* e);
    std::vector<VueFormulaireIP*> getFormulairesIP();
void clearLayout(QLayout *layout);

private:
    std::vector<VueFormulaireIP*> m_formulairesIP;
    QGridLayout* m_layout;
    //VueIPControleur* controleur = NULL;


signals:


public slots:
};

#endif
