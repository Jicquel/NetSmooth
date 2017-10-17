#include "Machine.h"

using namespace std;



Machine::Machine(int id, int type, const char* cntName)
        :Entitee(id, type)
{
        char buff[20];
        sprintf(buff, "%s%d\0", cntName, id);
        cout << "buff = '" << buff << "'" << endl;
        cout << "cntName = '" << cntName << "'" << endl;
        m_container=lxc_container_new(buff, NULL);
        m_container->set_config_item(m_container, "lxc.utsname", buff);
        this->reinitNetworkConfig();

        for(int i=0 ; i<4 ; i++)
                this->m_oldV6[i] = "";

        this->m_contrainerName = buff;
}

Machine::~Machine(){}

void Machine::setupBridges()
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


        for(i=0 ; i<(int)listCable->size() ; i++)
                if((*listCable)[i]->isActive())
                {
                        Cable* c = (*listCable)[i];
                        if(!c->getHub()->isBridgeActive())
                                c->getHub()->turnOnBridge();
                        this->lierABridge(c);
                }
}

void Machine::unsetupBridges()
{
        vector<Cable*>* listCable=this->getCables();
        int i=0;
        bool qqnAutour=false;

        for(i=0 ; i<(int)listCable->size() ; i++)
                if((*listCable)[i]->getHub()->howManyActiveCables() == 0)
                    (*listCable)[i]->getHub()->turnOffBridge();
}

void Machine::addIpConfig(struct paramIp* ip)
{
        this->m_paramIp.push_back(ip);
}

void Machine::setIpConfig(struct paramIp* ip)
{
        std::cout <<this->m_paramIp.size()<< std::endl;
        for(int i = 0; i<(int)this->m_paramIp.size() ; i++)
        {
                std::cout << this->m_paramIp[i]->interface+";"+ip->interface << std::endl;
                if(ip->interface.compare(this->m_paramIp[i]->interface.c_str()) == 0)
                {
                        this->m_paramIp[i]->ipv4 = ip->ipv4;
                        this->m_paramIp[i]->maskv4 = ip->maskv4;

                        this->m_oldV6[i] = m_paramIp[i]->ipv6;

                        this->m_paramIp[i]->ipv6 = ip->ipv6;
                        break;
                }
                cout << "i = " << i << " ; interface = " <<  ip->interface << endl;
        }
}

vector<struct paramIp*> Machine::getIpConfig()
{
        return this->m_paramIp;
}

void Machine::addRouteConfig4(struct paramRoutage route)
{
        this->m_paramRoutage4.push_back(route);
}

vector<struct paramRoutage> Machine::getRouteConfig4() const
{
        return this->m_paramRoutage4;
}

vector<struct paramRoutage> Machine::getRouteConfig6() const
{
        return this->m_paramRoutage6;
}

void Machine::addRouteConfig6(struct paramRoutage route)
{
        this->m_paramRoutage6.push_back(route);
}

struct lxc_container* Machine::getContainer(void) const
{
        return m_container;
}

int Machine::lancerContainer()
{
        int tst;

        //tst = this->m_container->start(this->m_container, 0, NULL);
        this->launchLxcContainer();       //solution de dernier recours
        /*if(!tst)
        {
                char cntName[20];
                bzero(cntName, 20);
                this->m_container->get_config_item(this->m_container, "lxc.utsname", cntName, 20);
                cout << "Failed to start the container '" << cntName << "'" << endl;
                return -1;
        }
        */
        cout << "container succefully started" << endl;
        return 0;
}

void Machine::stopperContainer()
{
        int tst;

        this->m_container->stop(this->m_container);
       // tst = this->m_container->shutdown(this->m_container, 1);
        //this->force_stopperContainer();
        /*if(!tst)
        {
                printf("Failed to cleanly stop the container, forcing.\n");
                force_stopperContainer();	//plus violent que shutdown
        }
*/
        cout << "container successfully stopped" << endl;
}

void Machine::force_stopperContainer()
{
        QProcess *p = new QProcess();
        QStringList args;

        args << this->m_contrainerName.c_str();
        p->start("/usr/share/NetSmooth/scripts/stopperContainer.sh", args);
        if(!p->waitForFinished(10000))
                std::cout << "failed stopping the container" << std::endl;
}


