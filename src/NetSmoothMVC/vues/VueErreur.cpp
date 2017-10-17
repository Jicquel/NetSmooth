#include "VueErreur.h"

VueErreur* VueErreur::m_instance=NULL;

VueErreur::VueErreur(QWidget *parent)
{
    m_instance=this;
}

VueErreur* VueErreur::getInstanceOf()
{
    if(m_instance == NULL)
        m_instance = new VueErreur();
    return m_instance;
}
