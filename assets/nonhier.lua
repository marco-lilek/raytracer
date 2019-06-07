-- A simple scene with some miscellaneous geometry.

mat1 = g.PhongMaterial(g.Color(0.7, 1.0, 0.7), g.Color(0.5, 0.7, 0.5), 25)
mat2 = g.PhongMaterial(g.Color(0.5, 0.5, 0.5), g.Color(0.5, 0.7, 0.5), 25)
mat3 = g.PhongMaterial(g.Color(1.0, 0.6, 0.1), g.Color(0.5, 0.7, 0.5), 25)
mat4 = g.PhongMaterial(g.Color(0.7, 0.6, 1.0), g.Color(0.5, 0.4, 0.8), 25)

sphere = g.Sphere()
cube = g.Cube()

scene_root = g.Node('root')

s1 = g.GeometryNode('s1', sphere, mat1) --g.Color(0, 0, -400), 100)
scene_root:addChild(s1)
s1:scale(100,100,100)
s1:translate(0,0,-400)

s2 = g.GeometryNode('s2', sphere, mat1)
scene_root:addChild(s2)
s2:scale(150,150,150)
s2:translate(200,50,-100)

s3 = g.GeometryNode('s3', sphere, mat2)
scene_root:addChild(s3)
s3:scale(1000,1000,1000)
s3:translate(0,-1200,-500)

s4 = g.GeometryNode('s4', sphere, mat3)
scene_root:addChild(s4)
s4:scale(50,50,50)
s4:translate(-100,25,-300)

s5 = g.GeometryNode('s5', sphere, mat1)
scene_root:addChild(s5)
s5:scale(25,25,25)
s5:translate(0,100,-250)

b1 = g.GeometryNode('b1', cube, mat4)
scene_root:addChild(b1)
b1:scale(100,100,100)
b1:translate(-200,-125,0)

-- A small stellated dodecahedron.

dodec = g.Mesh( 'smstdodeca.obj' )
dodecNode = g.GeometryNode('dodec', dodec, mat3);
scene_root:addChild(dodecNode)

-- The lights
white_light = g.Light(g.Color(0.9, 0.9, 0.9), g.Point(-100.0, 150.0, 400.0))
orange_light = g.Light(g.Color(0.7, 0.0, 0.7), g.Point(400.0, 100.0, 150.0))

lights = {white_light, orange_light}

camera = g.Camera(
  g.Point(0,0,800), 
  g.Vector(0,1,0), 
  g.Vector(0,0,-1), 256, 256, 50)
tracer = g.RayTracer()
tracer:render(scene_root, camera, lights, "nonhier.png")

-- g.render(scene_root, 'nonhier.png', 256, 256,
-- 	  {0, 0, 800}, {0, 0, -1}, {0, 1, 0}, 50,
-- 	  {0.3, 0.3, 0.3}, {white_light, orange_light})
