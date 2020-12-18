#include "mecha.h"

#include <limits>
#include <cmath>

using namespace afx;
using namespace afx::sim::mecha;

const Material Material::ground = Material(std::numeric_limits<double>::infinity(), 0.0, 0.0);

Material::Material(double mass, double spring, double dump)
    : mass(mass), spring(spring), dump(dump)
{}

Edge::Edge(const Material *material)
    : material(material)
{
    node0 = node1 = nullptr;
    length = 0.0005;
}

void Edge::connect(Node *node0, Node *node1)
{
    this->node0 = node0;
    this->node1 = node1;
    node0->edges.push_back(this);
    node1->edges.push_back(this);
}

void Edge::update()
{
    auto diff = node1->pos + math::Point::X(length) - node0->pos;

    diff = diff - length * diff.normalized();

    auto m = (diff.abs() > 0) ? 1 : 1;

    force = material ? m * material->spring * diff : math::Point();
}

math::Point Edge::getForceOn(Node *node)
{
    return (node == node0) ? force :
           (node == node1) ? -1 * force :
                             math::Point();
}

Node::Node(const Material *material)
    : material(material)
{
    locked = false;
}

void Node::step(double timestep)
{
    if (!material) return;

    if (locked) {
        speed = math::Point();
        return;
    }

    math::Point force;

    for (auto *edge: edges)
        force += edge->getForceOn(this);

    if (speed.sqrAbs() > 0.0) {
        auto dump = - material->dump * speed.sqrAbs();
        force += dump * speed.normalized();
    }

    auto acc = force / material->mass;

    speed += acc * timestep;
    pos += speed * timestep;
}

Model::Model(const IClock &clock)
    : clock(clock), ground(&Material::ground)
{}

void Model::step()
{
    int subSteps = 5;

    auto dT = clock.getStep() / subSteps;

    for (int i = 0; i < subSteps; i++) {
        for (auto &edge : edges) edge.update();
        for (auto &node : nodes) node.step(dT);
    }
}

String::String(int size, Material material, double pluckTime, const IClock &clock)
    : Model(clock), material(material), pluckTime(pluckTime)
{
    startTime = 0;

    nodes.resize(size);
    edges.resize(size + 1);

    for (auto &node: nodes) node = Node(&this->material);
    for (auto &edge: edges) edge = Edge(&this->material);

    edges.front().connect(&ground, &nodes.front());
    for (auto i = 1; i < size; i++)
        edges[i].connect(&nodes[i-1], &nodes[i]);
    edges.back().connect(&nodes.back(), &ground);
}

void String::pluck()
{
    startTime = clock.getTime();
}

double String::operator()()
{
    step();

    auto F = edges.front().force - edges.back().force;
    ground.speed = F / 200;
    ground.pos += ground.speed * clock.getStep();
    ground.pos *= 0.98;

    const double initTime = .02;
    auto actTime = clock.getTime();
    auto timeSinceStart = actTime - startTime;
    auto i = 2 + 0 * nodes.size();
    if (timeSinceStart <= initTime * pluckTime) {
        nodes[i].locked = true;
        nodes[i].pos.y = timeSinceStart / initTime;
    }
    else nodes[i].locked = false;

    return ground.pos.abs() / 2;

    auto sum = 0.0;
    for (auto node : nodes) sum += node.pos.y;
    return sum / nodes.size() / 100;

    return F.y / 1000000;
}
