root = g.node('root')
red = {0.5,0,0};
gre = {0,0.5,0};
blu = {0,0,0.5};

material = g.phong_material(red, red, 2)
material2 = g.phong_material(blu, blu, 5)
material3 = g.phong_material(gre, blu, 5)

cube = g.primitive_node("cube", "cube", material3) 
cube:rotate('x', 45)
cube:rotate('y', 45)
cube:scale(1.5,1.5,1.5)
cube:translate(0,1,8)
root:addChild(cube)

l1 = g.light({1,1,1}, {0,4,-5})

lights = {l1}

camera = g.camera({0,0,-5}, {0,1,0}, {0,0,1}, 256, 256, 50)
tracer = g.render(root, camera, lights, 'rotate-cube.png')