void Machine::separerDeBridge(Cable* c)
{
        QProcess *p = new QProcess();
        QStringList args;
        args << this->m_contrainerName.c_str() << c->getHub()->getBridgeName().c_str();
        p->start("/usr/share/NetSmooth/scripts/unjoinCntAndBridge.sh", args);
        if(!p->waitForFinished(10000))
                std::cout << "failed unjoining bridge" << std::endl;
}
void Machine::lierABridge(Cable* c)
{
        QProcess *p = new QProcess();
        QStringList args;
        args << this->m_contrainerName.c_str() << c->getHub()->getBridgeName().c_str() << std::to_string(c->getPort()).c_str();
        p->start("/usr/share/NetSmooth/scripts/joinCntAndBridge.sh", args);
        std::cout << "PASSE" << std::endl;
        if(!p->waitForFinished(10000))
                std::cout << "failed attaching to bridge" << std::endl;
}


void Machine::launchLxcContainer()
{
        QProcess *p = new QProcess();
        QStringList args;
        args << this->m_contrainerName.c_str();
        p->start("/usr/share/NetSmooth/scripts/lancerContainer.sh", args);
        if(!p->waitForFinished(10000))
                std::cout << "failed launching container" << std::endl;
}

void Machine::lancerCommandeDansContainer(const char** commande)
{
        lxc_attach_options_t options = LXC_ATTACH_OPTIONS_DEFAULT;
        lxc_attach_command_t cmd={(char*)commande[0], (char**)commande};		/* rien de compliqué par ici, juste */
        pid_t pid;
        /*(this->m_container)->init_pid(this->m_container);					/* transférer les arguments la ou il faut
                 * pour lancer une commande dans le container*/

        if(this->m_container->attach(this->m_container, lxc_attach_run_command, &cmd, &options, &pid) == -1)
                qDebug("attach lancerCommandeDansContainer");
        this->wait_for_pid(pid);//!\\ FONCTION DE LXC, A CHANGER CAR PAS ENCORE INCLUSE PAR HEADER

}

void Machine::appliquerParamIp()
{
        int i;

        vector<struct paramIp*> tab=this->getIpConfig();
        {
                for(i=0 ; i<(int)tab.size() ; i++)
                {
                        if(tab[i]->ipv4 != "" && tab[i]->maskv4 != "")
                        {
                                const char* cmd[]={"/.scr/aliasIfconfig.sh", tab[i]->interface.c_str(), tab[i]->ipv4.c_str(), "netmask", tab[i]->maskv4.c_str(), "up", NULL};
                                this->lancerCommandeDansContainer(cmd);
                        }
                        else
                        {
                                const char* cmd[]={"/.scr/aliasIfconfig.sh", tab[i]->interface.c_str(), "default", NULL};
                                this->lancerCommandeDansContainer(cmd);
                        }
                        if(tab[i]->ipv6 != "")
                        {
                                const char* cmd[]={"/.scr/aliasIfconfig.sh", tab[i]->interface.c_str(), "add", tab[i]->ipv6.c_str(), NULL};
                                this->lancerCommandeDansContainer(cmd);
                        }
                        else
                        {
                                const char* cmd[]={"/.scr/aliasIfconfig.sh", tab[i]->interface.c_str(), "del", this->m_oldV6[i].c_str(), NULL};
                                this->lancerCommandeDansContainer(cmd);
                        }
                }
        }
        this->lireModifContainer();
}

void Machine::supprimerContainerRoutage4(int id)
{
        bool found = false;
        vector<struct paramRoutage> tab=this->getRouteConfig4();
        int indice;

        for(indice=0 ; indice<(int)this->m_paramRoutage4.size() && !found ; indice++)
        {
                found = false;
                {
                        if(this->m_paramRoutage4[indice].id == id)
                        {
                                found = true;
                        }
                }
        }
        cout << "indice " << indice << endl;
        const char* cmd[]={"/sbin/route", "del", "-net", tab[indice-1].destination.c_str(), "gw", tab[indice-1].passerelle.c_str(), "dev", tab[indice-1].interface.c_str(), NULL};

        this->lancerCommandeDansContainer(cmd);
}

