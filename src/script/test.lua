mat_debug = g.DebugMaterial()
mat_white = g.PhongMaterial({0.5,0.5,0.5}, {0.2,0.2,0.2}, 10)
mat_red = g.PhongMaterial({0.5,0,0}, {0.2,0.2,0.2}, 10)
mat_glass = g.ReflectiveMaterial(5)

print('node')
root = g.Node('root')
s = g.SphereNode('sphere', mat_white)
root:addChild(s)
s:translate({0.1,0,10})

red = g.SphereNode('red', mat_red)
root:addChild(red)
red:scale({10,10,1})
red:translate({-0.5,0,-5})

print('mirrorey')
mirrorey = g.SphereNode('mirrorey', mat_glass)
root:addChild(mirrorey)
mirrorey:translate({-1,0,3})

lights = {}
print('tracer')
tracer = g.RayTracer()
print('render')
tracer:render(root, lights, 'test.png', 256, 256, {0.3, 0.3, 0.3})
