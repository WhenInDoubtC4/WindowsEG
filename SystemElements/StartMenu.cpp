#include "StartMenu.h"

StartMenu::StartMenu(QWidget* parent) : QMenu(parent)
{
	//Sloppy af, found no better way to do it
	_coverWidget = new QWidget(this);
	_coverWidget->move(1, 1);
	_coverWidget->resize(COVER_WIDTH, height());
	_coverWidget->setStyleSheet("background: qlineargradient( x1:0 y1:0, x2:0 y2:1, stop:0 #000000, stop:1 blue);");
}

QAction* StartMenu::addItem(const QString& text, const QPixmap& icon, const bool hasSubmenu)
{
	actionElement item;

	item.action = new QWidgetAction(this);

	item.actionWidget = new StartMenuItem();

	item.layout = new QHBoxLayout(item.actionWidget);
	item.layout->setMargin(5);

	item.paddingWidget = new QWidget();
	item.paddingWidget->setMinimumSize(COVER_WIDTH, 1);
	item.paddingWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);
	item.paddingWidget->setStyleSheet("background: transparent");
	item.layout->addWidget(item.paddingWidget, 0, Qt::AlignLeft);

	item.iconLabel = new QLabel();
	item.iconLabel->setPixmap(icon);
	item.iconLabel->setStyleSheet("background: transparent");
	item.layout->addWidget(item.iconLabel, 0, Qt::AlignLeft);

	item.textLabel = new QLabel(text);
	item.textLabel->setStyleSheet("background: transparent; color: #000000;");
	item.layout->addWidget(item.textLabel, 0, Qt::AlignLeading);

	item.hSpacer = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
	item.layout->addItem(item.hSpacer);

	if (hasSubmenu)
	{
		item.submenuLabel = new QLabel();
		item.submenuLabel->setPixmap(QPixmap(":/resources/style/assets/arrow-right.png"));
		item.submenuLabel->setStyleSheet("background: transparent");
		item.layout->addWidget(item.submenuLabel, 0, Qt::AlignRight);
	}

	item.action->setDefaultWidget(item.actionWidget);
	addAction(item.action);

	//Sloppiness intensifies
	_coverWidget->raise();
	_coverWidget->resize(COVER_WIDTH, getTotalHeight());

	//Highlights on hover
	QObject::connect(item.action, &QWidgetAction::hovered, [=]
	{
		static actionElement previous = item;

		item.actionWidget->setHovered(true);
		item.textLabel->setStyleSheet("background: transparent; color: #ffffff;");

		if (previous.action != item.action)
		{
			previous.actionWidget->setHovered(false);
			previous.textLabel->setStyleSheet("background: transparent; color: #000000;");
		}

		previous = item;
	});

	//Mouse leave from action widget in case cursor leaves the menu
	QObject::connect(item.actionWidget, &StartMenuItem::leave, [=]
	{
		item.actionWidget->setHovered(false);
		item.textLabel->setStyleSheet("background: transparent; color: #000000;");
	});

	return item.action;
}

int StartMenu::getTotalHeight() const
{
	int totalHeight = 0;
	for (QAction* action : actions())
	{
		totalHeight += actionGeometry(action).height();
	}

	return totalHeight;
}
