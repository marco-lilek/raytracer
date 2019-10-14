root = g.node('root')
red = {1,0,0};
gre = {0,1,0};
blu = {0,0,1};

buckyball = g.uvmesh('sphere-square-uv')
material = g.bump("gravel-stone", {0.3,0,0}, {0,0,0.5}, 5)
sphere = g.geometry_node("bumped", buckyball, material) 
sphere:scale(1.5,1.5,1.5)
sphere:translate(0,0,5)
root:addChild(sphere)

l1 = g.light({1,1,1}, {0,4,-5})

lights = {l1}

camera = g.camera({0,0,-5}, {0,1,0}, {0,0,1}, 256, 256, 50)
tracer = g.render(root, camera, lights, 'bump-mapping.png')
