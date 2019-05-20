root = g.Node('root')

sphere = g.GeometryNode("sphere", g.Sphere(), g.DebugMaterial())
root:addChild(sphere)

l1 = g.Light(g.Color(1,1,1), g.Point(0,0,0))

lights = {l1}

camera = g.Camera(
  g.Point(0,0,-5), 
  g.Vector(0,1,0), 
  g.Vector(0,0,1))
tracer = g.RayTracer()
tracer:render(root, camera, lights, 'test_tracer.png', 256, 256)
