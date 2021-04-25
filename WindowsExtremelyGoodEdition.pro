QT       += core gui webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    App.cpp \
    Apps/InternetExplorer.cpp \
    Apps/MessageBox.cpp \
    Apps/Notepad.cpp \
    Apps/Run.cpp \
    FileSystem/FakeFileSystem.cpp \
    System.cpp \
    SystemElements/Desktop.cpp \
    SystemElements/DesktopIcon.cpp \
    SystemElements/DesktopIconTextEdit.cpp \
    SystemElements/StartMenu.cpp \
    SystemElements/StartMenuItem.cpp \
    SystemElements/SystemMdiArea.cpp \
    SystemElements/SystemSubWindow.cpp \
    SystemElements/SystemTaskbar.cpp \
    SystemElements/TaskbarElement.cpp \
    SystemElements/WindowTitleBar.cpp \
    SystemWindow.cpp \
    main.cpp \
    ControlWindow.cpp

HEADERS += \
    App.h \
    Apps/InternetExplorer.h \
    Apps/MessageBox.h \
    Apps/Notepad.h \
    Apps/Run.h \
    ControlWindow.h \
    FileSystem/FakeFileSystem.h \
    System.h \
    SystemElements/Desktop.h \
    SystemElements/DesktopIcon.h \
    SystemElements/DesktopIconTextEdit.h \
    SystemElements/StartMenu.h \
    SystemElements/StartMenuItem.h \
    SystemElements/SystemMdiArea.h \
    SystemElements/SystemSubWindow.h \
    SystemElements/SystemTaskbar.h \
    SystemElements/TaskbarElement.h \
    SystemElements/WindowTitleBar.h \
    SystemWindow.h

FORMS += \
    Apps/InternetExplorer.ui \
    Apps/MessageBox.ui \
    Apps/Run.ui \
    ControlWindow.ui \
    SystemElements/DesktopIcon.ui \
    SystemElements/SystemMdiArea.ui \
    SystemElements/SystemSubWindow.ui \
    SystemElements/SystemTaskbar.ui \
    SystemElements/WindowTitleBar.ui \
    SystemWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
	res.qrc

DISTFILES += \
	.gitignore
