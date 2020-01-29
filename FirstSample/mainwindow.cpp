#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDir>
#include <QDebug>


#include <vtkAnimationCue.h>
#include <vtkAnimationScene.h>
#include <vtkCamera.h>
#include <vtkColor.h>
#include <vtkCommand.h>
#include <vtkConeSource.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkTDxInteractorStyle.h>
#include <vtkTDxInteractorStyleSettings.h>

#include <vtkEventQtSlotConnect.h>
#include "vtkGenericOpenGLRenderWindow.h"
#include <vtkDataObjectToTable.h>
#include <vtkElevationFilter.h>
#include "vtkGenericOpenGLRenderWindow.h"
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkQtTableView.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include "vtkSmartPointer.h"
#include <vtkVectorText.h>

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkVersion.h>
#include "vtkAutoInit.h"
#include <vtkTexture.h>
#include <vtkBMPReader.h>
#include <vtkAssembly.h>
#include <vtkCylinderSource.h>
#include <vtkTextSource.h>
#include <vtkBoxWidget.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkTransform.h>
#include <vtkCubeSource.h>
#include <vtkAxesActor.h>
#include <vtkCubeAxesActor.h>
#include <vtkTextProperty.h>
#include <vtkActorCollection.h>
#include <vtkCamera.h>
#include <QVTKOpenGLWidget.h>
#include <vtkTextActor.h>
#include <vtkPlaneSource.h>
#include <vtkTextureMapToCylinder.h>

VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType );
VTK_MODULE_INIT(vtkRenderingContextOpenGL2);
VTK_MODULE_INIT(vtkRenderingGL2PSOpenGL2);

//
// Similar to Cone2.cxx, we define a callback for interaction.
//
class vtkMyCallback : public vtkCommand
{
public:
  static vtkMyCallback *New()
	{ return new vtkMyCallback; }
  void Execute(vtkObject *caller, unsigned long, void*) override
  {
	  vtkTransform *t = vtkTransform::New();
	  vtkBoxWidget *widget = reinterpret_cast<vtkBoxWidget*>(caller);
	  widget->GetTransform(t);
	  widget->GetProp3D()->SetUserTransform(t);
	  t->Delete();
  }
};



MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	index = 0;
	//cone5();
	//cone1();
	//cone6();
	//cone2();
	//cone3();
	cube();
	cubebox();
	cubesphere();
	cubesphereAxis();
	cubesphereAxisTranfor();
	cubesphereAxisBoxTranfor();
	cubecamera();
	cubetext();
	cylindertext();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::cone1()
{
	//
	  // Next we create an instance of vtkConeSource and set some of its
	  // properties. The instance of vtkConeSource "cone" is part of a
	  // visualization pipeline (it is a source process object); it produces data
	  // (output type is vtkPolyData) which other filters may process.
	  //
	  vtkConeSource *cone = vtkConeSource::New();
	  cone->SetHeight( 3.0 );
	  cone->SetRadius( 1.0 );
	  cone->SetResolution( 10 );

	  //
	  // In this example we terminate the pipeline with a mapper process object.
	  // (Intermediate filters such as vtkShrinkPolyData could be inserted in
	  // between the source and the mapper.)  We create an instance of
	  // vtkPolyDataMapper to map the polygonal data into graphics primitives. We
	  // connect the output of the cone source to the input of this mapper.
	  //
	  vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
	  coneMapper->SetInputConnection( cone->GetOutputPort() );

	  //
	  // Create an actor to represent the cone. The actor orchestrates rendering
	  // of the mapper's graphics primitives. An actor also refers to properties
	  // via a vtkProperty instance, and includes an internal transformation
	  // matrix. We set this actor's mapper to be coneMapper which we created
	  // above.
	  //
	  vtkActor *coneActor = vtkActor::New();
	  coneActor->SetMapper( coneMapper );

	  //
	  // Create the Renderer and assign actors to it. A renderer is like a
	  // viewport. It is part or all of a window on the screen and it is
	  // responsible for drawing the actors it has.  We also set the background
	  // color here.
	  //
	  vtkRenderer *ren1= vtkRenderer::New();
	  ren1->AddActor( coneActor );
	  ren1->SetBackground( 0.1, 0.2, 0.4 );

	  render1 = ren1;

	  //
	  // Finally we create the render window which will show up on the screen.
	  // We put our renderer into the render window using AddRenderer. We also
	  // set the size to be 300 pixels by 300.
	  //
	  //---------
	  auto vw = new  QVTKOpenGLWidget(this) ;
	  vtkRenderWindow *renWin = vw->GetRenderWindow();
	  ui->tabWidget->addTab( vw, "cone1");
	  renWin1 = renWin;

	  //vtkRenderWindow *renWin = vtkRenderWindow::New();
	  //---------

	  renWin->AddRenderer( ren1 );
	  renWin->SetSize( 300, 300 );


	  //step 5
	  vtkSmartPointer<vtkTransform> transform =
		  vtkSmartPointer<vtkTransform>::New();
		transform->Translate(1, 0.0, 0.0);

		vtkSmartPointer<vtkAxesActor> axes =
		  vtkSmartPointer<vtkAxesActor>::New();

		// The axes are positioned with a user transform
		axes->SetUserTransform(transform);


	  //绕Z轴旋转45^{\circ}
	  vtkSmartPointer<vtkTransform> trans =
		  vtkSmartPointer<vtkTransform>::New();
	  trans->PostMultiply();
	  trans->Translate(1, 0, 0);
	  trans->RotateZ(45);
	  coneActor->SetUserTransform(trans);

	  renWin->Render();
}

