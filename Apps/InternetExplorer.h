#pragma once

#include <QObject>
#include <QMainWindow>
#include <QBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QSizeGrip>
#include <QWebEngineScript>
#include <QWebEngineScriptCollection>

#include "App.h"

const QString cssLoaderJS = R"(
(function() {
	css = document.createElement('style');
	css.type = 'text/css';
	css.id = '%1';
	document.head.appendChild(css);
	css.innerText = '%2';
})()
)";

namespace Ui
{
	class InternetExplorer;
}

class InternetExplorer : public App
{
	Q_OBJECT
public:
	InternetExplorer();
	~InternetExplorer();

private:
	Ui::InternetExplorer* _ui = nullptr;
	QMainWindow* _uiWidget = nullptr;
	QBoxLayout* _uiLayout = nullptr;

	QLabel* _addressLabel = nullptr;
	QComboBox* _addressComboBox = nullptr;

	QLabel* _statusLabel = nullptr;

private slots:
	void addressChanged(const QString& address);
};

