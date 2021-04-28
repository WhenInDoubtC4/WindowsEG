#include "NotepadControl.h"

#include <QDebug>

NotepadControl::NotepadControl() : AppControl()
  , _modeComboBox(new QComboBox)
{
	CONSTRUCT_ONCE

	_modeComboBox->addItem("Broken text");
	_modeComboBox->addItem("Error messages");

	_cutErrorMessagesLineEditList = new LineEditList(_defaultCutErrorMessages);
	_copyErrorMessagesLineEditList = new LineEditList(_defaultCopyErrorMessages);

	getControlItemsList()
			<< row{new QLabel("Mode"), _modeComboBox}
			<< row{new QLabel("Cut error message"), _cutErrorMessagesLineEditList}
			<< row{new QLabel("Copy error messages"), _copyErrorMessagesLineEditList};
}

void NotepadControl::setSaveData(QJsonObject& data)
{
	QJsonObject rootObject;
	rootObject[CUT_ERROR_MESSAGES] = QJsonArray::fromStringList(_cutErrorMessagesLineEditList->getTextInAllFields());
	rootObject[COPY_ERROR_MESSAGES] = QJsonArray::fromStringList(_copyErrorMessagesLineEditList->getTextInAllFields());

	data[ROOT_NAME] = rootObject;
}

void NotepadControl::load(QJsonObject& data)
{
	_cutErrorMessagesLineEditList->clear();
	_copyErrorMessagesLineEditList->clear();

	QJsonObject rootObject = data[ROOT_NAME].toObject();

	_cutErrorMessagesLineEditList->addFromStringList(toStringList(rootObject[CUT_ERROR_MESSAGES]));
	_copyErrorMessagesLineEditList->addFromStringList(toStringList(rootObject[COPY_ERROR_MESSAGES]));
}
