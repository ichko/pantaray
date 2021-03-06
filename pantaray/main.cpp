#include <SDL.h>
#include <time.h>

#include "hpp/pantaray.hpp"
#include "hpp/sdl-init.hpp"

using namespace PantaRay;
using namespace PantaRay::Constants;

void first_test();
void second_test();

int main(int argc, char** argv) {
    // first_test();
    second_test();

    return 0;
}

void first_test() {
    unsigned width = 400;
    unsigned height = 400;

    auto renderer = Renderer(width, height, Color(0.01f, 0.01f, 0.01f));
    renderer.anti_aliasing = true;

    auto camera = PinholeCamera(pi / 2.5f, float(width) / float(height))
        .Set(Vector(0, 0, 10), Vector(0, 1, 10));

    auto plane_geometry_bottom = PlaneGeometry(Vector(0, 0, 0), Vector(0, 0, 1));
    auto plane_geometry_top = PlaneGeometry(Vector(0, 0, 45), Vector(0, 0, -1));
    auto plane_geometry_left = PlaneGeometry(Vector(-20, 0, 0), Vector(1, 0, 0));
    auto plane_geometry_right = PlaneGeometry(Vector(20, 0, 0), Vector(-1, 0, 0));

    auto sphere_geometry = SphereGeometry(Vector(5, 30, 6), 6);

    auto solid_texture_red = SolidColorTexture(Color(0.9f, 0.1f, 0.2f));
    auto solid_texture_blue = SolidColorTexture(Color(0.2f, 0.2f, 0.9f));
    auto solid_texture_white = SolidColorTexture(Color(0.8f, 0.8f, 0.1f));
    auto checker_texture = CheckerTexture(Color(0.1f, 0.1f, 0.1f), Color::White());
    auto checker_texture_sphere = CheckerTexture(Color(0.9f, 0.1f, 0.1f), Color(0.1f, 0.1f, 0.9f), 0.1f);

    auto phong_shader = PhongShader(6, 10);
    auto lambert_shader = PhongShader();

    auto point_light_left = PointLight(Vector(10, 20, 30), 650);

    auto scene = Scene()
        .Add(Mesh(plane_geometry_top, lambert_shader, solid_texture_white))
        .Add(Mesh(plane_geometry_bottom, lambert_shader, checker_texture))
        .Add(Mesh(plane_geometry_left, lambert_shader, solid_texture_red))
        .Add(Mesh(plane_geometry_right, lambert_shader, solid_texture_blue))

        .Add(Mesh(sphere_geometry, phong_shader, checker_texture_sphere))

        .Add(point_light_left);

    clock_t tStart = clock();

    auto buffer = renderer.Render(camera, scene);

    printf("Time taken: %.6fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

    init(width, height, buffer);
}

void second_test() {
    unsigned width = 500;
    unsigned height = 500;

    auto renderer = Renderer(width, height, Color(0.01f, 0.01f, 0.01f));
    renderer.anti_aliasing = true;

    auto camera = PinholeCamera(pi / 2.5f, float(width) / float(height))
        .Set(Vector(10, 0, 20), Vector(10, 1, 20), Vector(0, 0, 1));

    auto plane_geometry_top = PlaneGeometry(Vector(0, 0, 0), Vector(0, 0, 1));
    auto plane_geometry_bottom = PlaneGeometry(Vector(0, 0, 60), Vector(0, 0, -1));
    auto plane_geometry_left = PlaneGeometry(Vector(-20, 0, 0), Vector(1, 0, 0));
    auto plane_geometry_back = PlaneGeometry(Vector(0, 100, 0), Vector(0, -1, 0));
    auto plane_geometry_right = PlaneGeometry(Vector(50, 0, 0), Vector(-1, 0, 0));


    auto sphere_geometry = SphereGeometry(Vector(35, 80, 30), 20);
    auto sphere_geometry_small = SphereGeometry(Vector(12, 75, 30), 12);
    auto sphere_geometry_big = SphereGeometry(Vector(-10, 75, 0), 25);

    auto checker_texture_big = CheckerTexture(Color(0.8f, 0.8f, 0.8f), Color(0.1f, 0.1f, 0.1f));
    auto checker_texture_small = CheckerTexture(Color(0.8f, 0.8f, 0.8f), Color(0.3f, 0.3f, 0.3f), 1.0f / 15);
    auto red_texture = SolidColorTexture(Color(1.0f, 0.0f, 0.0f));

    auto sphere_checker_shader = CheckerTexture(Color(1, 0, 0), Color(0, 0, 1), 0.01f);
    auto normal_shader = NormalShader();
    auto reflection_shader = ReflectionShader(0.8f);

    auto lambert_shader_red = PhongShader();
    auto lambert_shader = PhongShader();

    auto point_light_red = PointLight(Vector(10, 40, 25), 550, Color(1, 0, 0));
    auto point_light_green = PointLight(Vector(15, 40, 40), 500, Color(0, 1, 0));
    auto point_light_blue = PointLight(Vector(30, 40, 30), 500, Color(0, 0, 1));
    auto point_light_big = PointLight(Vector(30, 80, 55), 400, Color(1, 1, 1));

    auto ambient_light = AmbientLight(Color(0.1f, 0.05f, 0.05f));

    auto scene = Scene()
        .Add(Mesh(plane_geometry_top, lambert_shader, checker_texture_big))
        .Add(Mesh(plane_geometry_bottom, lambert_shader_red, checker_texture_big))
        .Add(Mesh(plane_geometry_left, lambert_shader_red, red_texture))
        .Add(Mesh(plane_geometry_back, lambert_shader_red, red_texture))
        .Add(Mesh(plane_geometry_right, lambert_shader_red, red_texture))

        .Add(Mesh(sphere_geometry, reflection_shader))
        .Add(Mesh(sphere_geometry_small, lambert_shader))
        .Add(Mesh(sphere_geometry_big, reflection_shader, checker_texture_small))

        .Add(point_light_red)
        .Add(point_light_green)
        .Add(point_light_blue)
        .Add(point_light_big)

        .Add(ambient_light);

    clock_t tStart = clock();

    auto buffer = renderer.Render(camera, scene);

    printf("Time taken: %.6fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

    init(width, height, buffer);
}
