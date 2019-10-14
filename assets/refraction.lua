root = g.node('root')
red = {0.5,0,0};
gre = {0,0.5,0};
blu = {0,0,0.5};

material = g.phong_material(red, red, 2)
material2 = g.phong_material(blu, blu, 5)
material3 = g.phong_material(gre, blu, 5)
reflective_mat = g.refractive_material(1.4)
sphere = g.primitive_node("reflector", "sphere", reflective_mat) 
sphere:rotate('x', 45)
sphere:rotate('y', 45)
sphere:scale(1.5,1.5,1.5)
sphere:translate(-1,0,10)
root:addChild(sphere)

sphere2 = g.primitive_node("sphere2", "sphere", material2) 
sphere2:scale(1.5,1.5,1.5)
sphere2:translate(-3,0,5)
root:addChild(sphere2)

cube = g.primitive_node("green", "sphere", material3) 
cube:scale(50,50,1.5)
cube:translate(0,0,40)
root:addChild(cube)

l1 = g.light({1,1,1}, {0,4,-5})

lights = {l1}

camera = g.camera({0,0,-5}, {0,1,0}, {0,0,1}, 256, 256, 50)
tracer = g.render(root, camera, lights, 'refraction.png')
