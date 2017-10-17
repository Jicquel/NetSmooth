#ifndef ENTITEE_DEF
#define ENTITEE_DEF

#include <iostream>
#include <stdio.h>
#include <string>
#include <strings.h>
#include <vector>

class Entitee;

class Hub;
class Machine;
class Ordinateur;
class Passerelle;

#include "modeles/Cable.h"
#include "vues/vueinformation.h"
#include "vues/vueentitee.h"
#include "modeles/DataBase.h"

#include "modeles/Constantes.h"

/*	paramIp
 *
 *	structure qui permet de stocker les parametres IP d'une machine pour les
 *	lui appliquer lors de son démarage
 */
struct paramIp
{
    std::string interface;
    std::string ipv4;
    std::string maskv4;
    std::string ipv6;
};

class Entitee
{
public:
        /*	Entitee(int numType, int type)
                 *
                 *	Constructeur de la classe, il initialise le
                 *	nom de bridge par defaut (ou bridge Initial) pour hub
                 *	et passerelles
                 *
                 *	ARGS
                 *	-numtype :
                 *		numero de la machine créée, il doit
                 *		etre unique pour chaque ma de meme
                 *		type
                 *
                 *	-type :
                 *		numero correspondant au type, se
                 *		réferer au fichier
                 *		Constantes.h -> TYPE_****
                 */
        Entitee(int id, int type);

        /*	bool getEtatEntitee()
                 *
                 *	permet d'obtenir l'etat de la machine
                 *
                 *	RETURN VALUE
                 *	elle retourne un booleen : true si la
                 *	machine est allumée et false sinon.
                 *
                 *	NOTE
                 *	cette methode est applicable sur n'importe
                 *	quel entitee, cad Machine, Passerelle ou Hub
                 */
        bool getEtatEntitee(void);

        /*	void setEtatEntitee(bool etat)
                 *
                 *	permet de modifier l'etat de la machine
                 *
                 *	ARGS
                 *	-etat:
                 *		booleen: true si vous avez
                 *		allumé la machine, false si
                 *		vous l'avez eteinte
                 *
                 *	NOTE
                 *	cette methode est applicable sur n'importe
                 *	quel entitee, cad Machine, Passerelle ou Hub
                 */
        void setEtatEntitee(bool etat);

        /*	int getType()
                 *
                 *	permet de connaitre le type de l'entitee
                 *
                 *	RETURN VALUE
                 *	retourne un entier representant le type; se réferer
                 *	au fichier Constantes.h -> TYPE_****
                 */
        int getType(void);

        /*	vector<Cable*> getCables()
                 *
                 *	permet de recuperer les cables auxquels est
                 *	connecté l'entitée
                 *
                 *	RETURN VALUE
                 *	renvoie un "vector" (=tableau plus ou moins)
                 *	d'adresses de Cables dans lequel tous les
                 *	cables auquels l'entitee est relié sont repertoriés
                 */
        std::vector<Cable *> *getCables(void);

        /*	void addCable(Cable* cable)
                 *
                 *	permet d'ajouter un cable a la liste des cables
                 *	de l'entitée
                 *
                 *	ARGS
                 *	-cable:
                 *		adresse du cable a ajouter
                 *
                 *	NOTE
                 *	ne pas créer le cable a ajouter dans un une
                 *	structure conditionnelle ou une boucle, sinon
                 *	le cable disparaitra *POOF*
                 *
                 */
        void addCable(Cable *cable);

        void setID(int id);

        int getID(void);

        /*	void launchEntitee()
                 *
                 *	permet de lancer une Entitee, et d'executer toutes les
                 *	opérations annexes a ce lancement
                 */
        void launchEntitee();

        /*	void stopEntitee()
                 *
                 *	permet de stopper une Entitee, et d'executer toutes les
                 *	opérations annexes a cet arret
                 */
        void stopEntitee();

        /*	Methodes virtuelles pures
                 *
                 *	ces methodes sont décrites dans la classe Machine. Les declarer
                 *	ici en tant que methodes virtuelles pures evite les transtypages
                 *	du type < ((Machine*)this)->lancerContainer() >
                 */
        std::string getNom();
        void setNom(std::string nom);

        void deleteCable(Cable const *c);

        bool testCreateCable(Entitee* e);

        virtual void deleteAllParams() = 0;

        virtual void setupBridges() = 0;
        virtual void unsetupBridges() = 0;

        virtual void setIpConfig(struct paramIp* ip) = 0;
        virtual std::vector<struct paramIp*> getIpConfig() = 0 ;
        virtual void lireModifContainer() = 0;
        virtual void appliquerParamIp() = 0;
        virtual void appliquerParamRoutage4() = 0;
        virtual void appliquerParamRoutage6() = 0;
        virtual int lancerContainer() = 0;
        virtual void stopperContainer() = 0;
        virtual void lierABridge(Cable* c) = 0;
        virtual void separerDeBridge(Cable* c) = 0;
        virtual void majIpContainer() = 0;
        virtual void majRouteContainer() = 0;
        void setVue(VueEntitee* v);
        VueEntitee* getVue();

        virtual ~Entitee();
protected:

        /*	m_running
                 *
                 *	variable representant l'etat de l'entitée
                 *	elle vaut true si la machine est allumée et
                 *	false sinon
                 */
        bool m_running;

        /*	m_cableList
                 *
                 *	liste de Cables auquel l'entitee est reliée
                 *	ATTENTION, rien au niveau du code n'empeche
                 *	de mettre 2 cables sur une machine,
                 *	IL NE FAUT PAS LE FAIRE, sinon ca va tout casser
                 *	au demarage de la machine... TOUT CASSER!!!
                 */
        std::vector<Cable*> *m_cableList=NULL;

        int m_type;
        int m_id;

        std::string m_nom;

        VueEntitee* m_vue;
};


#include "modeles/Hub.h"
#include "modeles/Machine.h"

#endif
