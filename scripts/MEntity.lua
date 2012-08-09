--module('MEntity', package.seeall)

class "MEntity"
{
   id = 0;

   -- Constructor
   __init__ = function(self, id)
		 if classmatches(self, id) then
		    self.id = getClone(id.id) -- we're being passed an actual object, clone it
		 elseif type(id) == "string" then
		    self.id = getObject(id) -- we're being passed a name, look it up
		 else
		    self.id = id -- just assume we've been passed a valid id
		 end
	      end,
   
   -- just wrap the standard Maratis functions

   --[[
   Effort has been taken to match the standard lua interface
   as closely as possible. For this reason, we have the normal
   get{VALUE}/set{VALUE} pair.
   These functions usually take variable arguments, but we pass
   them to MVec3 in order for it to parse the arguments and give
   us valid values
   This, however, means that the order of arguments had to
   change on a couple of functions. In particular the rotation
   functions, the angle has to precede the axis, in order to
   correctly parse it
   Also, rather than mess around with similar issues for "local"
   a separate function has been created for each local function.
		 -- Philipp Geyer 08.08.2012
   --]]
   getPosition = function(self)
		    return MVec3(getPosition(self.id))
		 end,

   setPosition = function(self, ...)
		    local pos = MVec3(...)
		    setPosition(self.id, {pos.x, pos.y, pos.z})
		 end,

   translate = function(self, ...)
		  local pos = MVec3(...)
		  translate(self.id, {pos.x, pos.y, pos.z})
	       end,

   translateLocal = function(self, ...)
		  local pos = MVec3(...)
		  translate(self.id, {pos.x, pos.y, pos.z}, "local")
	       end,

   getRotation = function(self)
		    return MVec3(getRotation(self.id))
		 end,

   setRotation = function(self, ...)
		    local rot = MVec3(...)
		    setRotation(self.id, {rot.x, rot.y, rot.z})
		 end,

   rotate = function(self, angle, ...)
	       local rot = MVec3(...)
	       rotate(self.id, {rot.x, rot.y, rot.z}, angle)
	    end,

   rotateLocal = function(self, angle, ...)
	       local rot = MVec3(...)
	       rotate(self.id, {rot.x, rot.y, rot.z}, angle, "local")
	    end,

   getScale = function(self)
		 return MVec3(getScale(self.id))
	      end,

   setScale = function(self, ...)
		 local scale = MVec3(...)
		 setScale(self.id, {scale.x, scale.y, scale.z})
	      end,
   
   getClone = function(self)
		 return MEntity(getClone(self.id))
	      end,

   activate = function(self, val)
		 if val == false then
		    self:deactivate()
		 else
		    activate(self.id)
		 end
	      end,
   
   deactivate = function(self)
		   deactivate(self.id)
		end,

   isVisible = function(self)
		  return isVisible(self.id)
	       end,
   
   getBehaviour = function(self, id)
		     print(getVariable)
		     print(broadcastMessage)
		     --rtn = MBehaviour(getBehavior(self.id, id))
		     --rtn:setParentObject(self)
		     --return rtn
		  end,
}