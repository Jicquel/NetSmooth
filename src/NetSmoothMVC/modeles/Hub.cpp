#include "Hub.h"

Hub::Hub(int id)
	:Entitee(id, TYPE_HUB)
{
    this->m_bridgeName = string("Hub") + std::to_string(id).c_str();
    this->m_stateBridge-false;
}

Hub::~Hub()
{
 DataBase::detruireHub(this);
}

std::string Hub::getBridgeName()
{
    return this->m_bridgeName;
}


void Hub::setupBridges()
{
        vector<Cable*>* listCable=this->getCables();
        int i=0;
        bool qqnAutour=false;

        for(i=0 ; i<(int)listCable->size() ; i++)
                if((*listCable)[i]->isActive())
                {
                    qqnAutour = true;
                    break;
                }

        if(!qqnAutour)        // personne dans les environs
        {
                cout << "personne de valable autour" << endl ;
                return;
        }

        this->turnOnBridge();

        for(i=0 ; i<(int)listCable->size() ; i++)
                if((*listCable)[i]->isActive())
                    (*listCable)[i]->getMachine()->lierABridge((*listCable)[i]);

}

int Hub::howManyActiveCables()
{
        vector<Cable*>* listCable=this->getCables();
        int i=0, j=0;

        for(i=0 ; i<(int)listCable->size() ; i++)
                if((*listCable)[i]->isActive())
                    j++;

        return j;

}

void Hub::turnOffBridge()
{
        this->m_stateBridge=false;
        Bridge::detruireBridge(this->m_bridgeName.c_str());
}

void Hub::turnOnBridge()
{
        this->m_stateBridge=true;
        Bridge::creerBridge(m_bridgeName.c_str());
}

bool Hub::isBridgeActive() const
{
        return m_stateBridge;
}

void Hub::unsetupBridges()
{
        this->turnOffBridge();
}


void Hub::deleteAllParams(){}
int Hub::lancerContainer(){return 0;}
std::vector<struct paramIp*> Hub::getIpConfig(){}
void Hub::appliquerParamIp(){}
void Hub::appliquerParamRoutage4(){}
void Hub::appliquerParamRoutage6(){}
void Hub::stopperContainer(){}
void Hub::lierABridge(Cable *c){}
void Hub::separerDeBridge(Cable* c){}
void Hub::lireModifContainer(){}
void Hub::majIpContainer(){}
void Hub::majRouteContainer(){}
void Hub::setIpConfig(struct paramIp* ip){}
