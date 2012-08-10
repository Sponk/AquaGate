dofile("MUtil.lua")

Player = getObject("Penguin")

mx = getAxis("MOUSE_X")
my = getAxis("MOUSE_Y")
print("Starting Script")

function onSceneUpdate()
   if not Penguin then
      print("First Script Update " .. getBehavior)
      Penguin = MPhysics("Penguin")
   end

   if isKeyPressed("UP") then
      Penguin:addCentralForceLocal(0, 6, 0)
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

   -- get mouse direction
   dx = getAxis("MOUSE_X") - mx
   dy = getAxis("MOUSE_Y") - my
   
   -- center cursor
   centerCursor()
   
   mx = getAxis("MOUSE_X")
   my = getAxis("MOUSE_Y")

   if not cam then
      cam = MCamera("Camera0")
      col = cam:getClearColor()
      print("Col: r(" .. col.r .. ") g(" .. col.g .. ") b(" .. col.b .. ")")
      cam:setClearColor(0, 255, 128)
   end

end
