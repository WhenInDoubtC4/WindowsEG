#include "GlobalControl.h"

GlobalControl::GlobalControl()
{
	CONSTRUCT_ONCE
}

void GlobalControl::setSaveData(QJsonObject& data)
{
	QJsonObject rootObject;
	rootObject[TEXT_AA] = _textAACheckBox->isChecked();

	data[ROOT_NAME] = rootObject;
}

void GlobalControl::load(QJsonObject& data)
{
	QJsonObject rootObject = data[ROOT_NAME].toObject();

	_textAACheckBox->setChecked(rootObject[TEXT_AA].toBool());
}

void GlobalControl::resetToDefault()
{
	_textAACheckBox->setChecked(false);
}
