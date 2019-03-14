mat_debug = g.DebugMaterial()

prim_mesh = g.Mesh("sphere-square-uv.obj")

print('node')
root = g.Node('root')
d = g.GeometryNode('debug', prim_mesh, mat_debug)
root:addChild(d)
d:translate({0,0,2})

l1 = g.Light({1,1,1}, {0,0,0})

lights = {l1}
print('tracer')
tracer = g.RayTracer()
print('render')
tracer:render(root, lights, 'test.png', 256, 256, {0.3, 0.3, 0.3})
