#ifndef AUDIOFX_SIM_MECHA_H
#define AUDIOFX_SIM_MECHA_H

#include "clock.h"
#include "math/point.h"

#include <vector>

namespace afx
{
namespace sim
{
namespace mecha
{

struct Material
{
    double spring;
    double mass;
    double dump;
    static const Material ground;
    Material(double mass, double spring, double dump);
};

struct Node;

struct Edge
{
    const Material *material;
    double length;
    math::Point force;
    Node *node0;
    Node *node1;

    Edge(const Material *material = nullptr);
    void connect(Node *node0, Node *node1);
    void update();
    math::Point getForceOn(Node *node);
};

struct Node
{
    const Material *material;
    math::Point pos;
    math::Point speed;
    bool locked;
    std::vector<Edge*> edges;

    Node(const Material *material = nullptr);
    void step(double timestep);
};

typedef std::vector<Node> Nodes;
typedef std::vector<Edge> Edges;

class Model
{
public:
    Model(const IClock &clock);
    void step();

protected:
    const IClock &clock;
    Node ground;
    Nodes nodes;
    Edges edges;
};

struct String : Model {
    String(int size, Material material, double pluckTime, const IClock &clock);
    void pluck();
    double operator()();
    double pluckTime;
    double startTime;
    Material material;
};

}
}
}

#endif
