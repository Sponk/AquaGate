dofile("MUtil.lua")
Player = getObject("Penguin")

obj = MEntity("Penguin")
phys = MPhysics(obj)

function onSceneUpdate()

   if isKeyPressed("UP") then
      addCentralForce(Player, {0, 6, 0}, "local")
   end

   if isKeyPressed("DOWN") then
      addCentralForce(Player, {0, -6, 0}, "local")
   end
   
   if isKeyPressed("LEFT") then
      addCentralForce(Player, {-3, 0, 0}, "local")
   end
   
   if isKeyPressed("RIGHT") then
      addCentralForce(Player, {3, 0, 0}, "local")
   end	
   
   if isKeyPressed("A") then
      addCentralForce(Player, {0, 0, 3}, "local")
   end
   
   if isKeyPressed("Z") then
      addCentralForce(Player, {0, 0, -3}, "local")
   end	

   if isKeyPressed("T") then
      phys:addCentralForceLocal({0, 6, 0})
   end

end

--function penguinUpdate(obj)
--end