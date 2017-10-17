#ifndef SELECTION_H
#define SELECTION_H

#include <QWidget>
#include <QtGui>
#include <iostream>
#include <QPainter>

class Selection;

#include "vues/selectlabel.h"
#include "controleurs/selectioncontroleur.h"

class Selection : public QWidget
{
    Q_OBJECT
public:
    explicit Selection(QWidget *parent = 0);
    static int getEnSelection();
    static void setEnSelection(int es);
    static SelectLabel** getSelections();
    static QPixmap* getPixmaps();

private:
    //void setButtonStyle(SelectLabel* b, std::string imgPath);
    static int m_enSelection;
    static SelectLabel** m_selections;
    static QPixmap* m_pixmaps;
    SelectionControleur *m_sc;

protected:
    void dragEnterEvent(QDragEnterEvent *e);
    void dragMoveEvent(QDragMoveEvent *e);
    void mousePressEvent(QMouseEvent *e);

signals:
    void click(SelectLabel*);
};

#endif // SELECTION_H
