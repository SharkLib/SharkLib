#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vtkRenderer.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private:
	Ui::MainWindow *ui;

	vtkRenderer* render1;
	vtkRenderWindow *renWin1;
	int index;

	void cone1();
	void cone2();
	void cone3();
	void cone4();
	void cone5();
	void cone6();
	void cone7();
	void cone8();

	void cube();
	void cubesphere();
	void cubesphereAxis();
	void cubesphereAxisTranfor();
	void cubesphereAxisBoxTranfor();

	void cubebox();
	void cubecamera();
	void cubetext();
	void cylindertext();


	// QObject interface
protected:
	virtual void timerEvent(QTimerEvent *event);
private slots:
	void on_btnTimer_clicked();
};


#endif // MAINWINDOW_H
