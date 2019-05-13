root = g.Node('root')

--l1 = g.Light({1,1,1}, {0,0,0})

lights = {}
tracer = g.RayTracer()
tracer:render(root, lights, 'test_tracer.png', 256, 256)
