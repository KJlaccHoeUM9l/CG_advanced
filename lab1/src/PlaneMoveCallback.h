#pragma once


#include "vtkSmartPointer.h"
#include "vtkActor.h"
#include "vtkPlane.h"
#include "vtkCommand.h"
#include "vtkImplicitPlaneWidget2.h"
#include "vtkImplicitPlaneRepresentation.h"


class PlaneMoveCallback : public vtkCommand {
public:
    vtkSmartPointer<vtkPlane> plane;
    vtkSmartPointer<vtkActor> actor;

    PlaneMoveCallback(vtkSmartPointer<vtkPlane> plane_ = nullptr,
                      vtkSmartPointer<vtkActor> actor_ = nullptr) :
        plane(plane_),
        actor(actor_)
    {}

    static PlaneMoveCallback* New() {
        return new PlaneMoveCallback;
    }

    virtual void Execute(vtkObject* caller, unsigned long, void*) override {
        vtkSmartPointer<vtkImplicitPlaneWidget2> planeWidget =
            reinterpret_cast<vtkImplicitPlaneWidget2*>(caller);

        vtkSmartPointer<vtkImplicitPlaneRepresentation> representation =
            reinterpret_cast<vtkImplicitPlaneRepresentation*>(planeWidget->GetRepresentation());
        representation->GetPlane(plane);
    }
};
