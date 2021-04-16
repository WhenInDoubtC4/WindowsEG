#pragma once

#include <QMenu>
#include <QObject>
#include <QWidget>
#include <QWidgetAction>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QMouseEvent>

#include "StartMenuItem.h"

constexpr int COVER_WIDTH = 32;

class StartMenu : public QMenu
{
	Q_OBJECT

	struct actionElement
	{
		QWidgetAction* action;
		StartMenuItem* actionWidget;
		QHBoxLayout* layout;
		QWidget* paddingWidget;
		QLabel* iconLabel;
		QLabel* textLabel;
		QSpacerItem* hSpacer;
		QLabel* submenuLabel;
	};

public:
	StartMenu(QWidget* parent = nullptr);

	int getTotalHeight() const;

	QAction* addItem(const QString& text, const QPixmap& icon, const bool hasSubmenu = false);

private:
	QWidget* _coverWidget = nullptr;
};

