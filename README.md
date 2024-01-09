**English(current)** | [中文版](zh_cn.md)
# Godot 4 RemoteCollisionShape2D
A `RemoteTransform2D`-like `Node2D` based on GDExtension, providing remote control of single/multiple `CollisionShape2D`(s).

# How to Install?
1. Clone the repo to any folders and copy the `gdextension` folder
2. Go into the directory of your project where a `project.godot` exists
3. Paste the folder you just copied to the directory

# How it Works
## Remote `CollisionShape2D`s
To remote one or more `CollisionShape2D`(s), just resize the `remote_collision_shapes` in the inspector and fill in the collision shape(s). If no any `CollisionShape2D` is provided, a warning will be thrown to hint the developer that the node lacks collision shapes and you should offer references to them.
## Synchornize `global_transform` and `shape`
After setting the remoted collision shape(s), remember that those who are remoted are NOT get synchornized immediately, which is designed to prevent from the pollution to the remoted collision shapes by multiple remoters. Though it is not allowed to preview the effect of `global_transform` synchornization in the editor, it doesn't mean there is no any method to really synchornize the `shape`(s) or `global_transform`. `force_update_remote_shapes()` is such a method that can be called to synchornize the collision shapes with the remoter (`RemoteCollisionShape2D`), in which the method is called, at the moment. Meanwhile, if necessary, it is also allowed to automatically synchornize it by turning on `always_remote`, which will make the method automatically called **each physics frame**.
## Shape
The reason why this extension is called `RemoteCollisionShape2D` is majorly because it not only allows to synchornize the `global_transform` of the remoted, but also, by setting `shape` of a remoter, the `shape` of the(se) collision shape(s) are done so as well. In addition, for convenience of changing `disabled` of the remoted one(s), the `disabled` property is also provided in this plugin, by switching which you can easily control `disabled` of them directly.

# Future plans
1. Option to decide whether to track global transform or local transform.
2. Tracks whether the `position`, `rotation`, `scale` or all or part of them.

# Requirements
## Supported Godot Versions
4.2 or above

## Supported developing platforms
Windows 10, 11 x86-64
