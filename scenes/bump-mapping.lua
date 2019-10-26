root = gr.node('root')
red = {1,0,0};
gre = {0,1,0};
blu = {0,0,1};

bump = gr.texture("bumped", "crystal-bump")
material = gr.material(red, {0,1,0}, 25)
sphere = gr.uvsphere("sphere")
sphere:set_material(material)
sphere:set_bump(bump)
sphere:scale(1.5,1.5,1.5)
sphere:translate(0,0,5)
root:add_child(sphere)

l1 = gr.light({0,10,-5}, {1,1,1}, {1,1,1})

lights = {l1}

tracer = gr.render(root, 'bump-mapping.png', 256, 256,
    {0,0,-5},{0,0,1},{0,1,0},50,{0.3,0.3,0.3},lights)
