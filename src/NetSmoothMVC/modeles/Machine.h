#ifndef ORDINATEUR_DEF
#define ORDINATEUR_DEF

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <signal.h>
#include <unistd.h>
#include <strings.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <lxc/lxccontainer.h>
#include <errno.h>
#include <fstream>
#include <string>
#include <bitset>
#include <sstream>
#include <QProcess>
#include <QStringList>
#include <pwd.h>

class Machine;

class Ordinateur;
class Passerelle;

#include "modeles/Entitee.h"


/*	paramRoutage
 *
 *	structure qui permet de stocker les parametres de routage d'une machine pour les
 *	lui appliquer lors de son démarage
 */
struct paramRoutage
{
    int id;
    std::string interface;
    std::string destination;
    std::string passerelle;
};



class Machine : public Entitee
{
public:
    /*	Machine(int id, int type, struct lxc_container* c)
     *
     *	Constructeur de la classe, il appelle le constructeur
     *	de Entitee et initialise l'argument container
     *
     *	ARGS
     *	-id
     *		id de la machine
     *	-type
     *		type de la machine (TYPE_ORDINATEUR ou TYPE_PASSERELLE)
     *	-c
     *		container associé a la machine
     */
    Machine(int d, int type, const char* cntName);

    virtual ~Machine();
    /*	struct lxc_container* getContainer() const
     *
     *	permet de recuperer le container associé a la machine
     *
     *	RETURN VALUE
     *	adresse du container associé a la machine
     */
    struct lxc_container* getContainer(void) const;

    /*	void addIpConfig(struct paramIp ip)
     *
     *	permet d'ajouter une configuration IP a une machine
     *
     *	ARGS
     *	-ip
     *		structure contenant les parametres IP
     *		a ajouter
     */
    void addIpConfig(struct paramIp* ip);

    /*	vector<struct paramIp> getIpConfig() const
     *
     *	permet de recuperer les configurations IP d'une machine
     *
     *	RETURN VALUE
     *	tableau (sous forme de vector) contenant toutes les
     *	configurations IP
     */


    void setIpConfig(struct paramIp* ip);

    std::vector<struct paramIp*> getIpConfig();

    /*	void addRouteConfig(struct paramRoutage route)
     *
     *	permet d'ajouter une configuration de routage a une machine
     *
     *	ARGS
     *	-route
     *		structure contenant les parametres de routage
     *		a ajouter
     */
    void addRouteConfig4(struct paramRoutage route);

    /*	vector<struct paramRoutage> getRouteConfig() const
     *
     *	permet de recuperer les configurations de routage d'une machine
     *
     *	RETURN VALUE
     *	tableau (sous forme de vector) contenant touts les
     *	parametres de routage de la machine
     */
    std::vector<struct paramRoutage> getRouteConfig4() const;

    /*	int lancerContainer()
     *
     *	permet de lancer le container associé a la machine
     *
     *	NOTE
     *	Si vous voulez lancer la machine, utilisez la methode
     *	launchEntitee de la classe entitee, cette methode ne lance
     *	que le container, et ne fait pas toutes les opérations
     *	annexes necessaire au bon lancement de la machine
     */
    int lancerContainer();

    /*	int stopperContainer()
     *
     *	permet de stopper le container associé a la machine
     *
     *	RETURN VALUE
     *	0 en cas de succes, -1 sinon
     */
    void stopperContainer();

    /*	void force_stopperContainer()
     *
     *	permet de stopper le container associé a la machine, de
     *	maniere plus violente que stopperContainer (il tue le PID
     *	du container)
     */
    void force_stopperContainer();

    /*	void lierABridge()
     *
     *	permet de lier le container au bridge actuel
     *
     *	NOTE
     *	fonction a utiliser uniquement lorsque le container (et
     *	donc la machine) est lancé
     */
    void lierABridge(Cable *c);

    /*	void separerDeBridge()
     *
     *	permet de separer le container de son bridge actuel
     *
     *	NOTE
     *	fonction a utiliser uniquement lorsque le container (et
     *	donc la machine) est lancé
     */
    void separerDeBridge(Cable *c);

    /*	void appliquerParamIp()
     *
     *	permet d'appliquer les parametres IP qui ont étés préalablement
     *	ajoutés avec addIpConfig()
     *
     *	NOTE
     *	fonction a utiliser uniquement lorsque le container (et
     *	donc la machine) est lancé
     */
    void appliquerParamIp();

    /*	void appliquerParamRoutage()
     *
     *	permet d'appliquer les parametres de routage qui ont étés
     *	préalablementi ajoutés avec addRouteConfig()
     *
     *	NOTE
     *	fonction a utiliser uniquement lorsque le container (et
     *	donc la machine) est lancé
     */
    void appliquerParamRoutage4();

    /*	void lancerCommandeDansContainer(char** commande)
     *
     *	permet de lancer une commande dans le container
     *
     *	ARGS
     *	-commande:
     *		chaine de caracteres a deux dimensions
     *		representant la commande
     *		exemple:char** cmd={"echo", "HelloWord", NULL};
     *
     *	NOTE
     *	Le dernier element de la chaine doit etre NULL, comme dans
     *	l'exemple ci dessus
     *
     *	fonction a utiliser uniquement lorsque le container (et
     *	donc la machine) est lancé
     */
    void lancerCommandeDansContainer(const char** commande);

    /*	void lancerXterm()
     *
     *	permet de lancer une fenetre Xterm representant le
     *	terminal de la machine
     */
    void lancerXterm();

    void deleteAllParams();

    void setupBridges();
    void unsetupBridges();

    void launchLxcContainer();

    void reinitNetworkConfig();

    void lireModifContainer();

    int getNewIdIp();

    int getNewIdRoute4();

    void removeParamIp(int id);

    void removeParamRoute4(int id);

    void removeParamRoute6(int id);

    void supprimerContainerRoutage4(int id);

    void supprimerContainerRoutage6(int id);

    void majIpContainer();

    void majRouteContainer();

    void appliquerParamRoutage6();

    void addRouteConfig6(struct paramRoutage route);

    std::vector<struct paramRoutage> getRouteConfig6() const;


    //!\\ FONCTION PRISE DE LXC, CORRIGER POUR INCLURE LES HEADERS DE LXC (LXC_UTILS)
     int wait_for_pid(pid_t pid);



private:

    /*	container associé a la machine, quand on
     *	fait tourner la machine, c'est ce container
     *	que l'on lance
     */
    struct lxc_container *m_container;

    std::string m_contrainerName;

    std::vector<struct paramIp*> m_paramIp;

    std::vector<struct paramRoutage> m_paramRoutage4;

    std::vector<struct paramRoutage> m_paramRoutage6;

    std::string m_oldV6[4];
};

#include "modeles/Ordinateur.h"
#include "modeles/Passerelle.h"

#endif
