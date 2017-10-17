QT += widgets

HEADERS += \
    controleurs/vueRoutesControleur.h\
    controleurs/VueIPControleur.h\
    controleurs/vueinformationcontroleur.h\
    controleurs/vuemachinecontroleur.h \
    controleurs/vuehubcontroleur.h \
    controleurs/vuepasserellecontroleur.h\
    controleurs/selectioncontroleur.h \
    controleurs/vueprincipalecontroleur.h \
    controleurs/vueentiteecontroleur.h \
    controleurs/VueFormulaireIPControleur.h \
    controleurs/VueCableControleur.h\
    modeles/Machine.h\
    modeles/Entitee.h\
    modeles/Ordinateur.h\
    modeles/Passerelle.h\
    modeles/Constantes.h\
    modeles/Hub.h\
    modeles/DataBase.h\
    modeles/Cable.h\
    modeles/Bridge.h\
    modeles/Cable.h\
    modeles/Save.h\
    vues/fenetre.h\
    vues/selection.h \
    vues/vueprincipale.h \
    vues/vuemachine.h \
    vues/vueentitee.h \
    vues/vuehub.h \
    vues/vuepasserelle.h \
    vues/vuecable.h\
    vues/constantes.h\
    vues/vueinformation.h\
    vues/ligneroute.h\
    vues/vueRoutes.h\
    vues/VueIP.h\
    vues/VueFormulaireIP.h\
    vues/VueErreur.h\
    vues/draganddropgraphicsview.h\
    vues/selectlabel.h\

SOURCES += \
    main.cpp\
    controleurs/selectioncontroleur.cpp \
    controleurs/vueprincipalecontroleur.cpp \
    controleurs/vueentiteecontroleur.cpp \
    controleurs/vuemachinecontroleur.cpp \
    controleurs/vuehubcontroleur.cpp \
    controleurs/vuepasserellecontroleur.cpp\
    controleurs/vueinformationcontroleur.cpp\
    controleurs/vueRoutesControleur.cpp\
    controleurs/VueIPControleur.cpp\
    controleurs/VueFormulaireIPControleur.cpp \
    controleurs/VueCableControleur.cpp\
    modeles/Machine.cpp\
    modeles/Entitee.cpp\
    modeles/Ordinateur.cpp\
    modeles/Passerelle.cpp\
    modeles/Hub.cpp\
    modeles/DataBase.cpp\
    modeles/Cable.cpp\
    modeles/Bridge.cpp\
    modeles/Save.cpp\
    vues/fenetre.cpp\
    vues/VueIP.cpp\
    vues/VueFormulaireIP.cpp\
    vues/vueRoutes.cpp\
    vues/selection.cpp \
    vues/vueprincipale.cpp \
    vues/vuemachine.cpp \
    vues/vueentitee.cpp \
    vues/vuehub.cpp \
    vues/vuepasserelle.cpp \
    vues/vuecable.cpp\
    vues/vueinformation.cpp\
    vues/ligneroute.cpp\
    vues/VueErreur.cpp\
    vues/draganddropgraphicsview.cpp\
    vues/selectlabel.cpp\

QMAKE_LIBS += \
                -llxc \

QMAKE_CXXFLAGS += \
		-std=c++11 \
