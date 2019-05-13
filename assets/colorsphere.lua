mat = g.PhongMaterial({0.5,0,0}, {0,0.5,0},10)

print('node')
root = g.Node('root')
s = g.SphereNode('sphere', mat)
root:addChild(s)
s:translate({0,0,4})

lights = {}
print('tracer')
tracer = g.RayTracer()
print('render')
tracer:render(root, lights, 'colorsphere.png', 256, 256, {0.3, 0.3, 0.3})
