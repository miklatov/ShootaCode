#include "CollisionSystem.h"
#include "DataBank.h"
#include "GameObject.h"
#include "GameWindow.h"



void CollisionSystem::buildGrid()
{
    //announce
    std::cout << "CollisionSystem::buildGrid()" << std::endl;

    int xMax = pData->pGameWindow->screenDims.x / sectorSize.x;
    int yMax = pData->pGameWindow->screenDims.y / sectorSize.y;

    sectorGrid.resize(xMax);
    for(int x=0; x<xMax; ++x)
    {
        sectorGrid[x].resize(yMax);
    }

    //save grid size
    gridSize = Vector2d(xMax,yMax);

    std::cout << "Sector Size   : " << sectorSize << std::endl;
    std::cout << "x sector count: " << sectorGrid.size() << std::endl;
    std::cout << "y sector count: " << sectorGrid[0].size() << std::endl;
    std::cout << "Total Sectors : " << sectorGrid.size() * sectorGrid[0].size() << std::endl;

}

void CollisionSystem::updateGrid()
{
    //clear grid
    sectorGrid.clear();
    sectorGrid.resize(gridSize.x);
    for(int x=0; x<gridSize.x; ++x)
    {
        sectorGrid[x].resize(gridSize.y);
    }

    //clear objectSector map
    objectSectorMap.erase(objectSectorMap.begin(),objectSectorMap.end());

    //check all gameObjects in databank and bin into grid
    ObjectMap::iterator iObj = pData->objectMap.begin();
    while(iObj!=pData->objectMap.end())
    {
// TODO (shaldenby#1#): add check to ensure object is either in bound (i.e. on grid) or extend grid out? Also, sprite size ain't gonnawork properly when it's been rotated! think diamond vs squares...
       setSectorsForEntity(iObj);

        //top right and bottom right



        ++iObj;
    }

//            for (int y=0; y<gridSize.y; ++y)
//        {
//            for (int x=0; x<gridSize.x; ++x)
//            {
//                std::cout << sectorGrid[x][y].size();
//            }
//            std::cout << std::endl;
//        }

}

SectorList CollisionSystem::getSectorsForEntity(EntityId id)
{
    return objectSectorMap[id];
}


void CollisionSystem::setSectorsForEntity(ObjectMap::iterator &iObj)
{


    if(iObj->second==NULL)
    {
        return;
    }
    //add corners (tr=top left, bl=bottom right)
    Vector2d tl(int(iObj->second->coords.x/sectorSize.x) , int(iObj->second->coords.y/sectorSize.y));
    Vector2d br(int((iObj->second->coords.x + iObj->second->dims.x)/sectorSize.x) , int((iObj->second->coords.y + iObj->second->dims.y)/sectorSize.y));

    //check bounds
    if(tl.x >= 0 && tl.x < gridSize.x && tl.y >=0 && tl.y < gridSize.y)
    {
        //add topleft
//        std::cout << iObj->second->id << ": " << tl << "\t" << gridSize << std::endl;
        sectorGrid[tl.x][tl.y].push_back(iObj->second->id);
        objectSectorMap[iObj->second->id].push_back(Vector2d(tl.x,tl.y));

        //check if left in different grids to right etc
        if (tl.x == br.x && tl.y == br.y)
        {
    //            std::cout << "same" << std::endl;
        }
        //otherwise check bounds
        else if(br.x >= 0 && br.x < gridSize.x && br.y >=0 && br.y < gridSize.y)
        {
            if (tl.x!=br.x && tl.y!=br.y) //left to right and top to bottom difference
            {
                //check bounds

                sectorGrid[br.x][tl.y].push_back(iObj->second->id);   //topright
                objectSectorMap[iObj->second->id].push_back(Vector2d(br.x,tl.y));

                sectorGrid[tl.x][br.y].push_back(iObj->second->id);   //bottomleft
                objectSectorMap[iObj->second->id].push_back(Vector2d(tl.x,br.y));

                sectorGrid[br.x][br.y].push_back(iObj->second->id);   //bottomright
                objectSectorMap[iObj->second->id].push_back(Vector2d(br.x,br.y));

    //            std::cout << "all dif" << std::endl;
            }
            else if(tl.x!=br.x) //left to right difference
            {
                sectorGrid[br.x][tl.y].push_back(iObj->second->id);  //topright
                objectSectorMap[iObj->second->id].push_back(Vector2d(br.x,tl.y));
        //            std::cout << "lr dif" << std::endl;
            }
            else if(tl.y!=br.y) //top to bottom difference
            {
//                std::cout << tl.y << "," << br.y << std::endl;
                sectorGrid[tl.y][br.y].push_back(iObj->second->id);
        //            std::cout << "tb dif" << std::endl;
            }

        }

    }

}

