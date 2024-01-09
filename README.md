**English(current)** | [中文版](zh_cn.md)
# Godot 4 RemoteCollisionShape2D
A `RemoteTransform2D`-like `Node2D` based on GDExtension, providing remote control of single/multiple collision shape(s).

# How to Install?
1. Clone the repo to any folders and copy the `gdextension` folder
2. Go into the directory of your project where a `project.godot` exists
3. Paste the folder you just copied to the directory

# How it Works
## Remote `CollisionShape2D`s
To remote one or more `CollisionShape2D`s, just resize the `remote_collision_shapes` in the inspector and fill in the colision shape(s). If no any `CollisionShape2D` is provided, a warning will be thrown to hint the developer that the node lacks collision shapes and you should offer references to them.

# Requirements
## Supported Godot Versions
4.2 or above

## Supported developing platforms
Windows 10, 11 x86-64
