
class "MPhysics"
{
   ent;
   __init__ = function(self, ent)
		 self.ent = ent
	      end,

   addCentralForce = function(self, ...)
			local f = MVec3(...)
			addCentralForce(self.ent.id, {f.x, f.y, f.z})
		     end,

   addCentralForceLocal = function(self, ...)
			     local f = MVec3(...)
			     addCentralForce(self.ent.id, {f.x, f.y, f.z}, "local")
			  end,
   
   addTorque = function(self, ...)
		  local f = MVec3(...)
		  addTorque(self.ent.id, {f.x, f.y, f.z})
	       end,
   
   addTorqueLocal = function(self, ...)
		       local f = MVec3(...)
		       addTorque(self.ent.id, {f.x, f.y, f.z}, "local")
		    end,

   getLinearDamping = function(self)
			 return MVec(getLinearDamping(self.ent.id))
		      end,

   setLinearDamping = function(self, ...)
			 local d = MVec3(...)
			 return setLinearDamping(self.ent.id, {d.x, d.y, d.z})
		      end,

   getAngularDamping = function(self)
			 return getAngularDamping(self.ent.id))
		      end,

   setAngularDamping = function(self, d)
			 return setAngularDamping(self.ent.id, d)
		      end,

   clearForces = function(self)
		    clearForces(self.ent.id)
		 end,
}