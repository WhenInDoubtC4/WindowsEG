#include "DesktopIconTextEdit.h"

DesktopIconTextEdit::DesktopIconTextEdit(QWidget* parent) : QTextEdit(parent)
{

}

void DesktopIconTextEdit::focusOutEvent(QFocusEvent* e)
{
	QTextEdit::focusOutEvent(e);

	//I had to subclass the entire goddamn thing just for this
	emit focusOut();
}

void DesktopIconTextEdit::keyPressEvent(QKeyEvent* e)
{
	//Oh and also for this but I didn't think of that when I wrote the previous comment
	if (e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter)
	{
		emit enterPressed();
		return;
	}

	QTextEdit::keyPressEvent(e);
}
