-- OBJECTS
bounding = getObject("bounding")
pingu = getObject("pingu")
Camera0 = getObject("Camera0")

-- Mouse Look stuff
dx = 0.0
dy = 0.0

centerCursor()
mx = getAxis("MOUSE_X")
my = getAxis("MOUSE_Y")

-- Scene update
function onSceneUpdate()

--------------
-- MLOOK STUFF
--------------

	rotate(bounding, {0, 0, -1}, dx*100) -- rotate Player (X mouse)
    rotate(bounding, {-1, 0, 0}, dy*100, "local")	-- rotate bounding (Y mouse)
	addCentralForce(bounding, {0, 0, 0.003}, "local")	

	--Just for test
	if isKeyPressed("S") then
	    setRotation(bounding, {0, 180, 0})
	end	
	
	-- get mouse direction
	dx = getAxis("MOUSE_X") - mx
	dy = getAxis("MOUSE_Y") - my

	-- center cursor
	centerCursor()
	
	mx = getAxis("MOUSE_X")
	my = getAxis("MOUSE_Y")		
    

-----------------
------------------

    --UP
    if isKeyPressed("MOUSE_BUTTON1") then addCentralForce(bounding, {0, 0.1, 0}, "local") end
	if isKeyPressed("A") then addCentralForce(bounding, {-0.5, 0, 0}, "local") end
	if isKeyPressed("Z") then addCentralForce(bounding, {0.5, 0, 0}, "local") end
	if isKeyPressed("D") then addCentralForce(bounding, {0, 0, -0.5}, "local") end
	if isKeyPressed("E") then addCentralForce(bounding, {0, 0, 0.5}, "local") end


end

