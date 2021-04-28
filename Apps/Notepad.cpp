#include "Notepad.h"
#include "ui_Notepad.h"

#include <QDebug>

Notepad::Notepad() : App(WindowTitleBar::buttons::NORMAL)
  , _ui(new Ui::Notepad)
  , _uiWidget(new QMainWindow())
  , _uiLayout(new QBoxLayout(QBoxLayout::TopToBottom, getContentPlaceholder()))
{
	_ui->setupUi(_uiWidget);
	_uiLayout->addWidget(_uiWidget);
	_uiLayout->setMargin(0);

	enableFrameResize();
	getTitleBar()->setTitle("Notepad");
	taskbarTitle = "Notepad";

	//Config
	QObject::connect(AppControl::getInstance<NotepadControl>(), &AppControl::configApplied, this, &Notepad::onConfigApplied);

	QObject::connect(_ui->action_edit_undo, &QAction::triggered, _ui->textEdit, &QTextEdit::undo);
	QObject::connect(_ui->action_edit_cut, &QAction::triggered, _ui->textEdit, &QTextEdit::cut);
	QObject::connect(_ui->action_edit_copy, &QAction::triggered, _ui->textEdit, &QTextEdit::copy);
	QObject::connect(_ui->action_edit_paste, &QAction::triggered, _ui->textEdit, &QTextEdit::paste);
	QObject::connect(_ui->action_edit_delete, &QAction::triggered, this, &Notepad::deleteSelection);
	QObject::connect(_ui->action_edit_selectAll, &QAction::triggered, _ui->textEdit, &QTextEdit::selectAll);
}

Notepad::~Notepad()
{
	delete _uiLayout;
	delete _uiWidget;
	delete _ui;
}

void Notepad::onConfigApplied(QByteArray& configData)
{
	QDataStream stream(&configData, QIODevice::ReadOnly);
	QString a, b;
	stream >> a >> b;
	qDebug() << "Config applied" << a << b;
}

void Notepad::deleteSelection()
{
	_ui->textEdit->textCursor().removeSelectedText();
}
