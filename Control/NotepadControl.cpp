#include "NotepadControl.h"

NotepadControl::NotepadControl() : AppControl()
  , _clipboardModeComboBox(new QComboBox)
{
	CONSTRUCT_ONCE

	_clipboardModeComboBox->addItem("Broken text");
	_clipboardModeComboBox->addItem("Error messages");

	_cutErrorMessagesLineEditList = new LineEditList(_defaultCutErrorMessages);
	_copyErrorMessagesLineEditList = new LineEditList(_defaultCopyErrorMessages);
	_pasteErrorMessagesLineEditList = new LineEditList(_defaultPasteErrorMessages);

	_cutErrorMessageChanceSpinBox = new PercentageSpinBox(0.25);
	_copyErrorMessageChanceSpinBox = new PercentageSpinBox(0.25);
	_pasteErrorMessageChanceSpinBox = new PercentageSpinBox(0.5);

	_pasteTextFracionSpinBox = new RangedSpinBox(0., 1., 0., 1.);

	_brokenKeyboardCheckBox = new QCheckBox();
	_brokenKeyboardCheckBox->setChecked(true);
	_duplicateCharChanceSpinBox = new PercentageSpinBox(0.1);
	_missingCharChanceSpinBox = new PercentageSpinBox(0.1);

	_saveDialogLoopTextLineEditList = new LineEditList(_defaultSaveDialogLoopText);
	_saveDialogLoopSpinBox = new RangedSpinBox(0., 100., 1., 5., 1.);
	//NOTE: Disguise as int spin box
	_saveDialogLoopSpinBox->setPrecision(0);

	getControlItemsList()
			<< row{new QLabel("Clipboard mode"), _clipboardModeComboBox}
			<< row{new QLabel("Cut error message"), _cutErrorMessagesLineEditList}
			<< row{new QLabel("Cut error message chance"), _cutErrorMessageChanceSpinBox}
			<< row{new QLabel("Copy error messages"), _copyErrorMessagesLineEditList}
			<< row{new QLabel("Copy error message chance"), _copyErrorMessageChanceSpinBox}
			<< row{new QLabel("Paste error message"), _pasteErrorMessagesLineEditList}
			<< row{new QLabel("Paste error message chance"), _pasteErrorMessageChanceSpinBox}
			<< row{new QLabel("Paste text fraction"), _pasteTextFracionSpinBox}
			<< row{new QLabel("Break keyboard"), _brokenKeyboardCheckBox}
			<< row{new QLabel("Duplicate character chance"), _duplicateCharChanceSpinBox}
			<< row{new QLabel("Missing character chance"), _missingCharChanceSpinBox}
			<< row{new QLabel("Save dialog text"), _saveDialogLoopTextLineEditList}
			<< row{new QLabel("Save dialog loop count"), _saveDialogLoopSpinBox};
}

void NotepadControl::setSaveData(QJsonObject& data)
{
	QJsonObject rootObject;
	rootObject[MODE] = _clipboardModeComboBox->currentIndex();
	rootObject[CUT_ERROR_MESSAGES] = QJsonArray::fromStringList(_cutErrorMessagesLineEditList->getTextInAllFields());
	rootObject[COPY_ERROR_MESSAGES] = QJsonArray::fromStringList(_copyErrorMessagesLineEditList->getTextInAllFields());
	rootObject[PASTE_ERROR_MESSAGES] = QJsonArray::fromStringList(_pasteErrorMessagesLineEditList->getTextInAllFields());

	rootObject[CUT_ERROR_MESSAGE_CHANCE] = _cutErrorMessageChanceSpinBox->getPercentage();
	rootObject[COPY_ERROR_MESSAGE_CHANCE] = _copyErrorMessageChanceSpinBox->getPercentage();
	rootObject[PASTE_ERROR_MESSAGE_CHANCE] = _pasteErrorMessageChanceSpinBox->getPercentage();

	rootObject[PASTE_TEXT_FRACTION] = _pasteTextFracionSpinBox->getJsonObject();

	rootObject[BREAK_KEYBOARD] = _brokenKeyboardCheckBox->isChecked();
	rootObject[DUPLICATE_CHAR_CHANCE] = _duplicateCharChanceSpinBox->getPercentage();
	rootObject[MISSING_CHAR_CHANCE] = _missingCharChanceSpinBox->getPercentage();

	rootObject[SAVE_DIALOG_LOOP_TEXT] = QJsonArray::fromStringList(_saveDialogLoopTextLineEditList->getTextInAllFields());
	rootObject[SAVE_DIALOG_LOOP_COUNT] = _saveDialogLoopSpinBox->getJsonObject();

	data[ROOT_NAME] = rootObject;
}

