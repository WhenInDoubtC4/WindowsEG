#include "DesktopIcon.h"
#include "ui_DesktopIcon.h"

DesktopIcon::DesktopIcon(QWidget* parent, const QString& title, QPixmap* icon) : QWidget(parent)
  , _ui(new Ui::DesktopIcon)
{
	_ui->setupUi(this);

	setFocusPolicy(Qt::ClickFocus);
	setContextMenuPolicy(Qt::CustomContextMenu);

	_ui->titleLabel->setText(title);
	if (icon) _ui->iconLabel->setPixmap(*icon);
	_ui->lineEdit->setProperty("iconTitle", true);
	_ui->lineEdit->setText(_ui->titleLabel->text());

	staticMaxSize = property("maximumSize").toSize();

	QObject::connect(this, &DesktopIcon::customContextMenuRequested, this, &DesktopIcon::showContextMenu);

	QObject::connect(_ui->lineEdit, &DesktopIconTextEdit::enterPressed, [=]()
	{
		rename(false);
	});
}

DesktopIcon::~DesktopIcon()
{
	delete _ui;
}

void DesktopIcon::setSelected(bool selected)
{
	if (selected)
	{
		_ui->titleStack->setStyleSheet("background: rgba(0, 0, 128, 0.5)");
	}
	else
	{
		_ui->titleStack->setStyleSheet("background: transparent");
	}
}

void DesktopIcon::mousePressEvent(QMouseEvent* event)
{
	QWidget::mousePressEvent(event);

	if (event->buttons() != Qt::LeftButton) return;

	_capturedMousePosition = event->pos();

	setSelected(true);
}

void DesktopIcon::focusOutEvent(QFocusEvent* event)
{
	QWidget::focusOutEvent(event);

	if (_ignoreUnfocusOnce)
	{
		_ignoreUnfocusOnce = false;
		return;
	}

	setSelected(false);
	rename(false);
}

void DesktopIcon::mouseReleaseEvent(QMouseEvent* event)
{
	QWidget::mouseReleaseEvent(event);

	_dragStarted = false;
}

void DesktopIcon::mouseDoubleClickEvent(QMouseEvent* event)
{
	QWidget::mouseDoubleClickEvent(event);

	emit onOpened();
}

void DesktopIcon::mouseMoveEvent(QMouseEvent* event)
{
	QWidget::mouseMoveEvent(event);

	if (event->buttons() != Qt::LeftButton || _dragStarted) return;

	//Start drag
	if (QPoint(event->pos() - _capturedMousePosition).manhattanLength() >= QApplication::startDragDistance())
	{
		_initalPosition = pos();
		_dragStarted = true;

		//Set drag data with ptr address of class
		QByteArray iconData;
		QDataStream iconDataStream(&iconData, QIODevice::WriteOnly);
		iconDataStream << reinterpret_cast<qulonglong>(this) << pos();

		auto mimeData = new QMimeData();
		mimeData->setData(mimeType, iconData);

		auto drag = new QDrag(this);
		drag->setMimeData(mimeData);
		drag->exec(Qt::MoveAction);
	}
}

void DesktopIcon::drop()
{
	_dragStarted = false;
}

void DesktopIcon::showContextMenu(const QPoint& pos)
{
	auto contextMenu = new QMenu(this);

	contextMenu->addAction("Open", openActionSlot);
	contextMenu->addSeparator();
	contextMenu->addAction("Send to");
	contextMenu->addSeparator();
	contextMenu->addAction("Cut", cutActionSlot);
	contextMenu->addAction("Copy", copyActionSlot);
	contextMenu->addSeparator();
	contextMenu->addAction("Create Shortcut", createShortcutActionSlot);
	contextMenu->addAction("Delete", deleteActionSlot);
	contextMenu->addAction("Rename", renameActionSlot);
	contextMenu->addSeparator();
	contextMenu->addAction("Properties", propertiesActionSlot);
	contextMenu->popup(mapToGlobal(pos));

	//Highlight icon while menu is visible
	setSelected(true);
	QObject::connect(contextMenu, &QMenu::aboutToHide, this, [=]()
	{
		setSelected(false);
	});
}

void DesktopIcon::rename(bool rename)
{
	if (rename)
	{
		_ignoreUnfocusOnce = true;
		_ui->lineEdit->setText(_ui->titleLabel->text());
		_ui->titleStack->setCurrentIndex(1);
		_ui->lineEdit->setFocus();
		_ui->lineEdit->moveCursor(QTextCursor::End);
		_ui->lineEdit->selectAll();
		_ui->lineEdit->setStyleSheet("background: rgba(0, 0, 128, 0.7)");
		QObject::connect(_ui->lineEdit, &DesktopIconTextEdit::focusOut, [=]()
		{
			focusOutEvent(nullptr);
		});
	}
	else
	{
		_ui->titleLabel->setText(_ui->lineEdit->toPlainText());
		_ui->titleStack->setCurrentIndex(0);

		adjustSize();
	}
}
