#include <vector>

#include "vtkSmartPointer.h"

#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"

#include "vtkSTLReader.h"
#include "vtkPolyDataMapper.h"
#include "vtkAppendPolyData.h"

#include "vtkActor.h"
#include "vtkPlane.h"
#include "vtkImplicitPlaneWidget2.h"
#include "vtkImplicitPlaneRepresentation.h"

#include "PlaneMoveCallback.h"
#include "utils.h"


int main() {
    // Read data
    std::vector<vtkSmartPointer<vtkSTLReader>> readers = 
        read_mk7("..\\..\\data\\iron_man_mk7\\", {mk7::body, mk7::left_arm, mk7::right_arm, mk7::legs});

    // Merge filter
    vtkSmartPointer<vtkAppendPolyData> append_filter =
        vtkSmartPointer<vtkAppendPolyData>::New();
    for (vtkSmartPointer<vtkSTLReader> reader: readers) {
        append_filter->AddInputData(reader->GetOutput());
    }

    // Widget
    vtkSmartPointer<vtkPlane> plane =
        vtkSmartPointer<vtkPlane>::New();
    plane->SetOrigin(1.0, 1.5, 2.0);
    plane->SetNormal(-0.4, 0.2, 1.0);

    // Mapper
	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(append_filter->GetOutputPort());
    mapper->AddClippingPlane(plane);

    // Actor
	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	// Renderer
    vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);

    // Window
	vtkSmartPointer<vtkRenderWindow> render_window =
		vtkSmartPointer<vtkRenderWindow>::New();
	render_window->AddRenderer(renderer);
    render_window->Render();

    // Interactor
	vtkSmartPointer<vtkRenderWindowInteractor> interactor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(render_window);

    // The callback will do the work
    vtkSmartPointer<PlaneMoveCallback> my_callback =
        vtkSmartPointer<PlaneMoveCallback>::New();
    my_callback->plane = plane;
    my_callback->actor = actor;

    vtkSmartPointer<vtkImplicitPlaneRepresentation> plane_representation =
        vtkSmartPointer<vtkImplicitPlaneRepresentation>::New();
    plane_representation->SetPlaceFactor(1.25);
    plane_representation->PlaceWidget(actor->GetBounds());
    plane_representation->SetNormal(plane->GetNormal());
    plane_representation->SetOrigin(plane->GetOrigin());

    vtkSmartPointer<vtkImplicitPlaneWidget2> plane_widget =
        vtkSmartPointer<vtkImplicitPlaneWidget2>::New();
    plane_widget->SetInteractor(interactor);
    plane_widget->SetRepresentation(plane_representation);
    plane_widget->AddObserver(vtkCommand::InteractionEvent, my_callback);
    
    // Render
    interactor->Initialize();
	render_window->Render();
    plane_widget->On();

    // Begin mouse interaction
	interactor->Start();

	return 0;
}
