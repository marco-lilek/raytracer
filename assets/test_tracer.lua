root = g.Node('root')

l1 = g.Light({1,1,1}, g.Point(0,0,0))

lights = {l1}
tracer = g.RayTracer()
tracer:render(root, lights, 'test_tracer.png', 256, 256)