void NotepadControl::load(QJsonObject& data)
{
	_cutErrorMessagesLineEditList->clear();
	_copyErrorMessagesLineEditList->clear();
	_pasteErrorMessagesLineEditList->clear();
	_saveDialogLoopTextLineEditList->clear();

	QJsonObject rootObject = data[ROOT_NAME].toObject();

	_clipboardModeComboBox->setCurrentIndex(rootObject[MODE].toInt());

	_cutErrorMessagesLineEditList->addFromStringList(jsonToStringList(rootObject[CUT_ERROR_MESSAGES]));
	_copyErrorMessagesLineEditList->addFromStringList(jsonToStringList(rootObject[COPY_ERROR_MESSAGES]));
	_pasteErrorMessagesLineEditList->addFromStringList(jsonToStringList(rootObject[PASTE_ERROR_MESSAGES]));

	_cutErrorMessageChanceSpinBox->setPercentage(rootObject[CUT_ERROR_MESSAGE_CHANCE].toDouble());
	_copyErrorMessageChanceSpinBox->setPercentage(rootObject[COPY_ERROR_MESSAGE_CHANCE].toDouble());
	_pasteErrorMessageChanceSpinBox->setPercentage(rootObject[PASTE_ERROR_MESSAGE_CHANCE].toDouble());

	_brokenKeyboardCheckBox->setChecked(rootObject[BREAK_KEYBOARD].toBool());
	_duplicateCharChanceSpinBox->setPercentage(rootObject[DUPLICATE_CHAR_CHANCE].toDouble());
	_missingCharChanceSpinBox->setPercentage(rootObject[MISSING_CHAR_CHANCE].toDouble());

	_pasteTextFracionSpinBox->loadFromJson(rootObject[PASTE_TEXT_FRACTION]);

	_saveDialogLoopTextLineEditList->addFromStringList(jsonToStringList(rootObject[SAVE_DIALOG_LOOP_TEXT]));
	_saveDialogLoopSpinBox->loadFromJson(rootObject[SAVE_DIALOG_LOOP_COUNT]);
}

void NotepadControl::resetToDefault()
{
	_clipboardModeComboBox->setCurrentIndex(0);

	_cutErrorMessagesLineEditList->clear();
	_cutErrorMessagesLineEditList->addFromStringList(_defaultCutErrorMessages);
	_copyErrorMessagesLineEditList->clear();
	_copyErrorMessagesLineEditList->addFromStringList(_defaultCopyErrorMessages);
	_pasteErrorMessagesLineEditList->clear();
	_pasteErrorMessagesLineEditList->addFromStringList(_defaultPasteErrorMessages);
	_saveDialogLoopTextLineEditList->clear();
	_saveDialogLoopTextLineEditList->addFromStringList(_defaultSaveDialogLoopText);

	_cutErrorMessageChanceSpinBox->setPercentage(0.25);
	_copyErrorMessageChanceSpinBox->setPercentage(0.25);
	_pasteErrorMessageChanceSpinBox->setPercentage(0.5);

	_pasteTextFracionSpinBox->setMin(0.);
	_pasteTextFracionSpinBox->setMax(1.);

	_brokenKeyboardCheckBox->setChecked(true);
	_duplicateCharChanceSpinBox->setPercentage(0.1);
	_missingCharChanceSpinBox->setPercentage(0.1);

	_saveDialogLoopSpinBox->setMin(0.);
	_saveDialogLoopSpinBox->setMax(5.);
}

NotepadControl::clipboardMode NotepadControl::getClipboardMode()
{
	return static_cast<clipboardMode>(_clipboardModeComboBox->currentIndex());
}
