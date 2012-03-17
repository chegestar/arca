# Add more folders to ship with the application, here
folder_01.source = qml/arca
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

symbian:TARGET.UID3 = 0xE0637B16

# Smart Installer package's UID
# This UID is from the protected range and therefore the package will
# fail to install if self-signed. By default qmake uses the unprotected
# range value if unprotected UID is defined for the application and
# 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
symbian:TARGET.CAPABILITY += NetworkServices

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
CONFIG += mobility
MOBILITY += serviceframework

# Speed up launching on MeeGo/Harmattan when using applauncherd daemon
CONFIG += qdeclarative-boostable

# Add dependency to Symbian components
# CONFIG += qt-components

QT += network

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    articlestore.cpp \
    articlepublishingclient.cpp \
    dbsession.cpp \
    dbrestclient.cpp \
    ../kqoauth/src/kqoauthutils.cpp \
    ../kqoauth/src/kqoauthrequest.cpp \
    ../kqoauth/src/kqoauthrequest_xauth.cpp \
    ../kqoauth/src/kqoauthrequest_1.cpp \
    ../kqoauth/src/kqoauthmanager.cpp \
    ../kqoauth/src/kqoauthauthreplyserver.cpp \
    dblistmodel.cpp \
    dbmetadata.cpp

INCLUDEPATH += ../kqoauth/src

LIBS += -lqjson -lcontentaction

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog

HEADERS += \
    articlestore.h \
    articlepublishingclient.h \
    dbsession.h \
    dbrestclient.h \
    ../kqoauth/src/kqoauthutils.h \
    ../kqoauth/src/kqoauthrequest.h \
    ../kqoauth/src/kqoauthrequest_xauth.h \
    ../kqoauth/src/kqoauthrequest_xauth_p.h \
    ../kqoauth/src/kqoauthrequest_p.h \
    ../kqoauth/src/kqoauthrequest_1.h \
    ../kqoauth/src/kqoauthmanager.h \
    ../kqoauth/src/kqoauthmanager_p.h \
    ../kqoauth/src/kqoauthglobals.h \
    ../kqoauth/src/kqoauthauthreplyserver.h \
    ../kqoauth/src/kqoauthauthreplyserver_p.h \
    dblistmodel.h \
    dbmetadata.h
