[English](README.md) | **中文版（当前页面）**
# Godot 4 Mathorm
基于GDExtension开发的一种`Node2D`节点，运作方式类似于`RemoteTransform2D`，用来远控单个/多个`CollisionShape2D`。

# 安装
1. 将本工程克隆到任意文件夹下，复制其中的`gdextension`文件夹
2. 打开你的游戏工程文件所在目录（即project.godot文件所在目录）
3. 将已复制好的`gdextension`文件夹粘贴在该目录下

# 使用方法
## 远控`CollisionShape2D`
若要远控单个或多个`CollisionShape2D`节点，只需在检查器中调整`remote_collision_shapes`的大小，然后填入受控碰撞箱节点即可。若该属性不含任何元素，则会在其右侧显示警告，提示开发者该节点缺少受控碰撞箱节点，需要提供对受控碰撞箱节点的引用。
## 同步`global_transform`与`shape`属性
设置好受控碰撞箱节点以后，这些受控节点并不会立即跟施控节点进行同步，以免因多个施控节点作用于同一个/组受控碰撞箱上而导致污染其属性，虽然无法在编辑器中直接查看`global_transform`的同步情况，但这并不表示无法进行真正的属性同步。可以调用`force_update_remote_shapes()`方法来手动将受控碰撞箱节点与调用该方法的施控节点`RemoteCollisionShape2D`进行同步，如有必要，也可以通过在编辑器中或编写代码启用`always_remote`属性来将其设为自动同步，自动同步会在 **每个物理帧** 中进行处理。
## 形状
本插件之所以叫做`RemoteCollisionShape2D`，正是因为它除了能同步`global_transform`以外，还能通过设置施控节点的`shape`属性来同步碰撞箱节点的`shape`属性。除此之外，为了方便开发者修改受控碰撞箱节点的`disabled`属性，也给`RemoteCollisionShape2D`增加了同名属性，一键控制所有受控碰撞箱节点的该属性，十分方便。

# 未来计划
1. 添加用于决定是否使用全局变换的属性。
2. 追踪受控碰撞箱节点的`position`、`rotation`及`scale`属性，可选择性启用或全部启用。

# 安装需求
## 支持的Godot版本
4.2及以上

## 支持的开发系统及平台
Windows 10, 11 x86-64