void MainWindow::cone2()
{
	// Next we create an instance of vtkConeSource and set some of its
	// properties. The instance of vtkConeSource "cone" is part of a
	// visualization pipeline (it is a source process object); it produces data
	// (output type is vtkPolyData) which other filters may process.
	//
	vtkCubeSource *cone = vtkCubeSource::New();

	//
	// In this example we terminate the pipeline with a mapper process object.
	// (Intermediate filters such as vtkShrinkPolyData could be inserted in
	// between the source and the mapper.)  We create an instance of
	// vtkPolyDataMapper to map the polygonal data into graphics primitives. We
	// connect the output of the cone source to the input of this mapper.
	//
	vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
	coneMapper->SetInputConnection( cone->GetOutputPort() );

	//
	// Create an actor to represent the cone. The actor orchestrates rendering
	// of the mapper's graphics primitives. An actor also refers to properties
	// via a vtkProperty instance, and includes an internal transformation
	// matrix. We set this actor's mapper to be coneMapper which we created
	// above.
	//
	vtkActor *coneActor = vtkActor::New();
	coneActor->SetMapper( coneMapper );

	//
	// Create the Renderer and assign actors to it. A renderer is like a
	// viewport. It is part or all of a window on the screen and it is
	// responsible for drawing the actors it has.  We also set the background
	// color here.
	//
	vtkRenderer *ren1= vtkRenderer::New();
	ren1->AddActor( coneActor );
	ren1->SetBackground( 0.1, 0.2, 0.4 );

	//
	// Finally we create the render window which will show up on the screen.
	// We put our renderer into the render window using AddRenderer. We also
	// set the size to be 300 pixels by 300.
	//


	auto vw = new  QVTKOpenGLWidget(this) ;
	vtkRenderWindow *renWin = vw->GetRenderWindow();
	ui->tabWidget->addTab( vw, "cone2");
	renWin->AddRenderer( ren1 );
	renWin->SetSize( 300, 300 );

	//
	// The vtkRenderWindowInteractor class watches for events (e.g., keypress,
	// mouse) in the vtkRenderWindow. These events are translated into
	// event invocations that VTK understands (see VTK/Common/vtkCommand.h
	// for all events that VTK processes). Then observers of these VTK
	// events can process them as appropriate.
	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
	iren->SetRenderWindow(renWin);

	//
	// By default the vtkRenderWindowInteractor instantiates an instance
	// of vtkInteractorStyle. vtkInteractorStyle translates a set of events
	// it observes into operations on the camera, actors, and/or properties
	// in the vtkRenderWindow associated with the vtkRenderWinodwInteractor.
	// Here we specify a particular interactor style.
	vtkInteractorStyleTrackballCamera *style =
	  vtkInteractorStyleTrackballCamera::New();
	iren->SetInteractorStyle(style);

	//
	// Here we use a vtkBoxWidget to transform the underlying coneActor (by
	// manipulating its transformation matrix). Many other types of widgets
	// are available for use, see the documentation for more details.
	//
	// The SetInteractor method is how 3D widgets are associated with the render
	// window interactor. Internally, SetInteractor sets up a bunch of callbacks
	// using the Command/Observer mechanism (AddObserver()). The place factor
	// controls the initial size of the widget with respect to the bounding box
	// of the input to the widget.
	vtkBoxWidget *boxWidget = vtkBoxWidget::New();
	boxWidget->SetInteractor(iren);
	boxWidget->SetPlaceFactor(1.25);

	//
	// Place the interactor initially. The input to a 3D widget is used to
	// initially position and scale the widget. The EndInteractionEvent is
	// observed which invokes the SelectPolygons callback.
	//
	boxWidget->SetProp3D(coneActor);
	boxWidget->PlaceWidget();
	vtkMyCallback *callback = vtkMyCallback::New();
	boxWidget->AddObserver(vtkCommand::InteractionEvent, callback);

	//
	// Normally the user presses the "i" key to bring a 3D widget to life. Here
	// we will manually enable it so it appears with the cone.
	//
	boxWidget->On();

	//
	// Start the event loop.
	//
	iren->Initialize();
}

void MainWindow::cone3()
{
	//step 0: set it to a window:
	auto vw = new  QVTKOpenGLWidget(this) ;
	vtkRenderWindow *renWin = vw->GetRenderWindow();
	ui->tabWidget->addTab( vw, "My Cylinder");

	vtkRenderer *render= vtkRenderer::New();

	render->SetBackground( 0.1, 0.2, 0.4 );

	if(1)
	{
		//step 1, create a data source;
		vtkCylinderSource *cylinder = vtkCylinderSource::New();
		cylinder->SetHeight( 2.0 );
		cylinder->SetRadius( 2.0 );
		cylinder->SetResolution( 16 );

		//step 2: map data to a pipeline
		vtkPolyDataMapper *cylinderMapper = vtkPolyDataMapper::New();
		cylinderMapper->SetInputConnection( cylinder->GetOutputPort() );

		//step 3: create a actor and represente the pipeline
		vtkActor *actor = vtkActor::New();
		actor->SetMapper( cylinderMapper );

		//step4 :create a render and set the actor to it

		render->AddActor( actor );
		renWin->AddRenderer( render );
	}


	{
		//step 1, create a data source;
		vtkConeSource *cylinder = vtkConeSource::New();
		cylinder->SetHeight( 8.0 );
		cylinder->SetRadius( 1.0 );
		cylinder->SetResolution( 16 );

		//step 2: map data to a pipeline
		vtkPolyDataMapper *cylinderMapper = vtkPolyDataMapper::New();
		cylinderMapper->SetInputConnection( cylinder->GetOutputPort() );

		//step 3: create a actor and represente the pipeline
		vtkActor *actor = vtkActor::New();
		actor->SetMapper( cylinderMapper );

		//step4 :create a render and set the actor to it
		render->AddActor( actor );


		//step 5
		vtkSmartPointer<vtkTransform> transform =
			vtkSmartPointer<vtkTransform>::New();
		  transform->Translate(3, 3.0, 3.0);

		  vtkSmartPointer<vtkAxesActor> axes =
			vtkSmartPointer<vtkAxesActor>::New();

		  // The axes are positioned with a user transform
		 // axes->SetUserTransform(transform);

		  // properties of the axes labels can be set as follows
		  // this sets the x axis label to red
		  // axes->GetXAxisCaptionActor2D()->GetCaptionTextProperty()->SetColor(1,0,0);

		  // the actual text of the axis label can be changed:
		  // axes->SetXAxisLabelText("test");

		  render->AddActor(axes);
		  //step 6
		  vtkSmartPointer<vtkCubeAxesActor> cubeAxesActor =
			  vtkSmartPointer<vtkCubeAxesActor>::New();
			cubeAxesActor->SetBounds(cylinder->GetOutput()->GetBounds());
			cubeAxesActor->SetCamera(render->GetActiveCamera());
			cubeAxesActor->GetTitleTextProperty(0)->SetColor(1.0, 0.0, 0.0);
			cubeAxesActor->GetLabelTextProperty(0)->SetColor(1.0, 0.0, 0.0);

			cubeAxesActor->GetTitleTextProperty(1)->SetColor(0.0, 1.0, 0.0);
			cubeAxesActor->GetLabelTextProperty(1)->SetColor(0.0, 1.0, 0.0);

			cubeAxesActor->GetTitleTextProperty(2)->SetColor(0.0, 0.0, 1.0);
			cubeAxesActor->GetLabelTextProperty(2)->SetColor(0.0, 0.0, 1.0);

			cubeAxesActor->DrawXGridlinesOn();
			cubeAxesActor->DrawYGridlinesOn();
			cubeAxesActor->DrawZGridlinesOn();
		  #if VTK_MAJOR_VERSION == 6
			cubeAxesActor->SetGridLineLocation(VTK_GRID_LINES_FURTHEST);
		  #endif
		  #if VTK_MAJOR_VERSION > 6
			cubeAxesActor->SetGridLineLocation(
			  cubeAxesActor->VTK_GRID_LINES_FURTHEST);
		  #endif

			cubeAxesActor->XAxisMinorTickVisibilityOff();
			cubeAxesActor->YAxisMinorTickVisibilityOff();
			cubeAxesActor->ZAxisMinorTickVisibilityOff();

			render->AddActor(cubeAxesActor);
			//render->ResetCamera();


return;
		//step 5: camera
		vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
		iren->SetRenderWindow(renWin);

		vtkInteractorStyleTrackballCamera *style =	  vtkInteractorStyleTrackballCamera::New();
		iren->SetInteractorStyle(style);

		//step 6
		vtkBoxWidget *boxWidget = vtkBoxWidget::New();
		boxWidget->SetInteractor(iren);
		boxWidget->SetPlaceFactor(1.25);
		boxWidget->SetProp3D(actor);
		boxWidget->PlaceWidget();
		vtkMyCallback *callback = vtkMyCallback::New();
		boxWidget->AddObserver(vtkCommand::InteractionEvent, callback);

		//
		// Normally the user presses the "i" key to bring a 3D widget to life. Here
		// we will manually enable it so it appears with the cone.
		//
		boxWidget->On();


	}



}

