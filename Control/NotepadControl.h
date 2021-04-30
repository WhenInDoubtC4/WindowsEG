#pragma once

#include <QObject>
#include <QComboBox>
#include <QJsonArray>

#include "AppControl.h"
#include "Util/LineEditList.h"
#include "Util/RangedSpinBox.h"

#define ROOT_NAME "Notepad"
#define MODE "mode"
#define CUT_ERROR_MESSAGES "cutErrorMessages"
#define COPY_ERROR_MESSAGES "copyErrorMessages"
#define PASTE_ERROR_MESSAGES "pasteErrorMessages"
#define MIN "min"
#define MAX "max"
#define PASTE_TEXT_FRACTION "pasteTextFraction"

class NotepadControl : public AppControl
{
	Q_OBJECT
public:
	enum mode
	{
		BROKEN_TEXT,
		ERROR_MESSAGES
	};
	Q_ENUM(mode)

	mode getMode();
	LineEditList* getCutErrorMessagesLineEditList();
	LineEditList* getPasteErrorMessagesLineEditList();
	RangedSpinBox* getPasteTextFractionSpinBox();

protected:
	virtual void setSaveData(QJsonObject& data) override;
	virtual void load(QJsonObject& data) override;

private:
	APP_CONTROL
	NotepadControl();

	QComboBox* _modeComboBox = nullptr;

	LineEditList* _cutErrorMessagesLineEditList = nullptr;
	LineEditList* _copyErrorMessagesLineEditList = nullptr;
	LineEditList* _pasteErrorMessagesLineEditList = nullptr;

	RangedSpinBox* _pasteTextFracionSpinBox = nullptr;

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

	const QList<QString> _defaultPasteErrorMessages = QList<QString>
	{
		"Windows has encountered a clipboard error",
		"Clipboard overflow error",
		"Unknown exception encountered"
	};
};

