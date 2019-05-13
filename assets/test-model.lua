mat = g.PhongMaterial({0.5,0.5,0.5}, {0.2,0.2,0.2}, 10)

prim_mesh = g.UVMesh("icosa.obj")

print('node')
root = g.Node('root')
d = g.GeometryNode('debug', prim_mesh, mat)
root:addChild(d)
d:rotate('y', 15)
d:translate({0,0,2})

l1 = g.Light({1,1,1}, {0,0,0})

lights = {l1}
print('tracer')
tracer = g.RayTracer()
print('render')
tracer:render(root, lights, 'test.png', 256, 256, {0.3, 0.3, 0.3})
