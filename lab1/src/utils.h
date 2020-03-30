#pragma once


#include <array>
#include <vector>
#include <string>

#include "vtkSmartPointer.h"
#include "vtkSTLReader.h"
#include "vtkPolyData.h"


enum mk7 {
    left_arm, right_arm, body, legs
};

std::vector<vtkSmartPointer<vtkSTLReader>> read_mk7(const std::string& prefix_path,
                                                    const std::vector<mk7>& target_parts) {
    std::string extension = ".stl";

    std::vector<vtkSmartPointer<vtkSTLReader>> readers;
    for (mk7 part: target_parts) {
        std::string file_name;
        switch (part) {
        case mk7::body:
            file_name = "Body";
            break;
        case mk7::left_arm:
            file_name = "arm02";
            break;
        case mk7::right_arm:
            file_name = "arm01";
            break;
        case mk7::legs:
            file_name = "legs";
            break;
        }

        vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();
        reader->SetFileName((prefix_path + file_name + extension).c_str());
        reader->Update();
        readers.push_back(reader);

        std::cout << "Loaded: " << reader->GetOutput()->GetNumberOfPoints() << " points" << std::endl;
    }
    return readers;
}

std::array<double, 3> get_mean_point(vtkSmartPointer<vtkPolyData> output_data) {
    std::array<double, 3> mean_point = {0., 0., 0.};

    vtkIdType num_points = output_data->GetNumberOfPoints();
    for (vtkIdType i = 0; i < num_points; i++) {
        double current_point[3];
        output_data->GetPoint(i, current_point);

        mean_point[0] += current_point[0];
        mean_point[1] += current_point[1];
        mean_point[2] += current_point[2];
    }

    mean_point[0] /= num_points;
    mean_point[1] /= num_points;
    mean_point[2] /= num_points;

    return mean_point;
}
