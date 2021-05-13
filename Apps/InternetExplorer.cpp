#include "InternetExplorer.h"
#include "ui_InternetExplorer.h"

InternetExplorer::InternetExplorer() : App(WindowTitleBar::buttons::NORMAL)
  , _ui(new Ui::InternetExplorer)
  , _uiWidget(new QMainWindow())
  , _uiLayout(new QBoxLayout(QBoxLayout::TopToBottom, getContentPlaceholder()))
{
	_uiWidget->setAttribute(Qt::WA_ShowWithoutActivating);

	_ui->setupUi(_uiWidget);
	_uiLayout->addWidget(_uiWidget);
	_uiLayout->setMargin(0);

	getTitleBar()->setTitle("Internet Explorer");
	taskbarTitle = "Internet Explorer";

	auto sizeGrip = _ui->statusbar->findChild<QSizeGrip*>();
	sizeGrip->setFixedSize(_ui->statusbar->height(), _ui->statusbar->height());

	_ui->statusbar->setContentsMargins(3, 0, 3, 0);
	_statusLabel = new QLabel("Done");
	_ui->statusbar->addWidget(_statusLabel);

	//Create address bar
	_addressLabel = new QLabel("Address:");
	_ui->addressBar->addWidget(_addressLabel);
	_addressComboBox = new QComboBox();
	_addressComboBox->setEditable(true);
	_addressComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	_ui->addressBar->addWidget(_addressComboBox);

	//Change stylesheet to old look
	QFile stylesheetFile(":/Resources/Style/WebEngine.css");
	stylesheetFile.open(QIODevice::ReadOnly);
	QString stylesheet = QLatin1String(stylesheetFile.readAll());

	QWebEngineScript script;
	script.setName("stylesheet");
	script.setSourceCode(cssLoaderJS.arg("stylesheet", stylesheet.simplified()));
	script.setInjectionPoint(QWebEngineScript::DocumentReady);
	script.setRunsOnSubFrames(true);
	script.setWorldId(QWebEngineScript::ApplicationWorld);
	_ui->webEngineView->page()->scripts().insert(script);

	QObject::connect(_ui->webEngineView->page(), &QWebEnginePage::loadStarted, [=]()
	{
		_statusLabel->setText("Loading... please just wait a moment");
	});

	QObject::connect(_ui->webEngineView->page(), &QWebEnginePage::loadFinished, [=]()
	{
		_statusLabel->setText("Done");
	});

	QObject::connect(_ui->action_toolbar_back, &QAction::triggered, _ui->webEngineView, &QWebEngineView::back);
	QObject::connect(_ui->action_toolbar_forward, &QAction::triggered, _ui->webEngineView, &QWebEngineView::forward);
	QObject::connect(_ui->action_toolbar_stop, &QAction::triggered, _ui->webEngineView, &QWebEngineView::stop);
	QObject::connect(_ui->action_toolbar_refresh, &QAction::triggered, _ui->webEngineView, &QWebEngineView::reload);

	QObject::connect(_ui->action_view_toolbar, &QAction::triggered, _ui->toolBar, &QToolBar::setVisible);
	QObject::connect(_ui->action_view_statusbar, &QAction::triggered, _ui->statusbar, &QStatusBar::setVisible);
	QObject::connect(_ui->action_view_stop, &QAction::triggered, _ui->webEngineView, &QWebEngineView::stop);
	QObject::connect(_ui->action_view_refresh, &QAction::triggered, _ui->webEngineView, &QWebEngineView::reload);

	QObject::connect(_ui->action_go_back, &QAction::triggered, _ui->webEngineView, &QWebEngineView::back);
	QObject::connect(_ui->action_go_forward, &QAction::triggered, _ui->webEngineView, &QWebEngineView::forward);

	QObject::connect(_addressComboBox, &QComboBox::textActivated, this, &InternetExplorer::addressChanged);
}

InternetExplorer::~InternetExplorer()
{
	delete _statusLabel;
	delete _addressComboBox;
	delete _addressLabel;
	delete _uiLayout;
	delete _uiWidget;
	delete _ui;
}

void InternetExplorer::addressChanged(const QString& address)
{
	QUrl url = QUrl::fromUserInput(address);
	url.setScheme("https");

	_ui->webEngineView->load(url);
}
