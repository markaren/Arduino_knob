#include <iostream>

#include "json.hpp"
#include "MovingAverageFilter.hpp"
#include <serial/serial.h>
#include <threepp/loaders/SVGLoader.hpp>
#include <threepp/threepp.hpp>

using namespace threepp;

namespace {

    auto loadSVG() {
        SVGLoader loader;
        auto svgData = loader.load("knob.svg");

        auto svg = Group::create();
        svg->position.x = -250;
        svg->scale.y *= -1;

        for (const auto &data: svgData) {

            auto fillColor = data.style.fill;
            if (fillColor && *fillColor != "none") {

                auto material = MeshBasicMaterial::create(
                        {{"color", data.path.color},
                         {"opacity", data.style.fillOpacity}});

                const auto shapes = SVGLoader::createShapes(data);

                auto geometry = ShapeGeometry::create(shapes);
                geometry->computeBoundingBox();
                geometry->center();

                auto mesh = Mesh::create(geometry, material);
                geometry->boundingBox->getCenter(mesh->position);
                mesh->name = data.style.id;
                mesh->visible = data.style.visibility;
                svg->add(mesh);
            }
        }

        return svg;
    }

}// namespace

int main() {

    Canvas canvas("Knob", {{"aa", 4}});
    GLRenderer renderer(canvas.size());

    Scene scene;
    scene.background = Color::grey;

    float frustumSize = 1000;
    OrthographicCamera camera(-frustumSize * canvas.aspect() / 2, frustumSize * canvas.aspect() / 2, frustumSize / 2, -frustumSize / 2, 0.1, 1000);
    camera.position.z = 1;

    canvas.onWindowResize([&](WindowSize size) {
        camera.left = -frustumSize * size.aspect() / 2;
        camera.right = frustumSize * size.aspect() / 2;
        camera.updateProjectionMatrix();
        renderer.setSize(size);
    });

    auto svg1 = loadSVG();
    auto knob1 = svg1->getObjectByName("knob");
    scene.add(svg1);

    auto svg2 = loadSVG();
    svg2->position.y = 500;
    auto knob2 = svg2->getObjectByName("knob");
    scene.add(svg2);

    serial::Serial serial("COM4", 9600, serial::Timeout::simpleTimeout(1000));

    Clock clock;
    MovingAverageFilter filter(5);
    canvas.animate([&]() {
        if (knob1 && serial.isOpen() && serial.available()) {
            auto line = serial.readline();
            try {
                nlohmann::json j = nlohmann::json::parse(line);
                float p1 = j["potVal1"].get<float>();
                float p2 = j["potVal2"].get<float>();

                filter.update(p1);

                knob1->rotation.z = math::mapLinear(filter.value(), 0, 1023, math::PI, math::PI * 2) + math::degToRad(45);
                knob2->rotation.z = math::mapLinear(p2, 0, 1023, math::PI, math::PI * 2) + math::degToRad(45);
            } catch (const std::exception &) {}
        }

        renderer.render(scene, camera);
    });
}
