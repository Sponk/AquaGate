
class "MPhysics" (MEntity)
{
   addCentralForce = function(self, ...)
			local f = MVec3(...)
			addCentralForce(self.id, {f.x, f.y, f.z})
		     end,

   addCentralForceLocal = function(self, ...)
			     local f = MVec3(...)
			     addCentralForce(self.id, {f.x, f.y, f.z}, "local")
			  end,
   --[[
   addTorque = function(self, ...)
		  local f = MVec3(...)
		  addTorque(self.id, {f.x, f.y, f.z})
	       end,
   
   addTorqueLocal = function(self, ...)
		       local f = MVec3(...)
		       addTorque(self.id, {f.x, f.y, f.z}, "local")
		    end,

   getLinearDamping = function(self)
			 return MVec(getLinearDamping(self.id))
		      end,

   setLinearDamping = function(self, ...)
			 local d = MVec3(...)
			 return setLinearDamping(self.id, {d.x, d.y, d.z})
		      end,

   getAngularDamping = function(self)
			 return getAngularDamping(self.id))
		      end,

   setAngularDamping = function(self, d)
			 return setAngularDamping(self.id, d)
		      end,

   clearForces = function(self)
		    clearForces(self.id)
		 end,--]]
}