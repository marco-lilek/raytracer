g.echo()

prim_sphere = g.Sphere(1)
-- mat_mirror = g.Material({0.5,0.5,0.5}, {0.5,0.5,0.5}, 10, 0.9)
mat_green = g.PhongMaterial({0,0.5,0}, {0.5,0,0}, 10, 0)

node_root = g.Node("node_root")

node_center = g.GeometryNode("node_center", prim_sphere, mat_green)
node_center:scale({3,3,1})
node_root:addChild(node_center)

-- function makebehind(xt, yt)
--   local node_behind = g.GeometryNode(
--     "node_behind" .. xt .. yt, prim_sphere, mat_green)
--   node_behind:scale({3,3,1})
--   node_behind:translate({xt,yt,-6})
--   return node_behind
-- end

-- left = makebehind(-10, 0)
-- right = makebehind(5, 5)
-- node_root:addChild(left)
-- node_root:addChild(right)

rayTracer = g.RayTracer()
rayTracer:render(node_root)

