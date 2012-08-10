
class "MCol"
{
   r;
   g;
   b;
   a;

   __init__ = function(self, ...)
		 self.r = 0
		 self.g = 0
		 self.b = 0
		 self.a = 1
		 
		 args = {...}
		 if #args == 1 then
		    if classmatches(args[1], self) then
		       self.r = args[1].r
		       self.g = args[1].g
		       self.b = args[1].b
		       self.a = args[1].a
		    elseif type(args[1]) == "table" then
		       self.r = args[1][1]
		       self.g = args[1][2]
		       self.b = args[1][3]
		       if #args[1] >= 4 then self.a = args[1][4] end
		    end
		 elseif #args >= 3 then
		    self.r = args[1]
		    self.g = args[2]
		    self.b = args[3]
		    if #args >= 4 then  self.a = args[4] end
		 end
		 
		 if self.r > 1 then self.r = self.r / 255 end
		 if self.g > 1 then self.g = self.g / 255 end
		 if self.b > 1 then self.b = self.b / 255 end
		 if self.a > 1 then self.a = self.a / 255 end
	      end,

   __getattr__ = function(self, key)
		    if key == 1 then return self.r
		    elseif key == 2 then return self.g
		    elseif key == 3 then return self.b
		    elseif key == 4 then return self.a
		    else return end
		 end,
}