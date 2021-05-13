#include "System.h"

System::System(QObject* parent) : QObject(parent)
{
}

void System::init(SystemMdiArea* mdiArea, SystemTaskbar* taskbar)
{
	systemMdiArea = mdiArea;
	systemTaskbar = taskbar;
}

void System::runApp(App* app)
{
	systemMdiArea->addSubWindow(app);

	TaskbarElement* appTaskbarElement = app->createTaskbarElement();
	systemTaskbar->addTaskbarElement(appTaskbarElement);

	QObject::connect(appTaskbarElement, &TaskbarElement::clicked, [=]
	{
		app->setFocus();
	});

	app->show();
}

void System::addIconToDesktop(DesktopIcon* icon)
{
	systemMdiArea->getDesktop()->addIcon(icon);

	//Set default slots
	icon->createShortcutActionSlot = [=]([[maybe_unused]] bool checked)
	{
		auto msgBox = new MessageBox(MessageBox::messageBoxType::ERROR, "Windows", "Windows cannot create a shortcut for this object.", MessageBox::messageBoxButtonSet::OK);
		QObject::connect(msgBox->getButtons()[0], &QPushButton::pressed, [=]()
		{
			msgBox->closeApp();
			delete msgBox;
		});
		runApp(msgBox);
	};

	icon->deleteActionSlot = [=]([[maybe_unused]] bool checked)
	{
		auto msgBox = new MessageBox(MessageBox::messageBoxType::ERROR, "Windows", "Windows has encountered an error while trying to delete this object", MessageBox::messageBoxButtonSet::OK);
		QObject::connect(msgBox->getButtons()[0], &QPushButton::pressed, [=]()
		{
			msgBox->closeApp();
			delete msgBox;
		});
		runApp(msgBox);
	};

	icon->renameActionSlot = [=]([[maybe_unused]] bool checked)
	{
		icon->rename();
	};

	icon->propertiesActionSlot = [=]([[maybe_unused]] bool checked)
	{
		auto msgBox = new MessageBox(MessageBox::messageBoxType::ERROR, "Windows", "Windows was unable to show properties for this object.", MessageBox::messageBoxButtonSet::OK);
		QObject::connect(msgBox->getButtons()[0], &QPushButton::pressed, [=]()
		{
			msgBox->closeApp();
			delete msgBox;
		});
		runApp(msgBox);
	};
}

QRect System::getMdiAreaGeometry()
{
	return systemMdiArea->geometry();
}
