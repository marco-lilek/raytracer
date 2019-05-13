-- A simple scene with five spheres

print('materials')
mat1 = g.PhongMaterial({0.7, 1.0, 0.7}, {0.5, 0.7, 0.5}, 25)
mat2 = g.PhongMaterial({0.5, 0.5, 0.5}, {0.5, 0.7, 0.5}, 25)
mat3 = g.PhongMaterial({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25)

scene_root = g.Node('root')

print('s1')
s1 = g.SphereNode('s1', mat1)
s1:scale({100,100,100})
s1:translate({0,0,-400})
scene_root:addChild(s1)

print('s2')
s2 = g.SphereNode('s2', mat1)
s2:scale({150,150,150})
s2:translate({200,50,-100})
scene_root:addChild(s2)

print('s3')
s3 = g.SphereNode('s3', mat2)
s3:scale({1000,1000,1000})
s3:translate({0,-1200,-500})
scene_root:addChild(s3)

print('s4')
s4 = g.SphereNode('s4', mat3)
s4:scale({25,25,25})
s4:translate({-100,25,-300})
scene_root:addChild(s4)

print('s5')
s5 = g.SphereNode('s5', mat1)
s5:scale({25,25,25})
s5:translate({0,100,-250})
scene_root:addChild(s5)

print('lights')
white_light = g.Light({-100.0, 150.0, 400.0}, {0.9, 0.9, 0.9})
orange_light = g.Light({400.0, 100.0, 150.0}, {0.7, 0.0, 0.7})

print('run')
lights = {white_light, orange_light}
tracer = g.RayTracer()
tracer:render(scene_root, lights, 'simple.png', 256, 256, {0.3, 0.3, 0.3})
