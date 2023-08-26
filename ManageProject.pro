QT       += core gui
QT       += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    UI/main/mainwindow.cpp \
    UI/newfile/newfiledialog.cpp \
    UI/newproject/newprojectdialog.cpp \
    UI/plugins/abstract/abstrackplugin.cpp \
    UI/plugins/audio/audioform.cpp \
    UI/plugins/file/fileform.cpp \
    UI/plugins/video/videoform.cpp \
    UI/removefile/removefiledialog.cpp \
    UI/spacetab/abstractfile.cpp \
    UI/spacetab/audiospace.cpp \
    UI/spacetab/grider.cpp \
    UI/spacetab/gridtableview.cpp \
    UI/spacetab/playlistfile.cpp \
    UI/spacetab/spacefile.cpp \
    UI/spacetab/spacemedia.cpp \
    UI/spacetab/spacetabwidget.cpp \
    UI/spacetab/spacewidget.cpp \
    UI/spacetab/spacewidgetgriddesigndialog.cpp \
    UI/spacetab/textfile.cpp \
    UI/spacetab/videospace.cpp \
    UI/welcome/welcomewidget.cpp \
    main.cpp

HEADERS += \
    UI/main/mainwindow.h \
    UI/newfile/newfiledialog.h \
    UI/newproject/newprojectdialog.h \
    UI/plugins/abstract/abstrackplugin.h \
    UI/plugins/audio/audioform.h \
    UI/plugins/file/fileform.h \
    UI/plugins/video/videoform.h \
    UI/removefile/removefiledialog.h \
    UI/spacetab/abstractfile.h \
    UI/spacetab/audiospace.h \
    UI/spacetab/grider.h \
    UI/spacetab/gridtableview.h \
    UI/spacetab/playlistfile.h \
    UI/spacetab/spacefile.h \
    UI/spacetab/spacemedia.h \
    UI/spacetab/spacetabwidget.h \
    UI/spacetab/spacewidget.h \
    UI/spacetab/spacewidgetgriddesigndialog.h \
    UI/spacetab/textfile.h \
    UI/spacetab/videospace.h \
    UI/welcome/welcomewidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    UI/main/mainwindow.ui \
    UI/newfile/newfiledialog.ui \
    UI/newproject/newprojectdialog.ui \
    UI/plugins/audio/audioform.ui \
    UI/plugins/file/fileform.ui \
    UI/plugins/video/videoform.ui \
    UI/removefile/removefiledialog.ui \
    UI/spacetab/audiospace.ui \
    UI/spacetab/playlistfile.ui \
    UI/spacetab/spacefile.ui \
    UI/spacetab/spacewidgetgriddesigndialog.ui \
    UI/spacetab/textfile.ui \
    UI/spacetab/videospace.ui \
    UI/welcome/welcomewidget.ui

RESOURCES += \
    resources.qrc

DISTFILES +=
