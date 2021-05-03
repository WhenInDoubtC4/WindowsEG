#pragma once

#include <QObject>
#include <QComboBox>
#include <QCheckBox>
#include <QJsonArray>

#include "AppControl.h"
#include "Util/LineEditList.h"
#include "Util/RangedSpinBox.h"
#include "Util/PercentageSpinBox.h"

#define ROOT_NAME "Notepad"
#define MODE "mode"
#define CUT_ERROR_MESSAGES "cutErrorMessages"
#define CUT_ERROR_MESSAGE_CHANCE "cutErrorMessageChance"
#define COPY_ERROR_MESSAGES "copyErrorMessages"
#define COPY_ERROR_MESSAGE_CHANCE "copyErrorMessageChance"
#define PASTE_ERROR_MESSAGES "pasteErrorMessages"
#define PASTE_ERROR_MESSAGE_CHANCE "pasteErrorMessageChance"
#define PASTE_TEXT_FRACTION "pasteTextFraction"
#define BREAK_KEYBOARD "breakKeyboard"
#define DUPLICATE_CHAR_CHANCE "duplicateCharChance"
#define MISSING_CHAR_CHANCE "missingCharChance"
#define SAVE_DIALOG_LOOP_TEXT "saveDialogLoopText"
#define SAVE_DIALOG_LOOP_COUNT "saveDialogLoopCount"

class NotepadControl : public AppControl
{
	Q_OBJECT
public:
	enum clipboardMode
	{
		BROKEN_TEXT,
		ERROR_MESSAGES
	};
	Q_ENUM(clipboardMode)

	clipboardMode getClipboardMode();
	LineEditList* getCutErrorMessagesLineEditList(){ return _cutErrorMessagesLineEditList; };
	LineEditList* getCopyErrorMessagesLineEditList(){ return _copyErrorMessagesLineEditList; };
	LineEditList* getPasteErrorMessagesLineEditList(){ return _pasteErrorMessagesLineEditList; };

	PercentageSpinBox* getCutErrorMessageChanceSpinBox() { return _cutErrorMessageChanceSpinBox; };
	PercentageSpinBox* getCopyErrorMessageChanceSpinBox() { return _copyErrorMessageChanceSpinBox; };
	PercentageSpinBox* getPasteErrorMessageChanceSpinBox() { return _pasteErrorMessageChanceSpinBox; };

	RangedSpinBox* getPasteTextFractionSpinBox(){ return _pasteTextFracionSpinBox; };

	QCheckBox* getBrokenKeyboardCheckBox(){ return _brokenKeyboardCheckBox; };
	PercentageSpinBox* getDuplicateCharChanceSpinBox(){ return _duplicateCharChanceSpinBox; };
	PercentageSpinBox* getMissingCharChanceSpinBox(){ return _missingCharChanceSpinBox; };

	LineEditList* getSaveDialogLoopTextLineEditList(){ return _saveDialogLoopTextLineEditList; };
	RangedSpinBox* getSaveDialogLoopSpinBox(){ return _saveDialogLoopSpinBox; };

protected:
	virtual void setSaveData(QJsonObject& data) override;
	virtual void load(QJsonObject& data) override;
	virtual void resetToDefault() override;

private:
	APP_CONTROL
	NotepadControl();

	QComboBox* _clipboardModeComboBox = nullptr;

	LineEditList* _cutErrorMessagesLineEditList = nullptr;
	LineEditList* _copyErrorMessagesLineEditList = nullptr;
	LineEditList* _pasteErrorMessagesLineEditList = nullptr;
	PercentageSpinBox* _copyErrorMessageChanceSpinBox = nullptr;
	PercentageSpinBox* _cutErrorMessageChanceSpinBox = nullptr;
	PercentageSpinBox* _pasteErrorMessageChanceSpinBox = nullptr;

	RangedSpinBox* _pasteTextFracionSpinBox = nullptr;

	QCheckBox* _brokenKeyboardCheckBox = nullptr;
	PercentageSpinBox* _duplicateCharChanceSpinBox = nullptr;
	PercentageSpinBox* _missingCharChanceSpinBox = nullptr;

	LineEditList* _saveDialogLoopTextLineEditList = nullptr;
	RangedSpinBox* _saveDialogLoopSpinBox = nullptr;

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

	const QList<QString> _defaultSaveDialogLoopText = QList<QString>
	{
		"Are you sure?",
		"Are you absolutely certain?",
		"Have you double checked?"
	};
};
