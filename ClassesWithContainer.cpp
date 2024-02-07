#include "pch.h"
#include "framework.h"
#include "ClassesWithContainer.h"
#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <memory>
#include <cmath>
#include <list>
using namespace std;

class MapObject {
public:
    MapObject(float x, float y);
    void GetInfo();
    shared_ptr<MapObject> clone() const;
    void SetName(string name);
    string GetName();
    float GetX();
    float GetY();
    void SetLocation(float x, float y);
    void operator () (float dx, float dy);
private:
    float x, y;
    string name;
};

MapObject::MapObject(float x, float y) { this->x = x; this->y = y; }
void MapObject::SetLocation(float x, float y) { this->x = x; this->y = y; }
void MapObject::GetInfo() { cout << "name:" << name << ", (x, y) = (" << x << ", " << y << ")" << endl; }
float MapObject::GetX() { return x; }
float MapObject::GetY() { return y; }
void MapObject::operator () (float dx, float dy)
{
    float X = this->GetX();
    float Y = this->GetY();
    float newX = X + dx;
    float newY = Y + dy;
    SetLocation(newX, newY);
}
shared_ptr<MapObject> MapObject::clone() const
{
    return make_shared<MapObject>(*this);
}
void MapObject::SetName(string name) { this->name = name; }
string MapObject::GetName() { return name; } 

class Map {
public:
    void AddObject(MapObject& object);
    void GetMapInfo();
    Map();
    void MoveRobot(MapObject& robot, float dx, float dy);
private:
    vector<shared_ptr<MapObject>> MapContainer;
};

Map::Map()
{
    vector<shared_ptr<MapObject>> MapContainer = vector<shared_ptr<MapObject>>();
}
void Map::AddObject(MapObject& object) 
{ 
    if (object.GetName() == "robot")
    {
        MapContainer.insert(MapContainer.begin(), object.clone());
    }
    else    MapContainer.push_back(object.clone()); 
}
void Map::GetMapInfo() 
{ 
    int mapLength = MapContainer.size();
    cout << "Map Contains " << mapLength << " objects" << endl;
    for (int i = 0; i < mapLength; i++)
    {
        MapContainer[i]->GetInfo();
    }
}
void Map::MoveRobot(MapObject& robot, float dx, float dy)
{
    MapContainer.erase(MapContainer.begin());
    cout << "Robot is moving, (dx, dy) = (" << dx << ", " << dy << ")" << endl;
    // изменение полей координат в самом объекте с помощью перегруженного оператора "()"
    robot(dx, dy);
    this->AddObject(robot);
}

extern "C"
{
    MapObject* CreateMapObject(float x, float y) { return new MapObject(x, y); }
    void PrintingInfo(MapObject* object) { object->GetInfo(); }
    void SetObjectName(MapObject* object, char* new_name) { object->SetName(new_name); }
    void SetObjLocation(MapObject* object, float x, float y) { object->SetLocation(x, y); }
    Map* CreateMap() { return new Map(); }
    void AddObjectToMap(Map* mapInit, MapObject* object) { mapInit->AddObject(*object); }
    void GetInfoAboutMap(Map* mapItem) { mapItem->GetMapInfo(); }
    void MoveRobot(Map* mapItem, MapObject* robot, float dx, float dy) { mapItem->MoveRobot(*robot, dx, dy); }
}