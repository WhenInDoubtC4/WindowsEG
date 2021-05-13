#pragma once

#include <QObject>
#include <QTreeWidgetItem>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

//Pretty sure there's a better way to do this but I can't bother
#define APP_CONTROL friend class AppControl;

#define CONSTRUCT_ONCE \
	static bool alreadyConstructed = false; \
	if (alreadyConstructed) throw std::logic_error("Instance " __FILE__ " already constructed"); \
	alreadyConstructed = true;

class AppControl : public QObject
{
	Q_OBJECT
public:	
	template<typename T, typename = std::enable_if_t<std::is_base_of_v<AppControl, T>>>
	static T* registerControlClass()
	{
		T* instance = new T;
		_instances << instance;
		return instance;
	}

	template<typename T, typename = std::enable_if_t<std::is_base_of_v<AppControl, T>>>
	static T* getInstance()
	{
		for (auto instance : qAsConst(_instances)) if (typeid (*instance) == typeid (T)) return dynamic_cast<T*>(instance);
		return nullptr;
	}

	void setupControlWidgets(QTreeWidget* treeWidget, const QString& title);

	static QJsonDocument saveAll();
	static void loadAll(QJsonDocument& jsonDocument);

	bool isConfigActive();

protected:
	AppControl();

	typedef QList<QWidget*> row;
	QList<row>& getControlItemsList();

	virtual void setSaveData([[maybe_unused]] QJsonObject& data){};
	virtual void load([[maybe_unused]] QJsonObject& data){};
	virtual void resetToDefault(){};

	QList<QString> jsonToStringList(const QJsonValueRef& jsonValue);

private:
	inline static QList<AppControl*> _instances;
	inline static QMap<AppControl*, QList<row>> _controlItems;

	bool _isConfigActive = false;
};