void MainWindow::cone4(){}

void MainWindow::cone5()
{

}

void MainWindow::cone6()
{
	//
	  // Next we create an instance of vtkConeSource and set some of its
	  // properties. The instance of vtkConeSource "cone" is part of a
	  // visualization pipeline (it is a source process object); it produces data
	  // (output type is vtkPolyData) which other filters may process.
	  //
	  vtkConeSource *cone = vtkConeSource::New();
	  cone->SetHeight( 3.0 );
	  cone->SetRadius( 1.0 );
	  cone->SetResolution( 10 );

	  //
	  // In this example we terminate the pipeline with a mapper process object.
	  // (Intermediate filters such as vtkShrinkPolyData could be inserted in
	  // between the source and the mapper.)  We create an instance of
	  // vtkPolyDataMapper to map the polygonal data into graphics primitives. We
	  // connect the output of the cone source to the input of this mapper.
	  //
	  vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
	  coneMapper->SetInputConnection( cone->GetOutputPort() );

	  //
	  // Create an actor to represent the cone. The actor orchestrates rendering
	  // of the mapper's graphics primitives. An actor also refers to properties
	  // via a vtkProperty instance, and includes an internal transformation
	  // matrix. We set this actor's mapper to be coneMapper which we created
	  // above.
	  //
	  vtkActor *coneActor = vtkActor::New();
	  coneActor->SetMapper( coneMapper );

	  //
	  // Create the Renderer and assign actors to it. A renderer is like a
	  // viewport. It is part or all of a window on the screen and it is
	  // responsible for drawing the actors it has.  We also set the background
	  // color here.
	  //
	  vtkRenderer *ren1= vtkRenderer::New();
	  ren1->AddActor( coneActor );
	  ren1->SetBackground( 0.1, 0.2, 0.4 );

	  //
	  // Finally we create the render window which will show up on the screen.
	  // We put our renderer into the render window using AddRenderer. We also
	  // set the size to be 300 pixels by 300.
	  //


	  auto vw = new  QVTKOpenGLWidget(this) ;
	  vtkRenderWindow *renWin = vw->GetRenderWindow();
	  ui->tabWidget->addTab( vw, "cone6");
	  renWin->AddRenderer( ren1 );
	  renWin->SetSize( 300, 300 );

	  //
	  // The vtkRenderWindowInteractor class watches for events (e.g., keypress,
	  // mouse) in the vtkRenderWindow. These events are translated into
	  // event invocations that VTK understands (see VTK/Common/vtkCommand.h
	  // for all events that VTK processes). Then observers of these VTK
	  // events can process them as appropriate.
	  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
	  iren->SetRenderWindow(renWin);

	  //
	  // By default the vtkRenderWindowInteractor instantiates an instance
	  // of vtkInteractorStyle. vtkInteractorStyle translates a set of events
	  // it observes into operations on the camera, actors, and/or properties
	  // in the vtkRenderWindow associated with the vtkRenderWinodwInteractor.
	  // Here we specify a particular interactor style.
	  vtkInteractorStyleTrackballCamera *style =
		vtkInteractorStyleTrackballCamera::New();
	  iren->SetInteractorStyle(style);

	  //
	  // Here we use a vtkBoxWidget to transform the underlying coneActor (by
	  // manipulating its transformation matrix). Many other types of widgets
	  // are available for use, see the documentation for more details.
	  //
	  // The SetInteractor method is how 3D widgets are associated with the render
	  // window interactor. Internally, SetInteractor sets up a bunch of callbacks
	  // using the Command/Observer mechanism (AddObserver()). The place factor
	  // controls the initial size of the widget with respect to the bounding box
	  // of the input to the widget.
	  vtkBoxWidget *boxWidget = vtkBoxWidget::New();
	  boxWidget->SetInteractor(iren);
	  boxWidget->SetPlaceFactor(1.25);

	  //
	  // Place the interactor initially. The input to a 3D widget is used to
	  // initially position and scale the widget. The EndInteractionEvent is
	  // observed which invokes the SelectPolygons callback.
	  //
	  boxWidget->SetProp3D(coneActor);
	  boxWidget->PlaceWidget();
	  vtkMyCallback *callback = vtkMyCallback::New();
	  boxWidget->AddObserver(vtkCommand::InteractionEvent, callback);

	  //
	  // Normally the user presses the "i" key to bring a 3D widget to life. Here
	  // we will manually enable it so it appears with the cone.
	  //
	  boxWidget->On();

	  //
	  // Start the event loop.
	  //
	  iren->Initialize();

}