IdSet CollisionSystem::getNeighboursOf(EntityId id)
{
    //first, figure squares that entity falls in
    SectorList sectors = getSectorsForEntity(id);

    //then, get the entities
    IdSet idSet;

    //for each sector
    SectorList::iterator iSector = sectors.begin();
    SectorList::iterator iSectorE= sectors.end();
    while(iSector!=iSectorE)
    {
        //for each entity in that sector (except for self (i.e. id);
        IdList::iterator iId = sectorGrid[iSector->x][iSector->y].begin();
        IdList::iterator iIdE= sectorGrid[iSector->x][iSector->y].end();
        while(iId!=iIdE)
        {
            if (*iId!=id)
            {
                idSet.insert(*iId);
            }
            ++iId;

        }
        ++iSector;
    }

    return idSet;
}

IdList CollisionSystem::detectCollisions(EntityId id)
{
    //first, get neighbours of query object
    IdSet neighbours = getNeighboursOf(id);

    //then look for collisions
    IdList collidesWith;
    IdSet::iterator iNeighbour = neighbours.begin();
    while(iNeighbour!=neighbours.end())
    {
        if (collision(id,*iNeighbour))
        {
//            std::cout << "Collision: " << id << "," << *iNeighbour << std::endl;
            collidesWith.push_back(*iNeighbour);
        }
        ++iNeighbour;
    }

    return collidesWith;
}

bool CollisionSystem::collision(EntityId a, EntityId b)
{
// TODO (shaldenby#1#): should put checks into verify presence on entity
    Vector2d aCo = pData->objectMap[a]->coords;
    Vector2d aDim= pData->objectMap[a]->dims;
    Vector2d bCo = pData->objectMap[b]->coords;
    Vector2d bDim= pData->objectMap[b]->dims;

    //centralise
    aCo+=(aDim/2);
    bCo+=(bDim/2);

    float radiusA = aDim.x/2;
    float radiusB = bDim.x/2;
    float colDist = radiusA + radiusB;
    int dx = aCo.x - bCo.x;
    int dy = aCo.y - bCo.y;
    if(sqrt(dx*dx + dy*dy) < colDist)
    {
        return true;
    }
    else
    {
        return false;
    }
    return  !((aCo.y + aDim.y < bCo.y)
            ||(aCo.y > bCo.y + bDim.y)
            ||(aCo.x > bCo.x + bDim.x)
            ||(aCo.x + aDim.x < bDim.x));

//    return (bCo.x > aCo.x && bCo.x < aCo.x+aDim.x && bCo.y > aCo.y && bCo.y < aCo.y + aDim.y) ||
//           (aCo.x > bCo.x && aCo.x < bCo.x+bDim.x && aCo.y > bCo.y && aCo.y < bCo.y + bDim.y);
//
//NOT (
//		(Rect1.Bottom < Rect2.Top) OR
//		(Rect1.Top > Rect2.Bottom) OR
//		(Rect1.Left > Rect2.Right) OR
//		(Rect1.Right < Rect2.Left) )
}

CollisionSystem::CollisionSystem(DataBank* t_pData)
{
    pData = t_pData;
    sectorSize = pData->pGameWindow->screenDims/10;
    buildGrid();
}
