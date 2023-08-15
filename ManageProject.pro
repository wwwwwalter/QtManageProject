QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    UI/newproject/newprojectdialog.cpp \
    UI/plugins/audio/audioform.cpp \
    UI/plugins/file/fileform.cpp \
    UI/plugins/video/videoform.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    UI/newproject/newprojectdialog.h \
    UI/plugins/audio/audioform.h \
    UI/plugins/file/fileform.h \
    UI/plugins/video/videoform.h \
    mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    UI/newproject/newprojectdialog.ui \
    UI/plugins/audio/audioform.ui \
    UI/plugins/file/fileform.ui \
    UI/plugins/video/videoform.ui

RESOURCES += \
    resources.qrc
