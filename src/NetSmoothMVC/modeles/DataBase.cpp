#include "DataBase.h"


int DataBase::m_nbreOrdinateur = 0;
int DataBase::m_nbrePasserelle = 0;
int DataBase::m_nbreHub = 0;

ElementListeChainee* DataBase::m_premierOrdinateur=NULL;
ElementListeChainee* DataBase::m_premierePasserelle=NULL;
ElementListeChainee* DataBase::m_premierHub=NULL;

Ordinateur* DataBase::getNewOrdinateur(void)
{
    int id;
    bool idAvailable=false;//ID de nouvelle machine trouvé
    for(id = 0 ; (id < DataBase::m_nbreOrdinateur) && !idAvailable; id++)
    {
        std::cout << id << std::endl;
        ElementListeChainee* elemActuel = DataBase::m_premierOrdinateur;
        idAvailable=true;

        while(elemActuel!=NULL && idAvailable)
        {
            if(elemActuel->entitee->getID()==id)
            {
                idAvailable=false;
            }
            elemActuel=elemActuel->nextElement;
        }
        if(idAvailable)
            id--;
    }

        ElementListeChainee* tmp=DataBase::m_premierOrdinateur;
        DataBase::m_premierOrdinateur = new ElementListeChainee;//On remplace le premier maillon de la liste par le nouvel ordinateur.
        DataBase::m_premierOrdinateur->entitee=new Ordinateur(id);
        DataBase::m_premierOrdinateur->nextElement=tmp;

    DataBase::m_nbreOrdinateur+=1;
    return (Ordinateur*) DataBase::m_premierOrdinateur->entitee;
}




Passerelle* DataBase::getNewPasserelle(void)
{
    int id;
    bool idAvailable=false;//ID de nouvelle machine trouvé
    for(id=0 ; id < DataBase::m_nbrePasserelle && !idAvailable; id++)
    {
        ElementListeChainee* elemActuel = DataBase::m_premierePasserelle;
        idAvailable=true;

        while(elemActuel!=NULL && idAvailable)
        {
            if(elemActuel->entitee->getID()==id)
                idAvailable=false;

            elemActuel=elemActuel->nextElement;
        }
        if(idAvailable)
            id--;
    }

        ElementListeChainee* tmp=DataBase::m_premierePasserelle;
        DataBase::m_premierePasserelle = new ElementListeChainee;//On remplace le premier maillon de la liste par le nouvel ordinateur.
        DataBase::m_premierePasserelle->entitee=new Passerelle(id);
        DataBase::m_premierePasserelle->nextElement=tmp;

    DataBase::m_nbrePasserelle+=1;
    return (Passerelle*) DataBase::m_premierePasserelle->entitee;
}


Hub* DataBase::getNewHub(void)
{
    int id;
    bool idAvailable=false;//ID de nouvelle machine trouvé
    for(id=0 ; id < DataBase::m_nbreHub && !idAvailable; id++)
    {
        ElementListeChainee* elemActuel = DataBase::m_premierHub;
        idAvailable=true;

        while(elemActuel!=NULL && idAvailable)
        {
            if(elemActuel->entitee->getID()==id)
                idAvailable=false;

            elemActuel=elemActuel->nextElement;
        }
        if(idAvailable)
            id--;
    }
        ElementListeChainee* tmp=DataBase::m_premierHub;
        DataBase::m_premierHub = new ElementListeChainee;//On remplace le premier maillon de la liste par le nouvel ordinateur.
        DataBase::m_premierHub->entitee=new Hub(id);
        DataBase::m_premierHub->nextElement=tmp;

    DataBase::m_nbreHub+=1;
    return (Hub*) DataBase::m_premierHub->entitee;
}



void DataBase::detruireOrdinateur(Ordinateur* ordi)
{
    int id = ordi->getID();
    ElementListeChainee* elemActuel = DataBase::m_premierOrdinateur;
    if(elemActuel==NULL)
        return;
    else if(elemActuel->entitee->getID()==id)//Cas où c'est le premier élément à supprimer
    {
        DataBase::m_premierOrdinateur = elemActuel->nextElement;
        delete elemActuel;

        DataBase::m_nbreOrdinateur-=1;
        return;
    }
    else
        while(elemActuel->nextElement!=NULL)
        {
            if(elemActuel->nextElement->entitee->getID()==id)//ID Machine de Element suivant est le bon
            {
                ElementListeChainee* tmp = elemActuel->nextElement;
                elemActuel->nextElement=elemActuel->nextElement->nextElement;//Element actuel prend comme suivant le suivant de l'élément détruit
                delete tmp;

                DataBase::m_nbreOrdinateur-=1;
                return;
            }
            else
            {
                elemActuel = elemActuel->nextElement;
            }
        }
}

void DataBase::detruirePasserelle(Passerelle* passerelle)
{
    int id = passerelle->getID();
    ElementListeChainee* elemActuel = DataBase::m_premierePasserelle;
    if(elemActuel==NULL)
        return;
    else if(elemActuel->entitee->getID()==id)//Cas où c'est le premier élément à supprimer
    {
        DataBase::m_premierePasserelle = elemActuel->nextElement;
        delete elemActuel;

        DataBase::m_nbrePasserelle-=1;
        return;
    }
    else
        while(elemActuel->nextElement!=NULL)
        {
            if(elemActuel->nextElement->entitee->getID()==id)//ID Machine de Element suivant est le bon
            {
                ElementListeChainee* tmp = elemActuel->nextElement;
                elemActuel->nextElement=elemActuel->nextElement->nextElement;//Element actuel prend comme suivant le suivant de l'élément détruit
                delete tmp;

                DataBase::m_nbrePasserelle-=1;
                return;
            }
            else
            {
                elemActuel = elemActuel->nextElement;
            }
        }
}

void DataBase::detruireHub(Hub* hub)
{
    int id = hub->getID();
    ElementListeChainee* elemActuel = DataBase::m_premierHub;
    if(elemActuel==NULL)
        return;
    else if(elemActuel->entitee->getID()==id)//Cas où c'est le premier élément à supprimer
    {
        DataBase::m_premierHub = elemActuel->nextElement;
        delete elemActuel;

        DataBase::m_nbreHub-=1;
        return;
    }
    else
        while(elemActuel->nextElement!=NULL)
        {
            if(elemActuel->nextElement->entitee->getID()==id)//ID Machine de Element suivant est le bon
            {
                ElementListeChainee* tmp = elemActuel->nextElement;
                elemActuel->nextElement=elemActuel->nextElement->nextElement;//Element actuel prend comme suivant le suivant de l'élément détruit
                delete tmp;

                DataBase::m_nbreHub-=1;
                return;
            }
            else
            {
                elemActuel = elemActuel->nextElement;
            }
        }
}


ElementListeChainee* DataBase::getListOrdinateur()
{
    return DataBase::m_premierOrdinateur;
}
ElementListeChainee* DataBase::getListPasserelle()
{
    return DataBase::m_premierePasserelle;
}
ElementListeChainee* DataBase::getListHub()
{
    return DataBase::m_premierHub;
}