void Machine::supprimerContainerRoutage6(int id)
{
        bool found = false;
        vector<struct paramRoutage> tab=this->getRouteConfig6();
        int indice;

        for(indice=0 ; indice<(int)this->m_paramRoutage6.size() && !found ; indice++)
        {
                found = false;
                {
                        if(this->m_paramRoutage6[indice].id == id)
                        {
                                found = true;
                        }
                }
        }
        const char* cmd[]={"/.scr/aliasRoute.sh", "-A", "inet6", "del", tab[indice-1].destination.c_str(), "gw", tab[indice-1].passerelle.c_str(), "dev", tab[indice-1].interface.c_str(), NULL};
        this->lancerCommandeDansContainer(cmd);
}

void Machine::appliquerParamRoutage4()
{

        int i;

        vector<struct paramRoutage> tab = this->getRouteConfig4();
        for(i=0 ; i<(int)tab.size() ; i++)
        {
                const char* cmd[]={"/sbin/route", "add", "-net", tab[i].destination.c_str(), "gw", tab[i].passerelle.c_str(), "dev", tab[i].interface.c_str(), NULL};
                this->lancerCommandeDansContainer(cmd);
        }
}
/* 
 *	lance un xterm qui représente le terminal d'une Machine (donc d'un container)
 */
void Machine::lancerXterm()
{
        QProcess *p = new QProcess();
        QStringList args;
        args << this->m_contrainerName.c_str() << this->m_nom.c_str();
        p->start("/usr/share/NetSmooth/scripts/launchXtermRoot.sh", args);
}

void Machine::reinitNetworkConfig()
{
        QProcess *p = new QProcess();
        QStringList args;
        args << this->m_contrainerName.c_str();
        p->start("../NetSmoothMVC/scripts/reinitConfigContainer.sh", args);
        if(!p->waitForFinished(10000))
                std::cout << "failed reinitialating network configuration" << std::endl;
        else
                std::cout << "succefully reinitialating network configuration of " << this->m_contrainerName << std::endl;
}

void Machine::majIpContainer()
{
        const char* cmd[]={"/.scr/majIpconfig.sh", NULL};

        this->lancerCommandeDansContainer(cmd);
}

void Machine::majRouteContainer()
{
        const char* cmd1[]={"/.scr/majRoute4Config.sh", NULL};
        this->lancerCommandeDansContainer(cmd1);

        const char* cmd2[]={"/.scr/majRoute6Config.sh", NULL};
        this->lancerCommandeDansContainer(cmd2);
}

int Machine::getNewIdRoute4()
{
        bool found = false;
        int id;

        for(id = 0 ; !found ; id++)
        {
                found = true;
                for(int i=0;i<(int)this->m_paramRoutage4.size();i++)
                {
                        if(this->m_paramRoutage4[i].id == id)
                                found = false;
                }
        }

        cout << "id == >" << id << endl;
        return id-1;
}

