#include "remote_collision_shape_2d.h"

#include "fast_syntax.hpp"

#include "godot_cpp/variant/variant.hpp"
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/script.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;
using namespace gde_fast_syntax;

void RemoteCollisionShape2D::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_remote_collision_shapes", "p_remote_collision_shapes"), &RemoteCollisionShape2D::set_remote_collision_shapes);
	ClassDB::bind_method(D_METHOD("get_remote_collision_shapes"), &RemoteCollisionShape2D::get_remote_collision_shapes);
	ClassDB::add_property("RemoteCollisionShape2D", PropertyInfo(Variant::ARRAY, "remote_collision_shapes", PROPERTY_HINT_ARRAY_TYPE, vformat("%s/%s:%s", Variant::OBJECT, PROPERTY_HINT_NODE_TYPE, "CollisionShape2D")), "set_remote_collision_shapes", "get_remote_collision_shapes");
	ClassDB::bind_method(D_METHOD("set_shape", "p_shape"), &RemoteCollisionShape2D::set_shape);
	ClassDB::bind_method(D_METHOD("get_shape"), &RemoteCollisionShape2D::get_shape);
	ClassDB::add_property("RemoteCollisionShape2D", PropertyInfo(Variant::OBJECT, "shape", PROPERTY_HINT_RESOURCE_TYPE, "Shape2D"), "set_shape", "get_shape");
	ClassDB::bind_method(D_METHOD("set_disabled", "p_disabled"), &RemoteCollisionShape2D::set_disabled);
	ClassDB::bind_method(D_METHOD("is_disabled"), &RemoteCollisionShape2D::is_disabled);
	ClassDB::add_property("RemoteCollisionShape2D", PropertyInfo(Variant::BOOL, "disabled"), "set_disabled", "is_disabled");
	ClassDB::bind_method(D_METHOD("set_debug_color", "p_debug_color"), &RemoteCollisionShape2D::set_debug_color);
	ClassDB::bind_method(D_METHOD("get_debug_color"), &RemoteCollisionShape2D::get_debug_color);
	ClassDB::add_property("RemoteCollisionShape2D", PropertyInfo(Variant::COLOR, "debug_color"), "set_debug_color", "get_debug_color");
	ClassDB::bind_method(D_METHOD("set_always_remote", "p_disabled"), &RemoteCollisionShape2D::set_always_remote);
	ClassDB::bind_method(D_METHOD("is_always_remote"), &RemoteCollisionShape2D::is_always_remote);
	ClassDB::add_property("RemoteCollisionShape2D", PropertyInfo(Variant::BOOL, "always_remote"), "set_always_remote", "is_always_remote");
}

RemoteCollisionShape2D::RemoteCollisionShape2D() {
	disabled = false;
	debug_color = Color(0.27, 0.55, 0.26, 0.4);
	always_remote = false;
}

RemoteCollisionShape2D::~RemoteCollisionShape2D() {}

void RemoteCollisionShape2D::_draw()
{
	if (!Engine::get_singleton()->is_editor_hint() && !get_tree()->is_debugging_collisions_hint()) {
		return;
	}
	if (shape != nullptr) {
		shape->draw(get_canvas_item(), disabled ? _debug_disabled_color : debug_color);
	}
}

void RemoteCollisionShape2D::_physics_process(double delta)
{
	if (!always_remote || !is_running_mode(this)) {
		return;
	}
	force_update_remote_shapes();
}

void RemoteCollisionShape2D::force_update_remote_shapes()
{
	for (int i = 0; i < remote_collision_shapes.size(); i++) {
		CollisionShape2D* clshape = Object::cast_to<CollisionShape2D>(get_node_or_null(remote_collision_shapes[i]));
		if (clshape == nullptr) {
			continue;
		}
		clshape->set_global_transform(get_global_transform());
		clshape->set_deferred("shape", shape);
		clshape->set_deferred("disabled", disabled);
	}
}

void RemoteCollisionShape2D::set_remote_collision_shapes(TypedArray<CollisionShape2D> p_remote_collision_shapes) {
	remote_collision_shapes = p_remote_collision_shapes;
	update_configuration_warnings();
}

TypedArray<CollisionShape2D> RemoteCollisionShape2D::get_remote_collision_shapes() const {
	return remote_collision_shapes;
}

void RemoteCollisionShape2D::set_shape(Ref<Shape2D> p_shape)
{
	shape = p_shape;
	Callable redraw = create_custom_callable_function_pointer<RemoteCollisionShape2D>(this, &Node2D::queue_redraw);
	if (shape != nullptr && !shape->is_connected("changed", redraw)) {
		shape->connect("changed", redraw);
	}
	redraw.call();
}

Ref<Shape2D> RemoteCollisionShape2D::get_shape() const
{
    return shape;
}

void RemoteCollisionShape2D::set_disabled(bool p_disabled)
{
	disabled = p_disabled;
	queue_redraw();
}

bool RemoteCollisionShape2D::is_disabled() const
{
    return disabled;
}

void RemoteCollisionShape2D::set_debug_color(Color p_debug_color)
{
	debug_color = p_debug_color;
	queue_redraw();
}

Color RemoteCollisionShape2D::get_debug_color() const
{
    return debug_color;
}

void RemoteCollisionShape2D::set_always_remote(bool p_always_remote)
{
	always_remote = p_always_remote;
}

bool RemoteCollisionShape2D::is_always_remote() const
{
    return always_remote;
}
