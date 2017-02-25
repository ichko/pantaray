#include <SDL.h>

#include "pantaray.hpp"
#include "sdl-init.hpp"

using namespace PantaRay;
using namespace PantaRay::Constants;

int main(int argc, char** argv) {

    auto width = 500;
    auto height = 500;

    auto renderer = Renderer(width, height);

    auto camera = PinholeCamera(pi / 2.5, width / height)
        .Set(Vector(10, 0, 20), Vector(10, 1, 20), Vector(0, 0, 1));

    auto plane_geometry = PlaneGeometry(Vector(0, 0, 0), Vector(0, 0, 1));
    auto sphere_geometry = SphereGeometry(Vector(30, 80, 30), 20);

    auto checker_shader = CheckerShader(Color(1, 1, 0), Color(0, 1, 0));
    auto sphere_checker_shader = CheckerShader(Color(1, 0, 0), Color(0, 0, 1), 0.01f);
    auto normal_shader = NormalShader();
    auto lambert_shader = LambertShader(Color(1, 0, 0));
    auto point_light = PointLight(Vector(-10, 50, 20), 422);

    auto scene = Scene()
        .Add(Mesh(plane_geometry, lambert_shader))
        .Add(Mesh(sphere_geometry, normal_shader))

        .Add(point_light);

    auto buffer = renderer.Render(camera, scene);

    init(width, height, buffer);

    return 0;

}