#pragma once

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QRandomGenerator>
#include <QJsonObject>

class RangedSpinBox : public QWidget
{
	Q_OBJECT
public:
	explicit RangedSpinBox(double min = 0., double max = 1., double defaultMin = 0., double defaultMax = 1., double step = 0.1, QWidget* parent = nullptr);
	~RangedSpinBox();

	double generateValue() const;

	double getMin() const;
	double getMax() const;
	void setMin(double value);
	void setMax(double value);

	void setPrecision(int decimals);

	QJsonObject getJsonObject() const;
	void loadFromJson(const QJsonValueRef& jsonObject);

private:
	QHBoxLayout* _layout = nullptr;
	QDoubleSpinBox* _minSpinBox = nullptr;
	QDoubleSpinBox* _maxSpinBox = nullptr;

private slots:
	void validateValue();
};

