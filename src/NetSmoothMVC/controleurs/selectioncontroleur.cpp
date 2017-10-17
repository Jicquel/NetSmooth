#include "selectioncontroleur.h"


SelectionControleur::SelectionControleur(Selection *vue0, QObject *parent) : QObject(parent)
{
        vue = vue0;
        connect(this->vue,SIGNAL(click(SelectLabel*)),this,SLOT(changeEnSelection(SelectLabel*)));
}

void SelectionControleur::changeEnSelection(SelectLabel* sl)
{

        QApplication::setOverrideCursor(Qt::ArrowCursor);
        if(sl->getName() == "souris")
        {
                Selection::setEnSelection(SOURIS);
        }
        if(sl->getName() == "machine")
        {
                Selection::setEnSelection(MACHINE);
        }
        if(sl->getName() == "passerelle")
        {
                Selection::setEnSelection(PASSERELLE);
        }
        if(sl->getName() == "hub")
        {
                Selection::setEnSelection(HUB);
        }
        if(sl->getName() == "cable")
        {
                Selection::setEnSelection(CABLE);
        }
        if(sl->getName() == "supprimer")
        {
                Selection::setEnSelection(SUPPRIMER);
                QApplication::setOverrideCursor(Qt::CrossCursor);
        }
}

