#include "RangedSpinBox.h"

RangedSpinBox::RangedSpinBox(QWidget* parent) : QWidget(parent)
  , _layout(new QHBoxLayout(this))
  , _minSpinBox(new QDoubleSpinBox())
  , _maxSpinBox(new QDoubleSpinBox())
{
	_layout->addWidget(_minSpinBox);
	_layout->addWidget(_maxSpinBox);

	_minSpinBox->setMinimum(0.f);
	_minSpinBox->setMaximum(1.f);
	_minSpinBox->setSingleStep(0.1f);
	_minSpinBox->setPrefix("Min: ");
	_maxSpinBox->setMinimum(0.f);
	_maxSpinBox->setMaximum(1.f);
	_maxSpinBox->setSingleStep(0.1f);
	_maxSpinBox->setValue(1.f);
	_maxSpinBox->setPrefix("Max: ");

	QObject::connect(_minSpinBox, &QDoubleSpinBox::editingFinished, this, &RangedSpinBox::validateValue);
	QObject::connect(_maxSpinBox, &QDoubleSpinBox::editingFinished, this, &RangedSpinBox::validateValue);
}

RangedSpinBox::~RangedSpinBox()
{
	delete _minSpinBox;
	delete _maxSpinBox;
	delete _layout;
}

void RangedSpinBox::validateValue()
{
	if (_minSpinBox->value() > _maxSpinBox->value())
	{
		_minSpinBox->setValue(_maxSpinBox->value());
	}
}

double RangedSpinBox::generateValue() const
{
	double min = _minSpinBox->value();
	double max = _maxSpinBox->value();
	return QRandomGenerator::global()->bounded(max - min) + min;
}

double RangedSpinBox::getMin() const
{
	return _minSpinBox->value();
}

double RangedSpinBox::getMax() const
{
	return _maxSpinBox->value();
}

void RangedSpinBox::setMin(double value)
{
	_minSpinBox->setValue(value);
}

void RangedSpinBox::setMax(double value)
{
	_maxSpinBox->setValue(value);
}
