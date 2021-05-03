#pragma once

#include <QObject>
#include <QWidget>
#include <QSpinBox>
#include <QtMath>
#include <QRandomGenerator>

class PercentageSpinBox : public QSpinBox
{
	Q_OBJECT
public:
	PercentageSpinBox(double defaultValue = 0.5);

	bool generateBool() const;

	double getPercentage() const;
	void setPercentage(const double& value);
};

