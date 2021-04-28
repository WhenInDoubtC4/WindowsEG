#pragma once

#include <QObject>
#include <QComboBox>
#include <QJsonArray>

#include "AppControl.h"
#include "Util/LineEditList.h"

#define ROOT_NAME "Notepad"
#define CUT_ERROR_MESSAGES "cutErrorMessages"
#define COPY_ERROR_MESSAGES "copyErrorMessages"

class NotepadControl : public AppControl
{
	Q_OBJECT

protected:
	virtual void setSaveData(QJsonObject& data) override;
	virtual void load(QJsonObject& data) override;

private:
	APP_CONTROL
	NotepadControl();

	QComboBox* _modeComboBox = nullptr;

	LineEditList* _cutErrorMessagesLineEditList = nullptr;
	LineEditList* _copyErrorMessagesLineEditList = nullptr;

	const QList<QString> _defaultCutErrorMessages = QList<QString>
	{
		"Windows has encountered a cliboard error",
		"Windows cannot cut this value",
		"Clipboard error encountered while trying to cut this value",
		"Unknown exception encountered",
		"Unable to cut this value"
	};

	const QList<QString> _defaultCopyErrorMessages = QList<QString>
	{
		"Windows has encountered a cliboard error",
		"Windows was unable to copy this value",
		"Clipboard error encountered while trying to copy this value",
		"Unknown exception encountered",
		"Unable to copy this value"
	};
};

