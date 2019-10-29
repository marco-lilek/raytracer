root = gr.node('root')
red = {1,0,0};
gre = {0,1,0};
blu = {0,0,1};

material = gr.reflective()
sphere = gr.sphere("sphere")
sphere:set_material(material)
sphere:scale(1,1,1)
sphere:translate(-2,0,0)
root:add_child(sphere)

--reflective
mirror = gr.refractive(2)
mirror_sphere = gr.sphere("mirror")
mirror_sphere:set_material(mirror)
mirror_sphere:scale(1,1,1)
mirror_sphere:translate(2,0,5)
root:add_child(mirror_sphere)

--backwall
bwall_mat = gr.material({0.5,0.5,0.5}, blu, 55)
bwall = gr.cube("wall")
bwall:set_material(bwall_mat)
bwall:translate(-0.5,-0.5,0)
bwall:scale(20,20,1)
bwall:translate(0,0,40)
root:add_child(bwall)

--sidewalls
for i = 1,4 do
    wall_mat = gr.material({0.5 * (i % 2),0.5,0.5}, red, 80)
    wall = gr.cube("wall")
    wall:set_material(wall_mat)
    wall:translate(-0.5,-0.5,0)
    wall:scale(81,21,1)
    wall:translate(0,0,10)
    wall:rotate('y',90)
    wall:rotate('z',90 *(i-1))
    root:add_child(wall)
end

l1 = gr.light({-1,2,-5}, {1,1,1}, {1,1,1})

lights = {l1}

tracer = gr.render(root, 'refractive.png', 256, 256,
    {0,0,-5},{0,0,1},{0,1,0},50,{0.3,0.3,0.3},lights)