void MainWindow::cone7(){}

void MainWindow::cone8(){}

void MainWindow::cube()
{
	//step 0: set it to a window:
	auto vw = new  QVTKOpenGLWidget(this) ;
	vtkRenderWindow *renWin = vw->GetRenderWindow();
	ui->tabWidget->addTab( vw, __FUNCTION__);

	vtkRenderer *render= vtkRenderer::New();

	render->SetBackground( 0.1, 0.2, 0.4 );

	vtkSmartPointer<vtkConeSource> coneSource =
			vtkSmartPointer<vtkConeSource>::New();
		coneSource->SetRadius(.2);
		coneSource->SetHeight(.5);
		coneSource->SetCenter(0, 0, 0);
		vtkSmartPointer<vtkPolyDataMapper> coneMapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		coneMapper->SetInputConnection(coneSource->GetOutputPort());
		vtkSmartPointer<vtkActor> coneActor =
			vtkSmartPointer<vtkActor>::New();
		coneActor->SetMapper(coneMapper);

		vtkSmartPointer<vtkActor> oriConeActor =
			vtkSmartPointer<vtkActor>::New();
		oriConeActor->SetMapper(coneMapper);

	render->AddActor(oriConeActor);
	renWin->AddRenderer( render );
}

void MainWindow::cubesphere()
{

	//step 0: set it to a window:
	auto vw = new  QVTKOpenGLWidget(this) ;
	vtkRenderWindow *renWin = vw->GetRenderWindow();
	ui->tabWidget->addTab( vw, __FUNCTION__);

	vtkRenderer *render= vtkRenderer::New();

	render->SetBackground( 0.1, 0.2, 0.4 );


	vtkSmartPointer<vtkSphereSource> sphereSource =
			vtkSmartPointer<vtkSphereSource>::New();
	sphereSource->SetRadius(0.1);
	sphereSource->Update();
	vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
	sphereMapper->SetInputConnection(sphereSource->GetOutputPort());

	vtkSmartPointer<vtkActor> sphereActor =
			vtkSmartPointer<vtkActor>::New();
	sphereActor->SetPosition(0, 0, 0);
	sphereActor->SetMapper(sphereMapper);
	sphereActor->GetProperty()->SetColor(1, 0, 0);

	render->AddActor(sphereActor);


	vtkSmartPointer<vtkConeSource> coneSource =
			vtkSmartPointer<vtkConeSource>::New();
		coneSource->SetRadius(.2);
		coneSource->SetHeight(.5);
		coneSource->SetCenter(0, 0, 0);
		vtkSmartPointer<vtkPolyDataMapper> coneMapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		coneMapper->SetInputConnection(coneSource->GetOutputPort());
		vtkSmartPointer<vtkActor> coneActor =
			vtkSmartPointer<vtkActor>::New();
		coneActor->SetMapper(coneMapper);

		vtkSmartPointer<vtkActor> oriConeActor =
			vtkSmartPointer<vtkActor>::New();
		oriConeActor->SetMapper(coneMapper);

	render->AddActor(oriConeActor);
	renWin->AddRenderer( render );

}

void MainWindow::cubesphereAxis()
{
	//step 0: set it to a window:
	auto vw = new  QVTKOpenGLWidget(this) ;
	vtkRenderWindow *renWin = vw->GetRenderWindow();
	ui->tabWidget->addTab( vw, __FUNCTION__);

	vtkRenderer *render= vtkRenderer::New();

	render->SetBackground( 0.1, 0.2, 0.4 );


	vtkSmartPointer<vtkSphereSource> sphereSource =
			vtkSmartPointer<vtkSphereSource>::New();
	sphereSource->SetRadius(0.1);
	sphereSource->Update();
	vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
	sphereMapper->SetInputConnection(sphereSource->GetOutputPort());

	vtkSmartPointer<vtkActor> sphereActor =
			vtkSmartPointer<vtkActor>::New();
	sphereActor->SetPosition(0, 0, 0);
	sphereActor->SetMapper(sphereMapper);
	sphereActor->GetProperty()->SetColor(1, 0, 0);

	render->AddActor(sphereActor);




	vtkSmartPointer<vtkConeSource> coneSource =
			vtkSmartPointer<vtkConeSource>::New();
		coneSource->SetRadius(1);
		coneSource->SetHeight(5.5);
		coneSource->SetCenter(0, 0, 0);
		vtkSmartPointer<vtkPolyDataMapper> coneMapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		coneMapper->SetInputConnection(coneSource->GetOutputPort());
		vtkSmartPointer<vtkActor> coneActor =
			vtkSmartPointer<vtkActor>::New();
		coneActor->SetMapper(coneMapper);

		vtkSmartPointer<vtkActor> oriConeActor =
			vtkSmartPointer<vtkActor>::New();
		oriConeActor->SetMapper(coneMapper);

	render->AddActor(oriConeActor);


	double AXIS_LEN = 1.0;
	vtkSmartPointer<vtkAxesActor> oriAxesActor =
			vtkSmartPointer<vtkAxesActor>::New();
	oriAxesActor->SetPosition(0, 0, 0);
	oriAxesActor->SetTotalLength(AXIS_LEN, 2*AXIS_LEN, AXIS_LEN);
	oriAxesActor->SetShaftType(0);
	oriAxesActor->SetAxisLabels(0);
	oriAxesActor->SetCylinderRadius(0.02);

//	vtkSmartPointer<vtkAxesActor> axesActor =
//			vtkSmartPointer<vtkAxesActor>::New();
//	axesActor->SetPosition(0, 0, 0);

//	axesActor->SetTotalLength(AXIS_LEN, AXIS_LEN, AXIS_LEN*2);
//	axesActor->SetShaftType(0);
//	axesActor->SetAxisLabels(0);
//	axesActor->SetCylinderRadius(0.02);

	vtkSmartPointer<vtkTextActor> textActor =
			vtkSmartPointer<vtkTextActor>::New();
	textActor->SetPosition2(100, 40);
	textActor->GetTextProperty()->SetFontSize(24);
	textActor->GetTextProperty()->SetColor(1, 0, 0);


	vtkSmartPointer<vtkTransform> trans =
			vtkSmartPointer<vtkTransform>::New();

	trans->RotateZ(45);
	trans->Translate(2, 0, 0);
	coneActor->SetUserTransform(trans);
	textActor->SetInput("trans->RotateZ(45)\ntrans->Translate(1, 0, 0)\nconeActor->SetUserTransform(trans)");

	cout << "GetMatrix:" << endl;
	if (coneActor->GetMatrix()!=NULL)
	{
		coneActor->GetMatrix()->Print(cout);
	}
	else
	{
		cout << "NULL" << endl;
	}
	cout << "GetUserMatrix:" << endl;
	if (coneActor->GetUserMatrix() !=NULL)
	{
		coneActor->GetUserMatrix()->Print(cout);
	}
	else
	{
		cout << "NULL" << endl;
	}

	render->AddActor(oriAxesActor);
	//render->AddActor(axesActor);
	render->AddActor(textActor);

	renWin->AddRenderer( render );
}

