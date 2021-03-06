QT       += core gui webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 sdk_no_version_check

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    App.cpp \
    Apps/FileSelector.cpp \
    Apps/InternetExplorer.cpp \
    Apps/MessageBox.cpp \
    Apps/Notepad.cpp \
    Apps/Run.cpp \
    Control/AppControl.cpp \
    Control/GlobalControl.cpp \
    Control/InternetExplorerControl.cpp \
    Control/NotepadControl.cpp \
    FileSystem/FakeFileSystem.cpp \
    FileSystem/FileExplorerTable.cpp \
    System.cpp \
    SystemElements/Desktop.cpp \
    SystemElements/DesktopIcon.cpp \
    SystemElements/DesktopIconTextEdit.cpp \
    SystemElements/ListIcon.cpp \
    SystemElements/StartMenu.cpp \
    SystemElements/StartMenuItem.cpp \
    SystemElements/SystemMdiArea.cpp \
    SystemElements/SystemSubWindow.cpp \
    SystemElements/SystemTaskbar.cpp \
    SystemElements/TaskbarElement.cpp \
    SystemElements/WindowTitleBar.cpp \
    SystemWindow.cpp \
    Util/LineEditList.cpp \
    Util/PercentageSpinBox.cpp \
    Util/RangedSpinBox.cpp \
    Util/TreeComboBox.cpp \
    main.cpp \
    ControlWindow.cpp

HEADERS += \
    App.h \
    Apps/FileSelector.h \
    Apps/InternetExplorer.h \
    Apps/MessageBox.h \
    Apps/Notepad.h \
    Apps/Run.h \
    Control/AppControl.h \
    Control/GlobalControl.h \
    Control/InternetExplorerControl.h \
    Control/NotepadControl.h \
    ControlWindow.h \
    FileSystem/FakeFileSystem.h \
    FileSystem/FileExplorerTable.h \
    System.h \
    SystemElements/Desktop.h \
    SystemElements/DesktopIcon.h \
    SystemElements/DesktopIconTextEdit.h \
    SystemElements/ListIcon.h \
    SystemElements/StartMenu.h \
    SystemElements/StartMenuItem.h \
    SystemElements/SystemMdiArea.h \
    SystemElements/SystemSubWindow.h \
    SystemElements/SystemTaskbar.h \
    SystemElements/TaskbarElement.h \
    SystemElements/WindowTitleBar.h \
    SystemWindow.h \
    Util/LineEditList.h \
    Util/PercentageSpinBox.h \
    Util/RangedSpinBox.h \
    Util/TreeComboBox.h

FORMS += \
    Apps/FileSelector.ui \
    Apps/InternetExplorer.ui \
    Apps/MessageBox.ui \
    Apps/Notepad.ui \
    Apps/Run.ui \
    ControlWindow.ui \
    SystemElements/DesktopIcon.ui \
    SystemElements/ListIcon.ui \
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
