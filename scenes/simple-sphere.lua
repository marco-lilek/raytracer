root = gr.node('root')
red = {1,0,0};
gre = {0,1,0};
blu = {0,0,1};

material = gr.material(red, {0,1,0}, 25)
sphere = gr.sphere("sphere")
sphere:set_material(material)
sphere:scale(1.5,1.5,1.5)
sphere:translate(0,0,5)
root:add_child(sphere)

l1 = gr.light({0,10,-5}, {1,1,1}, {1,1,1})

lights = {l1}

tracer = gr.render(root, 'simple-sphere.png', 256, 256,
    {0,0,-5},{0,0,1},{0,1,0},50,{0.3,0.3,0.3},lights)
