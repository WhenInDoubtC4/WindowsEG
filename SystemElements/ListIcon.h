#pragma once

#include <QObject>
#include <QWidget>
#include <QFocusEvent>

namespace Ui
{
	class ListIcon;
}

class ListIcon : public QWidget
{
	Q_OBJECT
public:
	explicit ListIcon(const QPixmap& icon, const QString& title, QWidget* parent = nullptr);
	~ListIcon();

	void setCorrespondingPath(const QString& path){ _correspondingPath = path; };
	QString getCorrespondingPath() const{ return _correspondingPath; };

	void setSelected(bool selected);

protected:
	virtual void mouseDoubleClickEvent(QMouseEvent* event) override;
	virtual void focusOutEvent(QFocusEvent* event) override;
	virtual void focusInEvent(QFocusEvent* event) override;
	virtual void showEvent(QShowEvent* event) override;

private:
	Ui::ListIcon* _ui = nullptr;

	bool _ignoreFocusOnce = false;
	QString _correspondingPath;

signals:
	void opened();
};

