#include "SystemTaskbar.h"
#include "ui_SystemTaskbar.h"

SystemTaskbar::SystemTaskbar(QWidget* parent) : QWidget(parent)
  , _ui(new Ui::SystemTaskbar)
  , _clockTimer(new QTimer(this))
{
	_ui->setupUi(this);

	_ui->frame->setProperty("outset", true);
	_ui->clockFrame->setProperty("inset", true);
	_ui->clockLabel->setStyleSheet("color: #000000");

	QObject::connect(_ui->startButton, &QPushButton::clicked, this, &SystemTaskbar::onStartButtonPressed);
	QObject::connect(_clockTimer, &QTimer::timeout, this, &SystemTaskbar::updateClock);

	updateClock();
	_clockTimer->start(1s);
}

SystemTaskbar::~SystemTaskbar()
{
	delete _clockTimer;
	delete _ui;
}

void SystemTaskbar::onStartButtonPressed()
{
	auto startMenu = new StartMenu(this);
	auto programsAction = startMenu->addItem("Programs", QPixmap(":/Resources/Style/Assets/Icons/Programs.png"), true);
	startMenu->addItem("Documents",QPixmap(":/Resources/Style/Assets/Icons/Documents.png"), true);
	startMenu->addItem("Settings", QPixmap(":/Resources/Style/Assets/Icons/Settings.png"), true);
	startMenu->addItem("Find", QPixmap(":/Resources/Style/Assets/Icons/Find.png"), true);
	startMenu->addItem("Help", QPixmap(":/Resources/Style/Assets/Icons/Help.png"));
	startMenu->addItem("Run", QPixmap(":/Resources/Style/Assets/Icons/Run.png"));
	startMenu->addSeparator();
	startMenu->addItem("Shut down", QPixmap(":/Resources/Style/Assets/Icons/Shutdown.png"));

	auto propgramsMenu = new QMenu(this);
	propgramsMenu->addAction(QIcon(":/Resources/Style/Assets/Icons/Programs.png"), "Accessories");
	propgramsMenu->addAction(QIcon(":/Resources/Style/Assets/Icons/Programs.png"), "StartUp");
	propgramsMenu->addAction(QIcon(":/Resources/Style/Assets/Icons/Programs.png"), "MS-DOS Propmpt");
	propgramsMenu->addAction(QIcon(":/Resources/Style/Assets/Icons/Programs.png"), "Windows Explorer");
	programsAction->setMenu(propgramsMenu);

	QPoint startMenuDimensions = QPoint(0, startMenu->getTotalHeight());
	startMenu->popup(mapToGlobal(_ui->startButton->pos()) - startMenuDimensions);
}

void SystemTaskbar::addTaskbarElement(TaskbarElement* element)
{
	int index = _ui->frameLayout->count() - 2;
	_ui->frameLayout->insertWidget(index, element, 0);

	QObject::connect(element, &TaskbarElement::destroyed, [=](QObject* destroyedObject)
	{
		auto destroyedElement = dynamic_cast<TaskbarElement*>(destroyedObject);
		if (!destroyedElement) return;
		_ui->frameLayout->removeWidget(destroyedElement);
	});
}

void SystemTaskbar::updateClock()
{
	auto currentTime = QTime::currentTime();

	_ui->clockLabel->setText(currentTime.toString("hh:mm A"));
}
