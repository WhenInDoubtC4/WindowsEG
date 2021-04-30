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

	_ui->textEdit->installEventFilter(this);

	QObject::connect(_ui->action_edit_undo, &QAction::triggered, _ui->textEdit, &QTextEdit::undo);
	QObject::connect(_ui->action_edit_cut, &QAction::triggered, _ui->textEdit, &QTextEdit::cut);
	QObject::connect(_ui->action_edit_copy, &QAction::triggered, _ui->textEdit, &QTextEdit::copy);
	QObject::connect(_ui->action_edit_paste, &QAction::triggered, this, &Notepad::pasteText);
	QObject::connect(_ui->action_edit_delete, &QAction::triggered, this, &Notepad::deleteSelection);
	QObject::connect(_ui->action_edit_selectAll, &QAction::triggered, _ui->textEdit, &QTextEdit::selectAll);
}

Notepad::~Notepad()
{
	delete _uiLayout;
	delete _uiWidget;
	delete _ui;
}

bool Notepad::eventFilter(QObject* watched, QEvent* event)
{
	//This shouldn't be this complicated, but it is anyways
	if (watched == _ui->textEdit && event->type() == QEvent::KeyPress)
	{
		auto keyEvent = dynamic_cast<QKeyEvent*>(event);
		if (keyEvent->modifiers() == Qt::KeyboardModifier::ControlModifier && keyEvent->key() == Qt::Key_V)
		{
			event->ignore();
			pasteText();
			return true;
		}
	}

	App::eventFilter(watched, event);
	return false;
}

void Notepad::deleteSelection()
{
	_ui->textEdit->textCursor().removeSelectedText();
}

void Notepad::pasteText()
{
	auto controller = AppControl::getInstance<NotepadControl>();

	if (!controller || !controller->isConfigActive())
	{
		_ui->textEdit->paste();
		return;
	}

	switch (controller->getMode())
	{
		case NotepadControl::mode::ERROR_MESSAGES:
		{
			auto messageBox = new MessageBox(MessageBox::messageBoxType::ERROR, "Notepad", controller->getPasteErrorMessagesLineEditList()->selectRandom(), MessageBox::messageBoxButtonSet::OK);
			QObject::connect(messageBox->getButtons()->at(0), &QPushButton::pressed, messageBox, &MessageBox::deleteLater);
			messageBox->attachTo(this);
			System::runApp(messageBox);
			break;
		}
		case NotepadControl::mode::BROKEN_TEXT:
		{
			QString clipboardText = QApplication::clipboard()->text();
			int fractionLength = qFloor(controller->getPasteTextFractionSpinBox()->generateValue() * clipboardText.length());
			int startIndex = QRandomGenerator::global()->bounded(clipboardText.length() - fractionLength);
			_ui->textEdit->textCursor().insertText(clipboardText.mid(startIndex, fractionLength));
			break;
		}
	}
}