void MainWindow::cubesphereAxisTranfor()
{
	//step 0: set it to a window:
	auto vw = new  QVTKOpenGLWidget(this) ;
	vtkRenderWindow *renWin = vw->GetRenderWindow();
	ui->tabWidget->addTab( vw, __FUNCTION__);

	vtkRenderer *render= vtkRenderer::New();

	render->SetBackground( 0.1, 0.2, 0.4 );


	vtkSmartPointer<vtkSphereSource> sphereSource =
			vtkSmartPointer<vtkSphereSource>::New();
	sphereSource->SetRadius(0.1);
	sphereSource->Update();
	vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
	sphereMapper->SetInputConnection(sphereSource->GetOutputPort());

	vtkSmartPointer<vtkActor> sphereActor =
			vtkSmartPointer<vtkActor>::New();
	sphereActor->SetPosition(0, 0, 0);
	sphereActor->SetMapper(sphereMapper);
	sphereActor->GetProperty()->SetColor(1, 0, 0);

	render->AddActor(sphereActor);

	vtkTransform *myTrans = vtkTransform::New ();
	myTrans->Translate (3,0,0);

	//myTrans->RotateZ (orientation[2]);
	//myTrans->RotateX (orientation[0]);
	//myTrans->RotateZ (orientation[1];
	//myTrans->Scale (scale[0],scale[1],scale[2]);
	//myTrans->Translate (-origin[0],-origin[1],-origin[2]);

	sphereActor->SetUserTransform(myTrans);



	vtkSmartPointer<vtkConeSource> coneSource =
			vtkSmartPointer<vtkConeSource>::New();
	coneSource->SetRadius(1);
	coneSource->SetHeight(5.5);
	coneSource->SetCenter(0, 0, 0);
	vtkSmartPointer<vtkPolyDataMapper> coneMapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
	coneMapper->SetInputConnection(coneSource->GetOutputPort());
	vtkSmartPointer<vtkActor> coneActor =
			vtkSmartPointer<vtkActor>::New();
	coneActor->SetMapper(coneMapper);


	render->AddActor(coneActor);


	double AXIS_LEN = 1.0;
	vtkSmartPointer<vtkAxesActor> oriAxesActor =
			vtkSmartPointer<vtkAxesActor>::New();
	oriAxesActor->SetPosition(0, 0, 0);
	oriAxesActor->SetTotalLength(AXIS_LEN, 2*AXIS_LEN, AXIS_LEN);
	oriAxesActor->SetShaftType(0);
	oriAxesActor->SetAxisLabels(0);
	oriAxesActor->SetCylinderRadius(0.02);

//	vtkSmartPointer<vtkAxesActor> axesActor =
//			vtkSmartPointer<vtkAxesActor>::New();
//	axesActor->SetPosition(0, 0, 0);

//	axesActor->SetTotalLength(AXIS_LEN, AXIS_LEN, AXIS_LEN*2);
//	axesActor->SetShaftType(0);
//	axesActor->SetAxisLabels(0);
//	axesActor->SetCylinderRadius(0.02);

	vtkSmartPointer<vtkTextActor> textActor =
			vtkSmartPointer<vtkTextActor>::New();
	textActor->SetPosition2(100, 40);
	textActor->GetTextProperty()->SetFontSize(24);
	textActor->GetTextProperty()->SetColor(1, 0, 0);


	vtkSmartPointer<vtkTransform> trans =
			vtkSmartPointer<vtkTransform>::New();

	trans->RotateZ(45);
	trans->Translate(-8, 0, 0);
	coneActor->SetUserTransform(trans);
	textActor->SetInput("trans->RotateZ(45)\ntrans->Translate(1, 0, 0)\nconeActor->SetUserTransform(trans)");
	//textActor->SetUserTransform(trans);

	cout << "GetMatrix:" << endl;
	if (coneActor->GetMatrix()!=NULL)
	{
		coneActor->GetMatrix()->Print(cout);
	}
	else
	{
		cout << "NULL" << endl;
	}
	cout << "GetUserMatrix:" << endl;
	if (coneActor->GetUserMatrix() !=NULL)
	{
		coneActor->GetUserMatrix()->Print(cout);
	}
	else
	{
		cout << "NULL" << endl;
	}

	render->AddActor(oriAxesActor);
	//render->AddActor(axesActor);
	render->AddActor(textActor);

	renWin->AddRenderer( render );
}

