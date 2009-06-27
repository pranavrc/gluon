#include "kglphysicsengine.h"
#include <KDebug>
KGLPhysicsEngine::KGLPhysicsEngine()
{

    m_gravity= b2Vec2(0.0f,-10.0f);
    createWorld();



}
KGLPhysicsEngine::~KGLPhysicsEngine()
{
    delete m_world;
}
void KGLPhysicsEngine::createWorld()
{
    b2AABB worldAABB;
    worldAABB.lowerBound.Set(-100.0f, -100.0f);
    worldAABB.upperBound.Set(100.0f, 100.0f);

    bool doSleep = true;
    m_world = new b2World(worldAABB, m_gravity, doSleep);

}

void KGLPhysicsEngine::mainLoop(float fps)
{
    computeSimulation(10,fps);

}

void KGLPhysicsEngine::addPhysicsItem(KGLPhysicsItem *  item)
{
    m_list.append(item);
    addItem(item);
    item->setup(m_world);

}

void KGLPhysicsEngine::remPhysicsItem(KGLPhysicsItem * item)
{
    m_list.removeOne(item);
    m_world->DestroyBody(item->body());
    removeItem(item);
}

void KGLPhysicsEngine::clearPhysicsItem()
{
    foreach ( KGLPhysicsItem * item, m_list)
    {
        m_world->DestroyBody(item->body());
        removeItem(item);
    }
    m_list.clear();
}
void KGLPhysicsEngine::computeSimulation(int32 iterations,float fps)
{
    float32 timeStep = 1.0f / fps;
    m_world->Step(timeStep, iterations);

    b2Body* node = m_world->GetBodyList();
    while (node)
    {
        b2Body* b = node;
        node = node->GetNext();

        if ( b->GetUserData()!=NULL)
        {
            KGLPhysicsItem* item = (KGLPhysicsItem*)b->GetUserData();
            item->updatePhysics();

        }

        //    if (myActor->IsDead())
        //    {
        //        myWorld->DestroyBody(b);
        //    }
    }



}

KGLPhysicsItem * KGLPhysicsEngine::itemAt(QPointF pos)
{
    b2AABB aabb;
    b2Vec2 d;
    b2Vec2 p(pos.x(),pos.y());
    d.Set(0.1, 0.1);
    aabb.lowerBound = p - d;
    aabb.upperBound = p + d;




    // Query the world for overlapping shapes.
    const int32 k_maxCount = 10;
    b2Shape* shapes[k_maxCount];
    int32 count = m_world->Query(aabb, shapes, k_maxCount);
    b2Body* body = NULL;
    for (int32 i = 0; i < count; ++i)
    {
        b2Body* shapeBody = shapes[i]->GetBody();
        if (shapeBody->IsStatic() == false && shapeBody->GetMass() > 0.0f)
        {
            bool inside = shapes[i]->TestPoint(shapeBody->GetXForm(), p);
            if (inside)
            {
                body = shapes[i]->GetBody();
                if (body->GetUserData()!=NULL)
                {
                    return (KGLPhysicsItem*)body->GetUserData();
                }
                break;
            }
        }
    }

    return NULL;

}
