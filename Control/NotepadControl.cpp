#include "NotepadControl.h"

NotepadControl::NotepadControl() : AppControl()
  , _modeComboBox(new QComboBox)
{
	CONSTRUCT_ONCE

	_modeComboBox->addItem("Broken text");
	_modeComboBox->addItem("Error messages");

	_cutErrorMessagesLineEditList = new LineEditList(_defaultCutErrorMessages);
	_copyErrorMessagesLineEditList = new LineEditList(_defaultCopyErrorMessages);
	_pasteErrorMessagesLineEditList = new LineEditList(_defaultPasteErrorMessages);

	_pasteTextFracionSpinBox = new RangedSpinBox();

	getControlItemsList()
			<< row{new QLabel("Mode"), _modeComboBox}
			<< row{new QLabel("Cut error message"), _cutErrorMessagesLineEditList}
			<< row{new QLabel("Copy error messages"), _copyErrorMessagesLineEditList}
			<< row{new QLabel("Paste error message"), _pasteErrorMessagesLineEditList}
			<< row{new QLabel("Paste text fraction"), _pasteTextFracionSpinBox};
}

void NotepadControl::setSaveData(QJsonObject& data)
{
	QJsonObject rootObject;
	rootObject[MODE] = _modeComboBox->currentIndex();
	rootObject[CUT_ERROR_MESSAGES] = QJsonArray::fromStringList(_cutErrorMessagesLineEditList->getTextInAllFields());
	rootObject[COPY_ERROR_MESSAGES] = QJsonArray::fromStringList(_copyErrorMessagesLineEditList->getTextInAllFields());
	rootObject[PASTE_ERROR_MESSAGES] = QJsonArray::fromStringList(_pasteErrorMessagesLineEditList->getTextInAllFields());

	QJsonObject pasteTextFractionSpinBoxObject;
	pasteTextFractionSpinBoxObject[MIN] = _pasteTextFracionSpinBox->getMin();
	pasteTextFractionSpinBoxObject[MAX] = _pasteTextFracionSpinBox->getMax();
	rootObject[PASTE_TEXT_FRACTION] = pasteTextFractionSpinBoxObject;

	data[ROOT_NAME] = rootObject;
}

void NotepadControl::load(QJsonObject& data)
{
	_cutErrorMessagesLineEditList->clear();
	_copyErrorMessagesLineEditList->clear();
	_pasteErrorMessagesLineEditList->clear();

	QJsonObject rootObject = data[ROOT_NAME].toObject();

	_modeComboBox->setCurrentIndex(rootObject[MODE].toInt());
	_cutErrorMessagesLineEditList->addFromStringList(jsonToStringList(rootObject[CUT_ERROR_MESSAGES]));
	_copyErrorMessagesLineEditList->addFromStringList(jsonToStringList(rootObject[COPY_ERROR_MESSAGES]));
	_pasteErrorMessagesLineEditList->addFromStringList(jsonToStringList(rootObject[PASTE_ERROR_MESSAGES]));

	QJsonObject pasteTextFractionSpinBoxObject = rootObject[PASTE_TEXT_FRACTION].toObject();
	_pasteTextFracionSpinBox->setMin(pasteTextFractionSpinBoxObject[MIN].toDouble());
	_pasteTextFracionSpinBox->setMax(pasteTextFractionSpinBoxObject[MAX].toDouble());
}

NotepadControl::mode NotepadControl::getMode()
{
	return static_cast<mode>(_modeComboBox->currentIndex());
}

LineEditList* NotepadControl::getCutErrorMessagesLineEditList()
{
	return _cutErrorMessagesLineEditList;
}

LineEditList* NotepadControl::getPasteErrorMessagesLineEditList()
{
	return _pasteErrorMessagesLineEditList;
}

RangedSpinBox* NotepadControl::getPasteTextFractionSpinBox()
{
	return _pasteTextFracionSpinBox;
}
