
prim_sphere = g.Sphere()
prim_cube = g.Cube()

mat_red = g.PhongMaterial({0.5,0,0}, {0,0,0}, 10, 0)
mat_blue = g.PhongMaterial({0,0,0.5}, {0,0,0}, 10, 0)
mat_green = g.PhongMaterial({0,0.5,0}, {0,0,0}, 10, 0)
mat_white = g.PhongMaterial({0.5,0.5,0.5}, {0,0,0}, 10, 0)

print('side walls')
side_materials = {mat_red, mat_white, mat_blue, mat_white}
root = g.Node("root")
for i=0,3 do
  wall = g.GeometryNode(string.format('side-wall-%i', i), prim_cube, side_materials[i+1])
  root:addChild(wall)
  wall:scale({1.1,1,3})
  wall:translate({1,0,0})
  wall:rotate('z', 90 * (i))
end

print('front wall')
front = g.GeometryNode('front-wall', prim_cube, mat_white)
root:addChild(front)
front:scale({1,1,1})
front:translate({0,0,1.5})

print('sphere')
sphere = g.GeometryNode('sphere', prim_sphere, mat_green)
root:addChild(sphere)
sphere:scale({0.2,0.2,0.2})
sphere:translate({-0.28,0.28,0.8})

--for i=-1,1 do
--  for j=-1,1 do
--    for k=-1,1 do
--      wall = g.GeometryNode(string.format('wall%i-%i-%i', i, j, k), prim_cube, mat_white)
--      root:addChild(wall)
--      --wall:scale({0.5,4,8})
--      scale = 2
--      wall:translate({i*5,j*5,k*5})
--    end
--  end
--end
--
rayTracer = g.RayTracer()
rayTracer:render(root)
