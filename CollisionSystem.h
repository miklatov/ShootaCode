#ifndef COLLISIONSYSTEM_H_INCLUDED
#define COLLISIONSYSTEM_H_INCLUDED

#include "Vector2d.h"
#include <vector>
#include <list>
#include "Entity.h"
//forward decs
class DataBank;

typedef std::list<EntityId> IdList;
typedef std::set<EntityId> IdSet;
typedef std::list<Vector2d> SectorList;
typedef std::vector<std::vector <IdList> > SectorGrid;
typedef std::map<EntityId, SectorList > ObjectSectorMap;


class CollisionSystem
{
    private:
        void setSectorsForEntity(ObjectMap::iterator &iObj);
        IdSet getNeighboursOf(EntityId id);
        SectorList getSectorsForEntity(EntityId id);
        bool collision(EntityId a, EntityId b);
    public:
        DataBank* pData;
        ObjectSectorMap objectSectorMap;
        SectorGrid sectorGrid;
        Vector2d sectorSize;
        Vector2d gridSize;

        void buildGrid();
        void updateGrid();

        IdList detectCollisions(EntityId id);
        CollisionSystem(DataBank* t_pData);
};

#endif // COLLISIONSYSTEM_H_INCLUDED
