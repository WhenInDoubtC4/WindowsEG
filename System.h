#pragma once

#include <QObject>

#include "SystemElements/SystemMdiArea.h"
#include "SystemElements/SystemTaskbar.h"
#include "SystemElements/DesktopIcon.h"
#include "App.h"
#include "Apps/MessageBox.h"

class System : public QObject
{
	Q_OBJECT
public:
	static void init(SystemMdiArea* mdiArea, SystemTaskbar* taskbar);

	static void runApp(App* app);
	static void addIconToDesktop(DesktopIcon* icon);

	static QRect getMdiAreaGeometry();

private:
	System(QObject* parent = nullptr);

	inline static SystemMdiArea* systemMdiArea = nullptr;
	inline static SystemTaskbar* systemTaskbar = nullptr;
};

