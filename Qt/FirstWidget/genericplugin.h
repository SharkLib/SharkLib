#ifndef GENERICPLUGIN_H
#define GENERICPLUGIN_H

#include <QGenericPlugin>
#include "../MyApplication/myplugininterface.h"


class VTKPlugin :  public QGenericPlugin,  public MyPluginInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QGenericPluginFactoryInterface" FILE "FisrtWidnow.json")
	Q_INTERFACES(MyPluginInterface)
public:
	explicit VTKPlugin(QObject *parent = nullptr);
protected slots:
	void slot_add();
private:
	QObject *create(const QString &name, const QString &spec) override;

	// MyPluginInterface interface
public:
	virtual QWidget *createWidget(QWidget* parent= nullptr) override;
	virtual QMenu *createMenu(QWidget* parent= nullptr) override;

	// MyPluginInterface interface
public:
	virtual QString name();
};

#endif // GENERICPLUGIN_H
