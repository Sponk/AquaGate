
class "MCamera" (MEntity)
{
   selectCamera = function(self)
		     changeCurrentCamera(self.id)
		  end,

   getClearColor = function(self)
		      return MCol(getCameraClearColor(self.id))
		   end,

   setClearColor = function(self, ...)
		      col = MCol(...)
		      setCameraClearColor(self.id, {col.r, col.g, col.b})
		   end,
}