void Machine::lireModifContainer()
{
        if(this->getEtatEntitee()==MACHINE_STOPEE)
            return;
        int i, j;
        char cntName[20];
        const char *homedir;
        char base_name_path[200];

        bzero(cntName, 20);
        bzero(base_name_path, 200);

        this->m_container->get_config_item(this->m_container, "lxc.utsname", cntName, 20);

        std::string name(cntName);

        //get $HOME
        if ((homedir = getenv("HOME")) == NULL) {
            homedir = getpwuid(getuid())->pw_dir;
        }

        if(getuid())//if normal user
        {
            strcat(base_name_path,homedir);
            strcat(base_name_path,"/.local/share/lxc/");
        }
        else//if root
            strcat(base_name_path,"/var/lib/lxc/");

        //IP conf
        ifstream ipFile((std::string(base_name_path)+name+"/rootfs/.networkInfo/ipConfig.info").c_str(), ios::in);
        string line;
        while(getline(ipFile, line))
        {
                bool ok=false;
                for(i=0 ; i<(int)this->m_paramIp.size() && !ok ; i++)
                {
                        if(line == this->m_paramIp[i]->interface)
                                ok=true;
                }
                i--;
                if(ok)
                {
                        this->m_paramIp[i]->interface=line;

                        getline(ipFile, line);
                        this->m_paramIp[i]->ipv4=line;

                        getline(ipFile, line);
                        this->m_paramIp[i]->maskv4=line;

                        getline(ipFile, line);
                        this->m_paramIp[i]->ipv6=line;
                }
        }
        ipFile.close();

        vector<struct paramRoutage> *p4 = new vector<paramRoutage>;
        ifstream route4File((std::string(base_name_path)+name+"/rootfs/.networkInfo/route4Config.info").c_str(), ios::in);
        i=0;
        while(getline(route4File, line))
        {
                struct paramRoutage *tmp = new struct paramRoutage;
                tmp->id=i;

                tmp->interface=line;

                getline(route4File, line);
                string dest=line;

                int m=0;
                string buff="";
                getline(route4File, line);
                tmp->passerelle=line;

                getline(route4File, line);
                for(j=0 ; j<(int)line.size() ; j++)
                        if(line[j]=='.')
                        {
                                if(buff=="255")
                                        m+=8;
                                else if(buff=="0")
                                        j=line.size();
                                else
                                {
                                        int nb=atoi(buff.c_str());
                                        string binary = bitset<8>(nb).to_string();
                                        int e=0;
                                        while(binary[e]!='0')
                                                e++;
                                        m+=e;
                                }
                                buff="";
                        }
                        else
                                buff+=line[j];
                stringstream ss;
                ss << m;
                tmp->destination=dest+"/"+ss.str();
                p4->push_back(*tmp);
                i++;
        }
        this->m_paramRoutage4 = *p4;
        route4File.close();

        vector<struct paramRoutage> *p6 = new vector<paramRoutage>;
        ifstream route6File((std::string(base_name_path)+name+"/rootfs/.networkInfo/route6Config.info").c_str(), ios::in);
        i=0;
        while(getline(route6File, line))
        {
                struct paramRoutage *tmp = new struct paramRoutage;
                tmp->id=i;

                tmp->destination=line;

                getline(route6File, line);
                tmp->passerelle=line;

                getline(route6File, line);
                tmp->interface=line;
                p6->push_back(*tmp);
                i++;
        }
        this->m_paramRoutage6 = *p6;
        route6File.close();
}

void Machine::removeParamRoute4(int id)
{
        bool found = false;

        for(int i = 0 ; i<(int)this->m_paramRoutage4.size() && !found ; i++)
        {

                if(this->m_paramRoutage4[i].id == id)
                {
                        found = true;
                        this->supprimerContainerRoutage4(id);
                        this->m_paramRoutage4.erase(this->m_paramRoutage4.begin() + i);
                }

        }
}

void Machine::removeParamRoute6(int id)
{
        bool found = false;

        for(int i = 0 ; i<(int)this->m_paramRoutage6.size() && !found ; i++)
        {

                if(this->m_paramRoutage6[i].id == id)
                {

                        found = true;
                        if(this->m_running == true)
                                this->supprimerContainerRoutage6(id);
                        this->m_paramRoutage6.erase(this->m_paramRoutage6.begin() + i);
                }
        }
}

void Machine::deleteAllParams()
{
    int i;

    for(i=0 ; i<this->m_paramRoutage4.size() ; i++)
            this->supprimerContainerRoutage4(i);

    for(i=0 ; i<this->m_paramRoutage6.size() ; i++)
            this->supprimerContainerRoutage6(i);

    for(i=0 ; i<this->m_paramIp.size() ; i++)
    {
            this->m_paramIp[i]->interface="";
            this->m_paramIp[i]->ipv4="";
            this->m_paramIp[i]->maskv4="";
            this->m_paramIp[i]->ipv6="";
            this->appliquerParamIp();
    }
}

void Machine::appliquerParamRoutage6()
{
        int i;

        vector<struct paramRoutage> tab = this->getRouteConfig6();
        for(i=0 ; i<(int)tab.size() ; i++)
        {
                const char* cmd[]={"/.scr/aliasRoute.sh", "-A", "inet6", "add", tab[i].destination.c_str(), "gw", tab[i].passerelle.c_str(), "dev", tab[i].interface.c_str(), NULL};
                this->lancerCommandeDansContainer(cmd);
                std::cout << "IPV6\n";
        }
}

int Machine::wait_for_pid(pid_t pid)
{
        int status, ret;

again:
        ret = waitpid(pid, &status, 0);
        if (ret == -1) {
                if (errno == EINTR)
                        goto again;
                return -1;
        }
        if (ret != pid)
                goto again;
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
                return -1;
        return 0;
}