void MainWindow::cubesphereAxisBoxTranfor()
{
	//step 0: set it to a window:
	auto vw = new  QVTKOpenGLWidget(this) ;
	vtkRenderWindow *renWin = vw->GetRenderWindow();
	renWin->SetSize( 300, 300 );
	ui->tabWidget->addTab( vw, __FUNCTION__);

	vtkRenderer *render= vtkRenderer::New();

	render->SetBackground( 0.1, 0.2, 0.4 );


	vtkSmartPointer<vtkSphereSource> sphereSource =
			vtkSmartPointer<vtkSphereSource>::New();
	sphereSource->SetRadius(0.1);
	sphereSource->Update();
	vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
	sphereMapper->SetInputConnection(sphereSource->GetOutputPort());

	vtkSmartPointer<vtkActor> sphereActor =
			vtkSmartPointer<vtkActor>::New();
	sphereActor->SetPosition(0, 0, 0);
	sphereActor->SetMapper(sphereMapper);
	sphereActor->GetProperty()->SetColor(1, 0, 0);

	render->AddActor(sphereActor);

	vtkTransform *myTrans = vtkTransform::New ();
	myTrans->Translate (3,0,0);

	//myTrans->RotateZ (orientation[2]);
	//myTrans->RotateX (orientation[0]);
	//myTrans->RotateZ (orientation[1];
	//myTrans->Scale (scale[0],scale[1],scale[2]);
	//myTrans->Translate (-origin[0],-origin[1],-origin[2]);

	sphereActor->SetUserTransform(myTrans);



	vtkSmartPointer<vtkConeSource> coneSource =
			vtkSmartPointer<vtkConeSource>::New();
	coneSource->SetRadius(1);
	coneSource->SetHeight(5.5);
	coneSource->SetCenter(0, 0, 0);
	vtkSmartPointer<vtkPolyDataMapper> coneMapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
	coneMapper->SetInputConnection(coneSource->GetOutputPort());
	vtkSmartPointer<vtkActor> coneActor =
			vtkSmartPointer<vtkActor>::New();
	coneActor->SetMapper(coneMapper);


	render->AddActor(coneActor);


	double AXIS_LEN = 1.0;
	vtkSmartPointer<vtkAxesActor> oriAxesActor =
			vtkSmartPointer<vtkAxesActor>::New();
	oriAxesActor->SetPosition(0, 0, 0);
	oriAxesActor->SetTotalLength(AXIS_LEN, 2*AXIS_LEN, AXIS_LEN);
	oriAxesActor->SetShaftType(0);
	oriAxesActor->SetAxisLabels(0);
	oriAxesActor->SetCylinderRadius(0.02);


	vtkSmartPointer<vtkTextActor> textActor =
			vtkSmartPointer<vtkTextActor>::New();
	textActor->SetPosition2(100, 40);
	textActor->GetTextProperty()->SetFontSize(24);
	textActor->GetTextProperty()->SetColor(1, 0, 0);

	render->AddActor(oriAxesActor);
	//render->AddActor(axesActor);
	render->AddActor(textActor);

	renWin->AddRenderer( render );
//return;
	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
	iren->SetRenderWindow(renWin);


	//
	// By default the vtkRenderWindowInteractor instantiates an instance
	// of vtkInteractorStyle. vtkInteractorStyle translates a set of events
	// it observes into operations on the camera, actors, and/or properties
	// in the vtkRenderWindow associated with the vtkRenderWinodwInteractor.
	// Here we specify a particular interactor style.
	vtkInteractorStyleTrackballCamera *style =
	  vtkInteractorStyleTrackballCamera::New();
	iren->SetInteractorStyle(style);


	// of the input to the widget.
	vtkBoxWidget *boxWidget = vtkBoxWidget::New();
	boxWidget->SetInteractor(iren);
	boxWidget->SetPlaceFactor(1.25);

	//
	// Place the interactor initially. The input to a 3D widget is used to
	// initially position and scale the widget. The EndInteractionEvent is
	// observed which invokes the SelectPolygons callback.
	//
	boxWidget->SetProp3D(coneActor);
	boxWidget->PlaceWidget();
	vtkMyCallback *callback = vtkMyCallback::New();
	boxWidget->AddObserver(vtkCommand::InteractionEvent, callback);

	//
	// Normally the user presses the "i" key to bring a 3D widget to life. Here
	// we will manually enable it so it appears with the cone.
	//
	boxWidget->On();
	iren->Initialize();


}

void MainWindow::cubebox()
{
	//step 0: set it to a window:
	auto vw = new  QVTKOpenGLWidget(this) ;
	vtkRenderWindow *renWin = vw->GetRenderWindow();
	ui->tabWidget->addTab( vw, __FUNCTION__);

	vtkRenderer *render= vtkRenderer::New();

	render->SetBackground( 0.1, 0.2, 0.4 );

	vtkSmartPointer<vtkConeSource> coneSource =
			vtkSmartPointer<vtkConeSource>::New();
		coneSource->SetRadius(.2);
		coneSource->SetHeight(.5);
		coneSource->SetCenter(0, 0, 0);
		vtkSmartPointer<vtkPolyDataMapper> coneMapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		coneMapper->SetInputConnection(coneSource->GetOutputPort());
		vtkSmartPointer<vtkActor> coneActor =
			vtkSmartPointer<vtkActor>::New();
		coneActor->SetMapper(coneMapper);

		render->AddActor(coneActor);

		renWin->AddRenderer( render );


	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
	iren->SetRenderWindow(renWin);

	//
	// By default the vtkRenderWindowInteractor instantiates an instance
	// of vtkInteractorStyle. vtkInteractorStyle translates a set of events
	// it observes into operations on the camera, actors, and/or properties
	// in the vtkRenderWindow associated with the vtkRenderWinodwInteractor.
	// Here we specify a particular interactor style.
	vtkInteractorStyleTrackballCamera *style =
	  vtkInteractorStyleTrackballCamera::New();
	iren->SetInteractorStyle(style);


	// of the input to the widget.
	vtkBoxWidget *boxWidget = vtkBoxWidget::New();
	boxWidget->SetInteractor(iren);
	boxWidget->SetPlaceFactor(1.25);

	//
	// Place the interactor initially. The input to a 3D widget is used to
	// initially position and scale the widget. The EndInteractionEvent is
	// observed which invokes the SelectPolygons callback.
	//
	boxWidget->SetProp3D(coneActor);
	boxWidget->PlaceWidget();
	vtkMyCallback *callback = vtkMyCallback::New();
	boxWidget->AddObserver(vtkCommand::InteractionEvent, callback);

	//
	// Normally the user presses the "i" key to bring a 3D widget to life. Here
	// we will manually enable it so it appears with the cone.
	//
	boxWidget->On();

	iren->Initialize();


}

