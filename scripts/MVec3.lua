--module(..., package.seeall)

class "MVec3"
{
   x = 0;
   y = 0;
   z = 0;

   __init__ = function(self, v1, v2, v3)
		 if type(v1) == "number" and type(v2) == "number" and type(v3) == "number" then
		    self.x = v1 -- we've been passed 3 numbers, just stick them in
		    self.y = v2
		    self.z = v3
		 elseif type(v1) == "number" and v2 == nil and v3 == nil then
		    self.x = v1 -- we've only been given 1 number, use it for all
		    self.y = v1
		    self.z = v1
		 elseif classmatches(self, v1) then
		    self.x = v1.x -- we've been given another MVec3, copy it
		    self.y = v1.y
		    self.z = v1.z
		 else
		    self.x = v1[1] -- just assume we've been given a table, try and get values from it
		    self.y = v1[2]
		    self.z = v1[3]
		 end
	      end,

   __getattr__ = function(self, key)
		    if key == 1 or key == "x" then return self.x
		    elseif key == 2  or key == "y" then return self.y
		    elseif key == 3  or key == "z" then return self.z
		    else return end
		 end,

   __add__ = function(self, other)
		if classmatches(self, other) then
		   return MVec3(self.x + other.x, self.y + other.y, self.z + other.z)
		end
		if type(other) == "table" then
		   return MVec3(self.x + other[1], self.y + other[2], self.z + other[3])
		end
	     end,
   
   __sub__ = function(self, other)
		if classmatches(self, other) then
		   return MVec3(self.x - other.x, self.y - other.y, self.z - other.z)
		end
		if type(other) == "table" then
		   return MVec3(self.x - other[1], self.y - other[2], self.z - other[3])
		end
	     end,
   
   __mul__ = function(self, other)
		if classmatches(self, other) or type(other) == "table" then
		   return self:cross(other)
		end
		if type(other) == "number" then
		   return MVec3(self.x * other, self.y * other, self.z * other)
		end
	     end,

   -- I tried to make this work with the # operator, but I couldn't
   magnitude = function(self)
		  return math.sqrt(self:magnitudeSquared())
	       end,
   
   magnitudeSquared = function(self)
      return self.x^2 + self.y^2 + self.z^2
   end,

   cross = function(self, other)
	      if not classmatches(self, other) then
		 other = MVec3(other)
	      end
	      -- i j k
	      -- a b c
	      -- d e f
	      --
	      -- i(bf - ce), j(af - cd), k(ae - bd)
	      return MVec3( (self.y * other.z) - (self.z * other.y), -- i
			    (self.x * other.z) - (self.z * other.x), -- j
			    (self.x * other.y) - (self.y * other.x) )-- k
	   end,

   dot = function(self, other)
	    if not classmatches(self, other) then
	       other = MVec3(other)
	    end
	    return (self.x * other.x) + (self.y + other.y) + (self.z * other.z)
	 end,

   normalize = function(self)
		  local mag = self:magnitude()
		  self.x = self.x / mag
		  self.y = self.y / mag
		  self.z = self.z / mag
	       end,

   getNormalized = function(self)
		  local mag = self:magnitude()
		  return MVec3( self.x / mag,
				self.y / mag,
				self.z / mag )
	       end,
}