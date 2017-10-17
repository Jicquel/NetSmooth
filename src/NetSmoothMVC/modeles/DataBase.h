#ifndef DATABASE_DEF
#define DATABASE_DEF

class DataBase;

#include "modeles/Entitee.h"

typedef struct elemList
{
    Entitee* entitee;
    struct elemList* nextElement;
} ElementListeChainee;

class DataBase
{

public:

        static Ordinateur* getNewOrdinateur(void);
        static Passerelle* getNewPasserelle(void);
        static Hub* getNewHub(void);
        static void detruireOrdinateur(Ordinateur* ordi);
        static void detruirePasserelle(Passerelle* passerelle);
        static void detruireHub(Hub* hub);
        static ElementListeChainee* getListOrdinateur(void);
        static ElementListeChainee* getListPasserelle(void);
        static ElementListeChainee* getListHub(void);

private:
        static int m_nbreOrdinateur;
        static int m_nbrePasserelle;
        static int m_nbreHub;
        static ElementListeChainee* m_premierePasserelle;
        static ElementListeChainee* m_premierHub;
        static ElementListeChainee* m_premierOrdinateur;
};

/* struct elementListeEntitee */

#endif