void MainWindow::cubecamera()
{
	//step 0: set it to a window:
	auto vw = new  QVTKOpenGLWidget(this) ;
	vtkRenderWindow *renWin = vw->GetRenderWindow();
	ui->tabWidget->addTab( vw, __FUNCTION__);


	// Create a sphere
	  vtkSmartPointer<vtkSphereSource> sphereSource =
		vtkSmartPointer<vtkSphereSource>::New();
	  sphereSource->SetCenter(0.0, 0.0, 0.0);
	  sphereSource->SetRadius(1.0);
	  sphereSource->Update();

	  // Create a mapper and actor
	  vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	  mapper->SetInputConnection(sphereSource->GetOutputPort());

	  vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	  actor->SetMapper(mapper);

	  vtkSmartPointer<vtkCamera> camera =
		vtkSmartPointer<vtkCamera>::New();
	  camera->SetPosition(13, 10, 20);
	  camera->SetFocalPoint(0, 2, 0);

	  // Create a renderer, render window, and interactor
	  vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();

	  renderer->SetActiveCamera(camera);

	  vtkSmartPointer<vtkRenderWindow> renderWindow = renWin;
	  renderWindow->AddRenderer(renderer);
	  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	  renderWindowInteractor->SetRenderWindow(renderWindow);

	  // Add the actor to the scene
	  renderer->AddActor(actor);
	  renderer->SetBackground(1,1,1); // Background color white

	  // Render and interact
	  renderWindow->Render();
	  renderWindowInteractor->Initialize();
	  //renderWindowInteractor->Start();


//	vtkRenderer *render= vtkRenderer::New();

//	render->SetBackground( 0.1, 0.2, 0.4 );

//	vtkSmartPointer<vtkConeSource> coneSource =
//			vtkSmartPointer<vtkConeSource>::New();
//		coneSource->SetRadius(.2);
//		coneSource->SetHeight(.5);
//		coneSource->SetCenter(0, 0, 0);
//		vtkSmartPointer<vtkPolyDataMapper> coneMapper =
//			vtkSmartPointer<vtkPolyDataMapper>::New();
//		coneMapper->SetInputConnection(coneSource->GetOutputPort());
//		vtkSmartPointer<vtkActor> coneActor =
//			vtkSmartPointer<vtkActor>::New();
//		coneActor->SetMapper(coneMapper);

//		render->AddActor(coneActor);

//		renWin->AddRenderer( render );

//		vtkSmartPointer<vtkCamera> camera =
//			vtkSmartPointer<vtkCamera>::New();
//		  camera->SetPosition(0, 10, 20);
//		  camera->SetFocalPoint(0, 0, 0);

//		  // Create a renderer, render window, and interactor
//		  vtkSmartPointer<vtkRenderer> renderer =
//			vtkSmartPointer<vtkRenderer>::New();

//		  renderer->SetActiveCamera(camera);


//	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
//	iren->SetRenderWindow(renWin);

//	//
//	// By default the vtkRenderWindowInteractor instantiates an instance
//	// of vtkInteractorStyle. vtkInteractorStyle translates a set of events
//	// it observes into operations on the camera, actors, and/or properties
//	// in the vtkRenderWindow associated with the vtkRenderWinodwInteractor.
//	// Here we specify a particular interactor style.
//	vtkInteractorStyleTrackballCamera *style =
//	  vtkInteractorStyleTrackballCamera::New();
//	iren->SetInteractorStyle(style);


//	// of the input to the widget.
//	vtkBoxWidget *boxWidget = vtkBoxWidget::New();
//	boxWidget->SetInteractor(iren);
//	boxWidget->SetPlaceFactor(1.25);

//	//
//	// Place the interactor initially. The input to a 3D widget is used to
//	// initially position and scale the widget. The EndInteractionEvent is
//	// observed which invokes the SelectPolygons callback.
//	//
//	boxWidget->SetProp3D(coneActor);
//	boxWidget->PlaceWidget();
//	vtkMyCallback *callback = vtkMyCallback::New();
//	boxWidget->AddObserver(vtkCommand::InteractionEvent, callback);

//	//
//	// Normally the user presses the "i" key to bring a 3D widget to life. Here
//	// we will manually enable it so it appears with the cone.
//	//
//	boxWidget->On();

//	// 新建一个相机对象
//	vtkSmartPointer<vtkCamera> camera =
//			vtkSmartPointer<vtkCamera>::New();

//	// 根据相机外矩阵，设置相机（光心）位置
//	camera->SetPosition(camTrans.at<double>(0),
//						camTrans.at<double>(1),
//						camTrans.at<double>(2));

//	// 根据相机外矩阵，设置焦点位置。设置完这两项成像平面已经唯一确定。
//	camera->SetFocalPoint(camRot.at<double>(0, 2) + camTrans.at<double>(0),
//						  camRot.at<double>(1, 2) + camTrans.at<double>(1),
//						  camRot.at<double>(2, 2) + camTrans.at<double>(2));

//	// 根据相机外矩阵，设置成像y正方向。是否有负号取决于原始的相机坐标系中，y是朝向相机上方（正）还是下方（负）。
//	camera->SetViewUp(- camRot.at<double>(0, 1),
//					  - camRot.at<double>(1, 1),
//					  - camRot.at<double>(2, 1));

//	// 计算视角。注意这里我的焦距值focus是负数，所以前面加负号。VTK中ViewAngle用角度表示。
//	viewAngle = - 2 * atan((sensorSize.height / 2) / focus) * 180 / CV_PI;
//	camera->SetViewAngle(viewAngle);

//	// 计算窗口中心。xh和yh分别是光学中心相对于传感器中心的偏移量。注意正方向规定的差异导致的负号。建议正负号都试一下。
//	windowCenter.x = -xh / (sensorSize.width / 2);
//	windowCenter.y = -yh / (sensorSize.height / 2);
//	camera->SetWindowCenter(windowCenter.x, windowCenter.y);

/*
	// HFlip
		render->GetActiveCamera()->SetViewUp(0, 1 ,0 );
		render->GetActiveCamera()->Azimuth(180);
		// end HFlip

		// VFlip
		render->GetActiveCamera()->SetViewUp(0, -1 ,0 );
		render->GetActiveCamera()->Elevation(-180);
		// end VFlip

		// rotation n degrees
		double n = -90.0f;
		render->GetActiveCamera()->Roll(n);*/




}

