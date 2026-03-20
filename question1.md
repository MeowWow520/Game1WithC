# Question 1: zoom 参数导致位置和碰撞检测 Bug 的原因分析

## 问题描述

当将 Objects.h 中每个结构体的 `zoom` 从 1 改为 2 时，对象生成的位置和重叠检测出现 bug。

## 根本原因

**问题核心：`zoom` 被重复乘了两次**

代码中存在对 `zoom` 的**不一致使用**，导致缩放计算被重复应用。

## 详细分析

### 1. Initialize() 中的缩放处理

在 `SceneMain::Initialize()` 中，对象的 `width` 和 `height` 已经被 `zoom` 修正：

```cpp
// 第 67-68 行
player.width *= player.zoom;
player.height *= player.zoom;
```

此时 `player.width` 已经等于 `原始宽度 × zoom`。

### 2. 位置计算中的重复缩放

在 `shootPlayer()` 函数中（第 196-199 行）：

```cpp
projectile->position.x = player.position.x +
                         player.width / 2 * player.zoom -  // ❌ 问题所在
                         projectile->width / 2 * projectile->zoom;
```

这里的问题是：
- `player.width` 已经是 `原始宽度 × zoom`
- 但代码又乘了一次 `player.zoom`
- 实际计算：`原始宽度 × zoom × zoom = 原始宽度 × zoom²`

当 zoom=2 时，实际计算的是 `原始宽度 × 4`，而不是正确的 `原始宽度 × 2`。

### 3. 其他受影响的位置

**碰撞检测计算**（第 227-231 行）：
```cpp
int projectileRectPosX = (int)(
    projectile->position.x + (projectile->width - projectile->hitboxWidth / 2 ) * projectile->zoom  // ❌ 重复缩放
);
```

**边界检测**（第 168-169 行）：
```cpp
if (player.position.y < gameInstance.getWindowHeight() -
                        (player.height - player.edgeDown) * player.zoom)  // ❌ 重复缩放
```

**玩家与敌人碰撞检测**（第 301-309 行）：
```cpp
int enemyRectPosX = (int)(enemy->position.x + (enemy->width - enemy->hitboxWidth / 2 ) * enemy->zoom);  // ❌
int playerRectPosX = (int)(player.position.x + (player.width - player.hitboxWidth) / 2 * player.zoom);  // ❌
```

### 4. 为什么 zoom=1 时正常工作

当 zoom=1 时：
- `原始宽度 × 1 = 原始宽度`
- `原始宽度 × 1 × 1 = 原始宽度`
- 重复乘 zoom 不会改变结果

## 具体影响

1. **位置偏移**：子弹生成位置错误，可能偏离玩家中心
2. **碰撞检测错误**：碰撞箱位置计算错误，导致碰撞检测不准确
3. **边界检查错误**：玩家可能无法正常到达屏幕边缘
4. **视觉不匹配**：渲染的图形和实际碰撞检测位置不对应

## 解决方案

有两种修复方式：

### 方案一：统一使用已缩放的值

修改位置计算，不再额外乘 `zoom`：

```cpp
// shootPlayer() 中修改为：
projectile->position.x = player.position.x + player.width / 2 - projectile->width / 2;

// 碰撞检测中修改为：
int projectileRectPosX = (int)(projectile->position.x + (projectile->width - projectile->hitboxWidth / 2));
```

### 方案二：统一使用未缩放的值

保持原始的 `width` 和 `height` 不变，只在需要渲染时应用缩放。

## 受影响的代码位置列表

1. `SceneMain.cpp` 第 168-179 行：`keyboardControl()` 边界检测
2. `SceneMain.cpp` 第 196-199 行：`shootPlayer()` 子弹位置计算
3. `SceneMain.cpp` 第 227-231 行：`updatePlayerProjectiles()` 碰撞箱位置
4. `SceneMain.cpp` 第 265 行：`spawEnemy()` 敌人生成位置
5. `SceneMain.cpp` 第 287 行：`shootEnemy()` 敌人子弹位置
6. `SceneMain.cpp` 第 301-312 行：`updatePlayer()` 碰撞检测
7. `SceneMain.cpp` 第 362-373 行：`updateEnemyProjectiles()` 碰撞检测

## 总结

Bug 的根本原因是代码中对 `zoom` 的使用不一致：在初始化时将 `width/height` 乘以了 `zoom`，但在后续的位置和碰撞计算中又重复乘以 `zoom`。当 zoom=1 时，这种重复没有影响；但当 zoom≠1 时，就会导致计算错误。

**建议的修复策略**：统一在 Initialize() 中应用缩放，后续代码直接使用已缩放的值，不再重复应用 zoom。
