dofile("MUtil.lua")

Player = getObject("Penguin")

mx = getAxis("MOUSE_X")
my = getAxis("MOUSE_Y")

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

   -- get mouse direction
   dx = getAxis("MOUSE_X") - mx
   dy = getAxis("MOUSE_Y") - my
   
   -- center cursor
   centerCursor()
   
   mx = getAxis("MOUSE_X")
   my = getAxis("MOUSE_Y")
end



function penguinUpdate(obj)
   -- rotate Player (X mouse)
   rotate(obj, {0, 0, -1}, dx*100)
end

function headUpdate(obj)
   -- rotate Head (Y mouse)
   rotate(obj, {-1, 0, 0}, dy*100, "local")
   rotation = getRotation(obj)
   if rotation[1] > 90 then
      rotation[1] = 90
   elseif rotation[1] < -90 then
      rotation[1] = -90
   end
   
   setRotation(obj, rotation)
end
