-- test for hierarchical ray-tracers.
-- Thomas Pflaum 1996

gold = g.PhongMaterial(g.Color(0.9, 0.8, 0.4), g.Color(0.8, 0.8, 0.4), 25)
grass = g.PhongMaterial(g.Color(0.1, 0.7, 0.1), g.Color(0, 0,0), 0)
blue = g.PhongMaterial(g.Color(0.7, 0.6, 1), g.Color(0.5, 0.4, 0.8), 25)

scene = g.Node('scene')
scene:rotate('x', 23)
scene:translate(6, -2, -15)

-- the arc
arc = g.Node('arc')
scene:addChild(arc)
arc:translate(0,0,-10)
arc:rotate('y', 60)

p1 = g.GeometryNode("p1", g.Cube(), gold) 
arc:addChild(p1)
p1:scale(0.8, 4, 0.8)
p1:translate(-2.4, 0, -0.4)

p2 = g.GeometryNode("p2", g.Cube(), gold) 
arc:addChild(p2)
p2:scale(0.8, 4, 0.8)
p2:translate(1.6, 0, -0.4)

s = g.GeometryNode("s", g.Sphere(), gold) 
arc:addChild(s)
s:scale(4, 0.6, 0.6)
s:translate(0, 4, 0)

-- the floor
-- plane = g.GeometryNode( 'plane', g.Mesh('plane.obj'), grass)
-- scene:addChild(plane)
-- plane:scale(30, 30, 30)

-- sphere
-- poly = g.mesh( 'poly', g.Mesh('dodeca.obj' ), blue)
-- scene:addChild(poly)
-- poly:translate(-2, 1.618034, 0)

-- The lights
l1 = g.Light(g.Color(0.8,0.8,0.8), g.Point(200,200,400))
l2 = g.Light(g.Color(0.4,0.4,0.8), g.Point(0,5,-20))

lights = {l1, l2}

camera = g.Camera(
  g.Point(0,0,0), 
  g.Vector(0,1,0), 
  g.Vector(0,0,-1),
  256, 
  256, 50)
tracer = g.RayTracer()
tracer:render(scene, camera, lights, "hier.png")
