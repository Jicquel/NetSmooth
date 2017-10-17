#ifndef HUB_DEF
#define HUB_DEF

#include <iostream>
#include <vector>

class Hub;

#include "modeles/Entitee.h"
#include "modeles/Bridge.h"

class Hub : public Entitee
{
    public:
        /*	Hub()
         *
         *	constructeur de la classe, il appelle le constructeur
         *	de son parent
         */
        Hub(int id);
        ~Hub();

        std::string getBridgeName();

        void setupBridges();
        void unsetupBridges();

        void turnOnBridge();
        void turnOffBridge();

        int howManyActiveCables();

        bool isBridgeActive() const;

        /*	Methodes inutiles
         *
         *	ces methodes ne sont redéfinies ici que pour respecter
         *	les methodes virtuelles pures du parent, mais elles
         *	ne sont pas utiles ici (elles le sont dans l'autre
         *	enfant en revanche: Machine)
         *
         */
        void deleteAllParams();
        std::vector<struct paramIp*> getIpConfig();
        void appliquerParamIp();
        void appliquerParamRoutage4();
        void appliquerParamRoutage6();
        int lancerContainer();
        void lierABridge(Cable* c);
        void separerDeBridge(Cable *c);
        void stopperContainer();
        void lireModifContainer();
        void majIpContainer();
        void majRouteContainer();
        void setIpConfig(struct paramIp* ip);

    private:
        std::string m_bridgeName;
        bool m_stateBridge;
};

#endif

