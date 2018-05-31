# 网络指令：

## 旋转视角 正对 Kuka
vget /camera/0/rotation
vset /camera/0/rotation 10.000 -20.000 0.000

## 跳跃视角
vget /camera/0/location
vset /camera/0/location -3.757 -216.443 232.001

## 旋转 手臂
vget /object/Joint1/rotation
vset /object/Joint1/rotation 0.00 110.00 0.00

vget /object/Joint2/rotation
vset /object/Joint2/rotation 0.00 110.00 20.00

vget /object/Joint2/rotation
vset /object/Joint3/rotation 0.00 110.00 20.00

# Blueprint command
vexec KukaBP MotorOnForDegrees 0 -180 58

# Build-in command
vrun MotorOnForDegrees KukaBP 1 -180 500

