
class "MBehaviour"
{
   id = 0;
   parent = 0;
   variables = {}
   
   __init__ = function(self, id)
		 self.id = id
		 for i=0, getVariablesNumber(id) do
		    variables[getVariableName(id, i)] = i
		 end
	      end,
   
   setParentObject = function(self,parent)
			self.parent = parent
		     end,
   
   getParentObject = function(self)
			return self.parent
		     end,
   
   getVariable = function(self, name)
		    return getVariable(self.id, self.variables[name])
		 end,
   
   setVariable = function(self, name, val)
		    if type(val) == "boolean" then
		       if val == true then val = 1 else val = 0 end
		    end
		    setVariable(self.id, self.variables[name], val)
		 end,
}