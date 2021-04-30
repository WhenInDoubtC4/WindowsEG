#pragma once

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QRandomGenerator>

class RangedSpinBox : public QWidget
{
	Q_OBJECT
public:
	explicit RangedSpinBox(QWidget* parent = nullptr);
	~RangedSpinBox();

	double generateValue() const;
	double getMin() const;
	double getMax() const;
	void setMin(double value);
	void setMax(double value);

private:
	QHBoxLayout* _layout = nullptr;
	QDoubleSpinBox* _minSpinBox = nullptr;
	QDoubleSpinBox* _maxSpinBox = nullptr;

private slots:
	void validateValue();
};

