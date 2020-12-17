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
    force = 0;
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
    force = material
            ? material->spring * (node1->pos - node0->pos)
            : 0.0;
}

double Edge::getForceOn(Node *node)
{
    return (node == node0) ? force :
           (node == node1) ? -force :
                             0.0;
}

Node::Node(const Material *material)
    : material(material)
{
    pos = 0;
    speed = 0;
}

void Node::step(double timestep)
{
    if (!material) return;

    auto force = 0.0;

    for (auto *edge: edges)
        force += edge->getForceOn(this);

    force += - material->dump * speed * speed * (speed < 0 ? -1 : 1);

    auto acc = force / material->mass;

    speed += acc * timestep;
    pos += speed * timestep;
}

Model::Model(const IClock &clock)
    : clock(clock), ground(&Material::ground)
{}

void Model::step()
{
    auto dT = clock.getStep();

    for (auto &edge : edges) edge.update();
    for (auto &node : nodes) node.step(dT);
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

    const double initTime = .001;
    auto actTime = clock.getTime();
    auto timeSinceStart = actTime - startTime;
    if (timeSinceStart <= initTime * pluckTime)
        nodes[nodes.size()/8].pos = timeSinceStart / initTime;

    auto sum = 0.0;
    for (auto &node : nodes) sum += fabs(node.pos);
    return sum / (nodes.size()/2);

//    return nodes[nodes.size()/8].pos;
}
