#include "RangedSpinBox.h"

RangedSpinBox::RangedSpinBox(double min, double max, double defaultMin, double defaultMax, double step, QWidget* parent) : QWidget(parent)
  , _layout(new QHBoxLayout(this))
  , _minSpinBox(new QDoubleSpinBox())
  , _maxSpinBox(new QDoubleSpinBox())
{
	_layout->setMargin(2);
	_layout->addWidget(_minSpinBox);
	_layout->addWidget(_maxSpinBox);

	_minSpinBox->setMinimum(min);
	_minSpinBox->setMaximum(max);
	_minSpinBox->setSingleStep(step);
	_minSpinBox->setValue(defaultMin);
	_minSpinBox->setPrefix("Min: ");
	_maxSpinBox->setMinimum(min);
	_maxSpinBox->setMaximum(max);
	_maxSpinBox->setSingleStep(step);
	_maxSpinBox->setValue(defaultMax);
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

void RangedSpinBox::setPrecision(int decimals)
{
	_minSpinBox->setDecimals(decimals);
	_maxSpinBox->setDecimals(decimals);
}

QJsonObject RangedSpinBox::getJsonObject() const
{
	QJsonObject object;
	object["min"] = getMin();
	object["max"] = getMax();

	return object;
}

void RangedSpinBox::loadFromJson(const QJsonValueRef& jsonObject)
{
	setMin(jsonObject.toObject()["min"].toDouble());
	setMax(jsonObject.toObject()["max"].toDouble());
}
