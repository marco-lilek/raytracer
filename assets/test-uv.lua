root = g.node('root')
red = {0.5,0,0};
gre = {0,0.5,0};
blu = {0,0,0.5};

sphere_square_uv = g.uvmesh("sphere-square-uv.obj")

--material = g.texture('earth.png')
material = g.phong_material(red, gre, 50)
sphere = g.geometry_node("sphere", sphere_square_uv, material) 
sphere:scale(1.5,1.5,1.5)
sphere:translate(0,0,10)
root:addChild(sphere)

l1 = g.light({1,1,1}, {0,4,-5})

lights = {l1}

camera = g.camera({0,0,-5}, {0,1,0}, {0,0,1}, 256, 256, 50)
tracer = g.render(root, camera, lights, 'test-uv.png')
