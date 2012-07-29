-- get objects
Player = getObject("Penguin")

centerCursor()

-- scene update
function onSceneUpdate()
	
	-- move
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

	-- center cursor
	centerCursor()
	
end