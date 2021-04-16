#include "TaskbarElement.h"

TaskbarElement::TaskbarElement(const QString& text, const QPixmap* icon)
	: _layout(new QHBoxLayout(this))
	, _textLabel(new QLabel())
{
	_layout->setMargin(0);
	_layout->setContentsMargins(6, 2, 2, 2);

	setCheckable(true);
	setChecked(false);
	setFixedWidth(WIDTH);

	if (icon)
	{
		_iconLabel = new QLabel();
		_iconLabel->setPixmap(*icon);
		_layout->addWidget(_iconLabel, 0, Qt::AlignLeft);
	}

	_textLabel->setText(text);
	_textLabel->setStyleSheet("color: #000000");
	_layout->addWidget(_textLabel, 0, Qt::AlignLeft);

	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
}

TaskbarElement::~TaskbarElement()
{
	delete _textLabel;
	delete _layout;
}
