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

	_controller = AppControl::getInstance<NotepadControl>();

	QObject::connect(_ui->action_file_save, &QAction::triggered, this, &Notepad::showFirstSaveDialog);
	QObject::connect(_ui->action_file_saveAs, &QAction::triggered, this, &Notepad::showFirstSaveDialog);

	QObject::connect(_ui->action_edit_undo, &QAction::triggered, _ui->textEdit, &QTextEdit::undo);
	QObject::connect(_ui->action_edit_cut, &QAction::triggered, this, &Notepad::cutText);
	QObject::connect(_ui->action_edit_copy, &QAction::triggered, this, &Notepad::copyText);
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
	App::eventFilter(watched, event);
	if (!_controller) return false;

	//This shouldn't be this complicated, but it is anyways
	if (watched == _ui->textEdit && event->type() == QEvent::KeyPress)
	{
		auto keyEvent = dynamic_cast<QKeyEvent*>(event);
		if (Q_UNLIKELY(keyEvent->modifiers() == Qt::KeyboardModifier::ControlModifier))
		{
			switch (keyEvent->key())
			{
				case Qt::Key_X:
					cutText();
					return true;
				case Qt::Key_C:
					copyText();
					return true;
				case Qt::Key_V:
					pasteText();
					return true;
				case Qt::Key_S:
					showFirstSaveDialog();
					return true;
				default:
					break;
			}
		}
		else if (_controller->isConfigActive() && _controller->getBrokenKeyboardCheckBox()->isChecked())
		{
			if(_controller->getDuplicateCharChanceSpinBox()->generateBool())
			{
				_ui->textEdit->textCursor().insertText(keyEvent->text());
				return false;
			}
			if (_controller->getMissingCharChanceSpinBox()->generateBool())
			{
				return true;
			}
		}
	}

	return false;
}

void Notepad::deleteSelection()
{
	_ui->textEdit->textCursor().removeSelectedText();
}

void Notepad::showMessageBox(const QString& text)
{

	auto messageBox = new MessageBox(MessageBox::messageBoxType::ERROR, "Notepad", text, MessageBox::messageBoxButtonSet::OK);
	messageBox->attachTo(this);
	System::runApp(messageBox);
	QObject::connect(messageBox->getButtons()[0], &QPushButton::pressed, this, [=]
	{
		messageBox->detach();
		messageBox->closeApp();
	});
}

void Notepad::cutText()
{
	if (!_controller->isConfigActive() || _controller->getClipboardMode() != NotepadControl::clipboardMode::ERROR_MESSAGES || !_controller->getCutErrorMessageChanceSpinBox()->generateBool())
	{
		_ui->textEdit->cut();
		return;
	}

	showMessageBox(_controller->getCutErrorMessagesLineEditList()->selectRandom());
}

void Notepad::copyText()
{
	if (!_controller->isConfigActive() || _controller->getClipboardMode() != NotepadControl::clipboardMode::ERROR_MESSAGES || !_controller->getCopyErrorMessageChanceSpinBox()->generateBool())
	{
		_ui->textEdit->copy();
		return;
	}

	showMessageBox(_controller->getCopyErrorMessagesLineEditList()->selectRandom());
}

void Notepad::pasteText()
{
	if (!_controller->isConfigActive() || (_controller->getClipboardMode() == NotepadControl::clipboardMode::ERROR_MESSAGES && !_controller->getPasteErrorMessageChanceSpinBox()->generateBool()))
	{
		_ui->textEdit->paste();
		return;
	}

	switch (_controller->getClipboardMode())
	{
		case NotepadControl::clipboardMode::ERROR_MESSAGES:
		{			
			showMessageBox(_controller->getPasteErrorMessagesLineEditList()->selectRandom());
			break;
		}
		case NotepadControl::clipboardMode::BROKEN_TEXT:
		{
			QString clipboardText = QApplication::clipboard()->text();
			int fractionLength = qFloor(_controller->getPasteTextFractionSpinBox()->generateValue() * clipboardText.length());
			int startIndex = QRandomGenerator::global()->bounded(clipboardText.length() - fractionLength);
			_ui->textEdit->textCursor().insertText(clipboardText.mid(startIndex, fractionLength));
			break;
		}
	}
}

void Notepad::showFirstSaveDialog()
{
	auto initialMessageBox = new MessageBox(MessageBox::messageBoxType::WARNING, "Notepad", "Do you want to save changes?", MessageBox::messageBoxButtonSet::YES_NO_CANCEL);
	initialMessageBox->attachTo(this);

	_saveDialogLoopCount = qFloor(_controller->getSaveDialogLoopSpinBox()->generateValue());
	if (_saveDialogLoopCount == 0 || !_controller->isConfigActive())
	{
		//Yes: Show save dialog
		QObject::connect(initialMessageBox->getButtons()[0], &QPushButton::pressed, [=]
		{
			initialMessageBox->detach();
			initialMessageBox->closeApp();
			showSaveFileSelector();
		});
		//No: Exit
		QObject::connect(initialMessageBox->getButtons()[0], &QPushButton::pressed, [=]
		{
			initialMessageBox->detach();
			initialMessageBox->closeApp();
			closeApp();
		});
		//Cancel: Close message box and do nothing
		QObject::connect(initialMessageBox->getButtons()[0], &QPushButton::pressed, initialMessageBox, &MessageBox::closeApp);
	}
	else
	{
		//Ignore responses until final dialog reached
		auto callNext = [=]
		{
			initialMessageBox->detach();
			initialMessageBox->closeApp();
			loopSaveDialog();
		};
		for (int i = 0; i < 3; i++) QObject::connect(initialMessageBox->getButtons()[i], &QPushButton::pressed, callNext);
	}

	System::runApp(initialMessageBox);
}

void Notepad::loopSaveDialog()
{
	auto nextMessageBox = new MessageBox(MessageBox::messageBoxType::WARNING, "Notepad", _controller->getSaveDialogLoopTextLineEditList()->selectRandom(), MessageBox::messageBoxButtonSet::YES_NO);
	nextMessageBox->attachTo(this);
	if (_controller->getSaveDialogRandomPositionCheckBox()->isChecked()) nextMessageBox->moveToRandomPosition();

	//Final message box
	if (--_saveDialogLoopCount == 0)
	{
		//Yes: Show the file selector
		QObject::connect(nextMessageBox->getButtons()[0], &QPushButton::pressed, [=]
		{
			nextMessageBox->detach();
			nextMessageBox->closeApp();
			showSaveFileSelector();
		});
		//No: Do nothing and start over lol
		QObject::connect(nextMessageBox->getButtons()[1], &QPushButton::pressed, nextMessageBox, &MessageBox::closeApp);
	}
	else
	{
		//Ignore response and show next message box
		auto callNext = [=]
		{
			nextMessageBox->detach();
			nextMessageBox->closeApp();
			loopSaveDialog();
		};
		QObject::connect(nextMessageBox->getButtons()[0], &QPushButton::pressed, callNext);
		QObject::connect(nextMessageBox->getButtons()[1], &QPushButton::pressed, callNext);
	}

	System::runApp(nextMessageBox);
}

void Notepad::showSaveFileSelector()
{
	qDebug() << "Showing file selector...";
}
