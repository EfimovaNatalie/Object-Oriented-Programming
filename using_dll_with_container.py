import ctypes

lib = ctypes.WinDLL(r".\ClassesWithContainer.dll")

lib.CreateMapObject.argtypes = [ctypes.c_float, ctypes.c_float]
lib.CreateMapObject.restype = ctypes.c_void_p

lib.SetObjLocation.argtypes = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float]
lib.SetObjLocation.restype = None

lib.SetObjectName.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
lib.SetObjectName.restype = None

lib.PrintingInfo.argtypes = [ctypes.c_void_p]
lib.PrintingInfo.restype = None

lib.CreateMap.argtypes = None
lib.CreateMap.restype = ctypes.c_void_p

lib.AddObjectToMap.argtypes = [ctypes.c_void_p, ctypes.c_void_p]
lib.AddObjectToMap.restype = None

lib.MoveRobot.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_float, ctypes.c_float]
lib.MoveRobot.restype = None

lib.GetInfoAboutMap.argtypes = [ctypes.c_void_p]
lib.GetInfoAboutMap.restype = None

obj1 = lib.CreateMapObject(3, 5)
obj1_name = ctypes.c_char_p("landmark1".encode("utf-8"))
lib.SetObjectName(obj1, obj1_name)
lib.PrintingInfo(obj1)
obj2 = lib.CreateMapObject(2.4, 7.5)
obj2_name = ctypes.c_char_p("landmark2".encode("utf-8"))
lib.SetObjectName(obj2, obj2_name)
lib.PrintingInfo(obj2)
lib.SetObjLocation(obj2, 2, 7)
lib.PrintingInfo(obj2)
rob = lib.CreateMapObject(10, 8)
rob_name = ctypes.c_char_p("robot".encode("utf-8"))
lib.SetObjectName(rob, rob_name)
m = lib.CreateMap()
lib.AddObjectToMap(m, obj1)
lib.AddObjectToMap(m, obj2)
lib.AddObjectToMap(m, rob)
lib.GetInfoAboutMap(m)
lib.MoveRobot(m, rob, 1, -1)
lib.GetInfoAboutMap(m)