void MainWindow::cubetext()
{
	vtkSmartPointer<vtkBMPReader> texReader =
			vtkSmartPointer<vtkBMPReader>::New();
	texReader->SetFileName("/Users/rong/dfnet/user.bmp");

	vtkSmartPointer<vtkTexture> texture =
			vtkSmartPointer<vtkTexture>::New();
	texture->SetInputConnection(texReader->GetOutputPort());
	texture->InterpolateOn();


//	vtkSmartPointer<vtkJPEGReader>reader=vtkSmartPointer<vtkJPEGReader>::New();
//	//读入一张JPEG二维格式图
//	reader->SetFileName("...\\XXXXX.jpeg");

//	vtkSmartPointer<vtkTexture>texture=vtkSmartPointer<vtkTexture>::New();
//	//将读入的图片传入texture
//	texture->SetInputConnection(reader->GetOutputPort());
//	texture->InterpolateOn();

	vtkPlaneSource *cone = vtkPlaneSource::New();

	//
	// In this example we terminate the pipeline with a mapper process object.
	// (Intermediate filters such as vtkShrinkPolyData could be inserted in
	// between the source and the mapper.)  We create an instance of
	// vtkPolyDataMapper to map the polygonal data into graphics primitives. We
	// connect the output of the cone source to the input of this mapper.
	//
	vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
	coneMapper->SetInputConnection( cone->GetOutputPort() );

	//
	// Create an actor to represent the cone. The actor orchestrates rendering
	// of the mapper's graphics primitives. An actor also refers to properties
	// via a vtkProperty instance, and includes an internal transformation
	// matrix. We set this actor's mapper to be coneMapper which we created
	// above.
	//
	vtkActor *coneActor = vtkActor::New();
	coneActor->SetMapper( coneMapper );

	coneActor->SetTexture(texture);
	//
	// Create the Renderer and assign actors to it. A renderer is like a
	// viewport. It is part or all of a window on the screen and it is
	// responsible for drawing the actors it has.  We also set the background
	// color here.
	//
	vtkRenderer *ren1= vtkRenderer::New();
	ren1->AddActor( coneActor );
	ren1->SetBackground( 0.1, 0.2, 0.4 );

	render1 = ren1;

	//
	// Finally we create the render window which will show up on the screen.
	// We put our renderer into the render window using AddRenderer. We also
	// set the size to be 300 pixels by 300.
	//
	//---------
	auto vw = new  QVTKOpenGLWidget(this) ;
	vtkRenderWindow *renWin = vw->GetRenderWindow();
	ui->tabWidget->addTab( vw, "cone1");
	renWin1 = renWin;

	//vtkRenderWindow *renWin = vtkRenderWindow::New();
	//---------

	renWin->AddRenderer( ren1 );
	renWin->SetSize( 300, 300 );


	//step 5
	vtkSmartPointer<vtkTransform> transform =
		vtkSmartPointer<vtkTransform>::New();
	  transform->Translate(1, 0.0, 0.0);

	  vtkSmartPointer<vtkAxesActor> axes =
		vtkSmartPointer<vtkAxesActor>::New();

	  // The axes are positioned with a user transform
	  axes->SetUserTransform(transform);


	//绕Z轴旋转45^{\circ}
	vtkSmartPointer<vtkTransform> trans =
		vtkSmartPointer<vtkTransform>::New();
	trans->PostMultiply();
	trans->Translate(1, 0, 0);
	trans->RotateZ(45);
	coneActor->SetUserTransform(trans);

	renWin->Render();
}

void MainWindow::cylindertext()
{
	auto vw = new  QVTKOpenGLWidget(this) ;
	vtkRenderWindow *renWin = vw->GetRenderWindow();
	ui->tabWidget->addTab( vw, __FUNCTION__);


	vtkSmartPointer<vtkBMPReader> imageReader = vtkSmartPointer<vtkBMPReader>::New();
		imageReader->SetFileName("/Users/rong/dfnet/user.bmp");

		vtkSmartPointer<vtkTexture> texture = vtkSmartPointer<vtkTexture>::New();
		texture->SetInputConnection(imageReader->GetOutputPort());

		vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
		cylinder->SetHeight(20.0);
		cylinder->SetCenter(0, 0, 0);
		cylinder->SetRadius(3.0);
		cylinder->SetResolution(100);

		vtkSmartPointer<vtkTextureMapToCylinder> texturemap = vtkSmartPointer<vtkTextureMapToCylinder>::New();
		texturemap->SetInputConnection(cylinder->GetOutputPort());
		texturemap->SetPreventSeam(0);

		vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
		mapper->SetInputConnection(texturemap->GetOutputPort());

		vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
		actor->SetMapper( mapper );
		actor->SetTexture( texture );

		vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
		renderer->AddActor(actor);
		renderer->SetBackground(1.0, 1.0, 1.0);

		vtkSmartPointer<vtkRenderWindow> renderWindow = renWin;
		renderWindow->AddRenderer( renderer );

		vtkSmartPointer<vtkRenderWindowInteractor> renWinInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
		renWinInteractor->SetRenderWindow( renderWindow );

		renderWindow->Render();
		renWinInteractor->Initialize();

}

void MainWindow::timerEvent(QTimerEvent *event)
{
	//	int i;
//	 for (i = 0; i < 360; ++i)
//	 {
//	   // render the image
//	   renWin->Render();
//	   // rotate the active camera by one degree
//	   ren1->GetActiveCamera()->Azimuth( 1 );
//	 }
	if(index<360)
	{
		renWin1->Render();
		render1->GetActiveCamera()->Azimuth( 1 );
		index++;
	}
	else
	{
		renWin1->Render();
		render1->GetActiveCamera()->Azimuth( -360 );
		index++;
	}

}
void MainWindow::on_btnTimer_clicked()
{
	startTimer(500);
}
