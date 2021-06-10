class ctx_mgr:
	def __init__(self, raising=True):
		print("Created new contex manager object:", id(self))
		self.raising = raising
	def __enter__(self):
		print("__enter__ called.")
		cm = object()
		print("__enter__ returing object id:", id(cm))
		return cm 
	def __exit__(self, exc_type, exc_val, exc_tab):
		print("__exit__ called")
		if exc_type: # exc_type not None
			print("An exception occured")
			if self.raising:
				print("Re-raising exception")
			return not self.raising 
	