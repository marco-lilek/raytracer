root = g.Node('root')
red = g.Color(0.5,0,0);
gre = g.Color(0,0.5,0);
blu = g.Color(0,0,0.5);

sphere_square_uv = g.UVMesh("sphere-square-uv.obj")

material = g.PhongMaterial(g.Color(0.9, 0.8, 0.4), g.Color(0.8, 0.8, 0.4), 25)
sphere = g.GeometryNode("sphere", sphere_square_uv, material) 
sphere:scale(1.5,1.5,1.5)
sphere:translate(0,0,10)
root:addChild(sphere)

l1 = g.Light(g.Color(1,1,1), g.Point(0,4,-5))

lights = {l1}

camera = g.Camera(
  g.Point(0,0,-5), 
  g.Vector(0,1,0), 
  g.Vector(0,0,1),
  256, 
  256, 50)
tracer = g.RayTracer()

camera = g.Camera(
  g.Point(0,0,-5), 
  g.Vector(0,1,0), 
  g.Vector(0,0,1), 256, 256, 50)
tracer = g.RayTracer()
tracer:render(root, camera, lights, 'test-uv.png')