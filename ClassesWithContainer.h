#pragma once

#include <windows.h>


#define LIBRARY_API __declspec(dllexport)

class MapObject;
class Map;

extern "C"
{
    LIBRARY_API MapObject* CreateMapObject(float x, float y);
    LIBRARY_API void PrintingInfo(MapObject* object);
    LIBRARY_API Map* CreateMap();
    LIBRARY_API void AddObjectToMap(Map* mapInit, MapObject* object);
    LIBRARY_API void GetInfoAboutMap(Map* mapItem);
    LIBRARY_API void SetObjectName(MapObject* object, char* new_name);
    LIBRARY_API void SetObjLocation(MapObject* object, float x, float y);
    LIBRARY_API void MoveRobot(Map* mapItem, MapObject* robot, float dx, float dy);
}
