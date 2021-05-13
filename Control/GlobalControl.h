#pragma once

#include <QObject>
#include <QCheckBox>

#include "AppControl.h"

#define ROOT_NAME "Global"
#define TEXT_AA "textAntiAliasing"

class GlobalControl : public AppControl
{
	Q_OBJECT

public:
	void setTextAACheckBox(QCheckBox* textAACheckBox){ _textAACheckBox = textAACheckBox; };
	QCheckBox* getTextAACheckBox(){	return _textAACheckBox; };

protected:
	virtual void setSaveData(QJsonObject& data) override;
	virtual void load(QJsonObject& data) override;
	virtual void resetToDefault() override;

private:
	APP_CONTROL
	GlobalControl();

	QCheckBox* _textAACheckBox = nullptr;
};

