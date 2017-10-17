#ifndef VUEINFORMATION_H
#define VUEINFORMATION_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QTextEdit>
#include <QLabel>
#include <QCoreApplication>
#include <QGraphicsPixmapItem>

class VueInformation;

#include "vues/vueRoutes.h"
#include "vues/VueIP.h"


class VueInformation : public QWidget
{
        Q_OBJECT
public:
        static VueInformation* getInstanceOf();
        void refresh(QGraphicsPixmapItem* s);
        void setSource(QGraphicsPixmapItem* s);
        QGraphicsPixmapItem* getSource();
        void vider();
        void setAllumer(QPushButton*);
        QPushButton* getAllumer();
        void allumer();
        void activerBoutonAllumer(bool b);

        VueRoutes* getRoutes();
        void setRoutes(VueRoutes* v);

        VueIP* getVueIP(void);
        void setVueIP(VueIP* v);
        void addNewInfos();
        Entitee* getModele();
        std::string getName();
        bool getEtatBoutonAllumer();
        void setEtatBoutonAllumer(bool etat);

private:
        static VueInformation* instance;
        explicit VueInformation(QWidget *parent = 0);
        QGridLayout* m_layout;
        QGraphicsPixmapItem* m_source;
        QPushButton* m_allumer;
        VueRoutes* m_routes;
        VueIP* m_vueIP;
        QTextEdit* m_name;
        bool m_etatBoutonAllumer;

signals:
        void refresh();

public slots:
};

#endif // VUEINFORMATION_H
