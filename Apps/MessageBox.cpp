#include "MessageBox.h"
#include "ui_MessageBox.h"

MessageBox::MessageBox(messageBoxType type, const QString& title, const QString& text, messageBoxButtonSet buttonSet) : App(WindowTitleBar::buttons::CLOSE_ONLY)
  , _ui(new Ui::MessageBox)
{
	_ui->setupUi(getContentPlaceholder());

	getTitleBar()->setTitle(title);
	_ui->textLabel->setText(text);

	taskbarTitle = title;
	taskbarAllowGrouping = true;

	switch (type)
	{
		case MessageBox::messageBoxType::INFO:
			_ui->iconLabel->setPixmap(QPixmap(":/Resources/Style/Assets/Icons/Info.ico"));
			break;
		case MessageBox::messageBoxType::WARNING:
			_ui->iconLabel->setPixmap(QPixmap(":/Resources/Style/Assets/Icons/Warning.ico"));
			break;
		case MessageBox::messageBoxType::ERROR:
			_ui->iconLabel->setPixmap(QPixmap(":/Resources/Style/Assets/Icons/Error.ico"));
			break;
	}

	//Create buttons
	switch (buttonSet)
	{
		case MessageBox::messageBoxButtonSet::OK:
			_buttons << new QPushButton("OK");
			break;
		case MessageBox::messageBoxButtonSet::OK_CANCEL:
			_buttons << new QPushButton("OK") << new QPushButton("Cancel");
			break;
		case MessageBox::messageBoxButtonSet::YES_NO:
			_buttons << new QPushButton("Yes") << new QPushButton("No");
			break;
		case MessageBox::messageBoxButtonSet::YES_NO_CANCEL:
			_buttons << new QPushButton("Yes") << new QPushButton("No") << new QPushButton("Cancel");
			break;
		case MessageBox::messageBoxButtonSet::CUSTOM:
			break;
	}

	//Add buttons to the UI and set style
	_ui->buttonLayout->addStretch();
	for (QPushButton* button : qAsConst(_buttons))
	{
		static int index = 1;
		button->setMinimumWidth(BUTTON_MIN_WIDTH);
		_ui->buttonLayout->insertWidget(index++, button, 0, Qt::AlignCenter);
	}
	_ui->buttonLayout->addStretch();

	//Ensure min size
	adjustSize();
}

MessageBox::~MessageBox()
{
	while(!_buttons.isEmpty()) delete _buttons.takeLast();
	delete _ui;
}

QList<QPushButton*>& MessageBox::getButtons()
{
	return _buttons;
}
