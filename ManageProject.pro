QT       += core gui

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
    UI/spacetab/audiospace.cpp \
    UI/spacetab/emptyspace.cpp \
    UI/spacetab/form.cpp \
    UI/spacetab/spacetabwidget.cpp \
    UI/spacetab/textfile.cpp \
    UI/spacetab/videospace.cpp \
    main.cpp

HEADERS += \
    UI/main/mainwindow.h \
    UI/newfile/newfiledialog.h \
    UI/newproject/newprojectdialog.h \
    UI/plugins/abstract/abstrackplugin.h \
    UI/plugins/audio/audioform.h \
    UI/plugins/file/fileform.h \
    UI/plugins/video/videoform.h \
    UI/spacetab/audiospace.h \
    UI/spacetab/emptyspace.h \
    UI/spacetab/form.h \
    UI/spacetab/spacetabwidget.h \
    UI/spacetab/textfile.h \
    UI/spacetab/videospace.h

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
    UI/spacetab/audiospace.ui \
    UI/spacetab/emptyspace.ui \
    UI/spacetab/form.ui \
    UI/spacetab/textfile.ui \
    UI/spacetab/videospace.ui

RESOURCES += \
    resources.qrc
