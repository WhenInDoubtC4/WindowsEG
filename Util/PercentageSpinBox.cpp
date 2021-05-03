#include "PercentageSpinBox.h"

#include <QDebug>

PercentageSpinBox::PercentageSpinBox(double defaultValue)
{
	setSuffix("%");
	setMinimum(0);
	setMaximum(100);
	setPercentage(defaultValue);
}

bool PercentageSpinBox::generateBool() const
{
	int random = QRandomGenerator::global()->bounded(0, 100);
	return random <= value();
}

double PercentageSpinBox::getPercentage() const
{
	return value() / 100.;
}

void PercentageSpinBox::setPercentage(const double& value)
{
	setValue(qRound(value * 100.));
}
