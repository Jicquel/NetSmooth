#include "Entitee.h"

using namespace std;

Entitee::Entitee(int id, int type) :m_id(id)

{
        char nomBridge[10];
        char caratype='\0';
        stringstream stid;
        stid << id;
        if(type==TYPE_ORDINATEUR)
        {
                //m_bridgeInit="\0";
                m_nom="ordi"+stid.str();
        }
        else
        {
                if(type==TYPE_PASSERELLE)
                {
                        caratype='P';
                        m_nom="pass"+stid.str();
                }
                if(type==TYPE_HUB)
                {
                        caratype='H';
                        m_nom="hub"+stid.str();
                }
                sprintf(nomBridge, "br%c%d", caratype, id);
                //m_bridgeInit=nomBridge;
        }
        //this->setBridgeActuel("\0");
        m_type=type;
        //m_bridgeActuel=m_bridgeInit;
        m_running=MACHINE_STOPEE;
        //m_estConnecteAuBridge=false;
        this->m_cableList = new std::vector<Cable*>();
        std::cout << "addresse = " << this->m_cableList << std::endl;
}

Entitee::~Entitee(){}

string Entitee::getNom()
{
        return this->m_nom;
}

void Entitee::setNom(string nom)
{
        this->m_nom=nom;
}

void Entitee::setEtatEntitee(bool etat)
{
        this->m_running=etat;
}

bool Entitee::getEtatEntitee()
{
        return this->m_running;
}

int Entitee::getType()
{
        return this->m_type;
}

void Entitee::addCable(Cable *cable)
{
        m_cableList->push_back(cable);
}

vector<Cable*>* Entitee::getCables(void)
{
        return this->m_cableList;
}

void Entitee::setID(int id)
{
        this->m_id = id;
}

int Entitee::getID(void)
{
        return this->m_id;
}


void Entitee::launchEntitee()
{
        if(this->getEtatEntitee()==MACHINE_LANCEE)
                return;
        this->lancerContainer();	/*ces 3 lignes ne font rien si c'est un Hub*/
        this->appliquerParamIp();
        this->appliquerParamRoutage4();
        this->appliquerParamRoutage6();

        this->setEtatEntitee(MACHINE_LANCEE);	/* modifie flag dans entitee */
        //this->modifBridgesSousReseau_entiteeLancee();
        this->setupBridges();
        VueInformation::getInstanceOf()->getAllumer()->setEnabled(true);
}


void Entitee::stopEntitee()
{

        VueInformation::getInstanceOf()->addNewInfos();

        if(this->getEtatEntitee()==MACHINE_STOPEE)
                return;

        this->setEtatEntitee(MACHINE_STOPEE);	/* modifie flag dans entitee */

        this->stopperContainer();

        qDebug("modif bridge debut");
        //this->modifBridgesSousReseau_entiteeStoppee();
        this->unsetupBridges();
        qDebug("modif bridge fin");


        /*reste a supprimer les cables*/
}

bool Entitee::testCreateCable(Entitee* e)
{
        /* ne pas lier 2 fois les deux memes entitées */
        vector<Cable*> *cables = this->getCables();
        for(int i=0 ; i<cables->size() ; i++)
        {
                Entitee* autre;
                autre=(this->getType()==TYPE_HUB)?(Entitee*)((*cables)[i]->getMachine()):
                                                  (Entitee*)((*cables)[i]->getHub());
                if(autre == VueCable::getPremiereSelection()->getModele())
                        return false;
        }

        /* limiter le nombre de cables par entitée */
        if(this->m_type==TYPE_ORDINATEUR && cables->size() >= NOMBRE_INTERFACES_ORDINATEUR ||
                        this->m_type==TYPE_PASSERELLE && cables->size() >= NOMBRE_INTERFACES_PASSERELLE)
                return false;


        return true;
}

void Entitee::setVue(VueEntitee* v)
{
        this->m_vue=v;
}

VueEntitee* Entitee::getVue()
{
        return this->m_vue;
}

void Entitee::deleteCable(Cable const *c )
{
        for(int i= 0 ; i<(int)this->m_cableList->size(); i++)
        {
                if((*this->m_cableList)[i] == c)
                {
                        this->m_cableList->erase(this->m_cableList->begin()+i);
                }
        }
}

