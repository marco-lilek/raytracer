mat_white = g.DebugMaterial()

print('node')
root = g.Node('root')
s = g.SphereNode('sphere', mat_white)
root:addChild(s)
s:translate({0,0,4})

lights = {}
print('tracer')
tracer = g.RayTracer()
print('render')
tracer:render(root, lights, 'singlesphere.png', 256, 256, {0.3, 0.3, 0.3})