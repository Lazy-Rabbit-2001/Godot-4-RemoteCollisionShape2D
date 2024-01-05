#ifndef GD_REMOTE_COLLISION_SHAPE_2D
#define GD_REMOTE_COLLISION_SHAPE_2D

#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/shape2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/math.hpp>

using namespace godot;


class RemoteCollisionShape2D : public Node2D 
{
    GDCLASS(RemoteCollisionShape2D, Node2D)

private:
    TypedArray<CollisionShape2D> remote_collision_shapes;
    Ref<Shape2D> shape;
    bool disabled;
    Color debug_color;
    bool always_remote;

    Color _debug_disabled_color = Color(0.5, 0.5, 0.5, 0.25);

protected:
    static void _bind_methods();

public:
    // Constructor and Destructor

    RemoteCollisionShape2D();
    ~RemoteCollisionShape2D();

    // Built-ins
    void _draw() override;
    void _physics_process(double delta) override;
    PackedStringArray _get_configuration_warnings()
    {
        PackedStringArray warnings;
        if (remote_collision_shapes.is_empty())
        {
            warnings.append(tr("No collision shapes are remoted! Please set collision shapes to remote.", "Remote"));
        }
        return warnings;
    }

    // Methods
    void force_update_remote_shapes();

    // Setgets

    void set_remote_collision_shapes(TypedArray<CollisionShape2D> p_remote_collision_shapes);
    TypedArray<CollisionShape2D> get_remote_collision_shapes() const;
    void set_shape(Ref<Shape2D> p_shape);
    Ref<Shape2D> get_shape() const;
    void set_disabled(bool p_disabled);
    bool is_disabled() const;
    void set_debug_color(Color p_debug_color);
    Color get_debug_color() const;
    void set_always_remote(bool p_always_remote);
    bool is_always_remote() const;
};

#endif