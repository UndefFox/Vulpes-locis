#include "physicsengine.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

#include "components/transformation.h"
#include "components/colider.h"
#include "components/physicsData.h"

#include "ECS/include/ECS.h"

#include "types/vector3.h"

#include "Window/include/window.h"

namespace PhysicsEngineSystem
{

    namespace
    {

        static bool isEntityCompatable(int entityMask)
        {
            static const int systemMask =
                (1 << Entity::getTypeId<Transformation>()) |
                (1 << Entity::getTypeId<Colider>()) |
                (1 << Entity::getTypeId<PhysicsData>());

            return (entityMask & systemMask) == systemMask;
        }

        void circleToCircleColision(int f, int s)
        {
            Entity *entityF = ECS::getEntity(f);
            Transformation *transF = entityF->getComponent<Transformation>();
            SphereColider *coliderF = (SphereColider *)entityF->getComponent<Colider>();
            PhysicsData *physF = entityF->getComponent<PhysicsData>();

            Entity *entityS = ECS::getEntity(s);
            Transformation *transS = entityS->getComponent<Transformation>();
            SphereColider *coliderS = (SphereColider *)entityS->getComponent<Colider>();
            PhysicsData *physS = entityS->getComponent<PhysicsData>();

            // Check for colision
            if (!(ct::length(transF->position - transS->position) < coliderF->getRadius() + coliderS->getRadius()))
            {
                return;
            }

            ct::Vector3 normal = ct::normalize(transF->position - transS->position);
            float depth = coliderF->getRadius() + coliderS->getRadius() - ct::length(transF->position - transS->position);

            transF->position += normal * depth;
            transS->position -= normal * depth;
        }

        void circleToBoxColision(int f, int s)
        {
            Entity *entityF = ECS::getEntity(f);
            Transformation *transF = entityF->getComponent<Transformation>();
            SphereColider *coliderF = (SphereColider *)entityF->getComponent<Colider>();
            PhysicsData *physF = entityF->getComponent<PhysicsData>();

            Entity *entityS = ECS::getEntity(s);
            Transformation *transS = entityS->getComponent<Transformation>();
            BoxColider *coliderS = (BoxColider *)entityS->getComponent<Colider>();
            PhysicsData *physS = entityS->getComponent<PhysicsData>();

            ct::Vector3 transpoedVector = ct::transform(transF->position, -transS->position, -transS->rotation);
            transpoedVector -= coliderS->getSize() / 2.0f;
        }

        void boxToBoxColision(int f, int s)
        {
            Entity *entityF = ECS::getEntity(f);
            Transformation *transF = entityF->getComponent<Transformation>();
            BoxColider *coliderF = (BoxColider *)entityF->getComponent<Colider>();
            PhysicsData *physF = entityF->getComponent<PhysicsData>();

            Entity *entityS = ECS::getEntity(s);
            Transformation *transS = entityS->getComponent<Transformation>();
            BoxColider *coliderS = (BoxColider *)entityS->getComponent<Colider>();
            PhysicsData *physS = entityS->getComponent<PhysicsData>();

            ct::Vector3 sizeF = coliderF->getSize() / 2.0f;
            ct::Vector3 sizeS = coliderS->getSize() / 2.0f;

            // Working in space of entityF position

            std::array<ct::Vector3, 8> boxVertsF = {
                ct::transform(ct::Vector3(sizeF.x, sizeF.y, sizeF.z), transF->position, transF->rotation),
                ct::transform(ct::Vector3(sizeF.x, sizeF.y, -sizeF.z), transF->position, transF->rotation),
                ct::transform(ct::Vector3(sizeF.x, -sizeF.y, sizeF.z), transF->position, transF->rotation),
                ct::transform(ct::Vector3(sizeF.x, -sizeF.y, -sizeF.z), transF->position, transF->rotation),
                ct::transform(ct::Vector3(-sizeF.x, sizeF.y, sizeF.z), transF->position, transF->rotation),
                ct::transform(ct::Vector3(-sizeF.x, sizeF.y, -sizeF.z), transF->position, transF->rotation),
                ct::transform(ct::Vector3(-sizeF.x, -sizeF.y, sizeF.z), transF->position, transF->rotation),
                ct::transform(ct::Vector3(-sizeF.x, -sizeF.y, -sizeF.z), transF->position, transF->rotation)};

            std::array<ct::Vector3, 8> boxVertsS = {
                ct::transform(ct::Vector3(sizeS.x, sizeS.y, sizeS.z), transS->position, transS->rotation),
                ct::transform(ct::Vector3(sizeS.x, sizeS.y, -sizeS.z), transS->position, transS->rotation),
                ct::transform(ct::Vector3(sizeS.x, -sizeS.y, sizeS.z), transS->position, transS->rotation),
                ct::transform(ct::Vector3(sizeS.x, -sizeS.y, -sizeS.z), transS->position, transS->rotation),
                ct::transform(ct::Vector3(-sizeS.x, sizeS.y, sizeS.z), transS->position, transS->rotation),
                ct::transform(ct::Vector3(-sizeS.x, sizeS.y, -sizeS.z), transS->position, transS->rotation),
                ct::transform(ct::Vector3(-sizeS.x, -sizeS.y, sizeS.z), transS->position, transS->rotation),
                ct::transform(ct::Vector3(-sizeS.x, -sizeS.y, -sizeS.z), transS->position, transS->rotation)};

            ct::Vector3 colisionPos{};
            ct::Vector3 colisionNormal{};
            float colisionDepth = 9999999.0f;
            ct::Vector3 relativeVector = transS->position - transF->position;
            bool colisionFounded = true;

            // TODO: check vert colision for both boxes separated, then side colision

            // Check of vert colision into first box
            std::array<ct::Vector3, 3> boxFaceNormalsF = {
                ct::normalize(boxVertsF[3] - boxVertsF[7]), // Normal along first local X
                ct::normalize(boxVertsF[5] - boxVertsF[7]), // Normal along first local Y
                ct::normalize(boxVertsF[6] - boxVertsF[7])  // Normal along first local Z
            };

            for (int axisI = 0; axisI < 3; axisI++)
            {
                ct::Vector3 currentAxis = boxFaceNormalsF[axisI];

                // Making sure that all axis collinear to box relative vector so we need to get only
                // farthest vert of second box
                if (ct::dot(currentAxis, relativeVector) < 0)
                {
                    currentAxis = -currentAxis;
                }

                float higestF = -99999.0f;
                float lowestS = 999999.0f;
                int lowestId = -1;
                for (int vertI = 0; vertI < 8; vertI++)
                {
                    float projF = ct::dot(boxVertsF[vertI], currentAxis);
                    float projS = ct::dot(boxVertsS[vertI], currentAxis);

                    if (projF > higestF)
                    {
                        higestF = projF;
                    }
                    if (projS < lowestS)
                    {
                        lowestS = projS;
                        lowestId = vertI;
                    }
                }

                float depth = higestF - lowestS;
                if (depth < 0)
                {
                    colisionFounded = false;
                    break;
                }
                else if (depth < colisionDepth)
                {
                    colisionDepth = depth;
                    colisionNormal = currentAxis;
                    colisionPos = boxVertsS[lowestId];
                }
            }

            if (!colisionFounded)
            {
                return;
            }

            // Check of vert colision into second box
            std::array<ct::Vector3, 3> boxFaceNormalsS = {
                ct::normalize(boxVertsS[3] - boxVertsS[7]), // Normal along first local X
                ct::normalize(boxVertsS[5] - boxVertsS[7]), // Normal along first local Y
                ct::normalize(boxVertsS[6] - boxVertsS[7])  // Normal along first local Z
            };

            for (int axisI = 0; axisI < 3; axisI++)
            {
                ct::Vector3 currentAxis = boxFaceNormalsS[axisI];

                if (ct::dot(currentAxis, relativeVector) > 0)
                {
                    currentAxis = -currentAxis;
                }

                float higestS = -99999.0f;
                float lowestF = 999999.0f;
                int lowestId = -1;
                for (int vertI = 0; vertI < 8; vertI++)
                {
                    float projS = ct::dot(boxVertsS[vertI], currentAxis);
                    float projF = ct::dot(boxVertsF[vertI], currentAxis);

                    if (projS > higestS)
                    {
                        higestS = projS;
                    }
                    if (projF < lowestF)
                    {
                        lowestF = projF;
                        lowestId = vertI;
                    }
                }

                float depth = higestS - lowestF;
                if (depth < 0)
                {
                    colisionFounded = false;
                    break;
                }
                else if (depth < colisionDepth)
                {
                    colisionDepth = depth;
                    colisionNormal = currentAxis;
                    colisionPos = boxVertsF[lowestId];
                }
            }

            if (!colisionFounded)
            {
                return;
            }

            if (dot(relativeVector, colisionNormal) < 0)
            {
                colisionNormal = -colisionNormal;
            }

            ct::Vector3 rF = colisionPos - transF->position;
            ct::Vector3 rS = colisionPos - transS->position;

            ct::Vector3 rnF = ct::cross(rF, colisionNormal);
            ct::Vector3 rnS = ct::cross(rS, colisionNormal);

            ct::Mat3x3 rotateF = ct::getRotationMatrix(transF->rotation.x, transF->rotation.y, transF->rotation.z);
            ct::Mat3x3 iF = ct::transpose(rotateF) * physF->inertiaTensor * rotateF;

            ct::Mat3x3 rotateS = ct::getRotationMatrix(transS->rotation.x, transS->rotation.y, transS->rotation.z);
            ct::Mat3x3 iS = ct::transpose(rotateS) * physS->inertiaTensor * rotateS;

            float impulsMagnetude = std::abs((1.0f + (physF->bouncines + physS->bouncines)) *
                                             ct::dot(colisionNormal, physF->velocity + ct::cross(physF->angularSpeed, rF) - (physS->velocity + ct::cross(physS->angularSpeed, rS))) /
                                             (1.0f / physF->mass + 1.0f / physS->mass + ct::dot(colisionNormal, ct::cross(iF * rnF, rF)) + ct::dot(colisionNormal, ct::cross(iS * rnS, rS))));

            if (!physF->isStatic)
            {
                physF->velocity -= colisionNormal * impulsMagnetude / physF->mass;

                physF->angularSpeed -= iF * ct::cross(rF, colisionNormal * impulsMagnetude) / 6.282f;
            }
            else {
                transS->position += colisionNormal * colisionDepth;
            }

            if (!physS->isStatic)
            {
                physS->velocity += colisionNormal * impulsMagnetude / physS->mass;

                physS->angularSpeed += iS * ct::cross(rS, colisionNormal * impulsMagnetude) / 6.282f;
            }
            else {
                transF->position -= colisionNormal * colisionDepth;
            }
        }

    } // namespace <anonymous>

    void execute()
    {
        std::vector<int> simulatingEntityIds;
        for (int i = 0; i < ECS::getEntityCount(); i++)
        {
            Entity *entity = ECS::getEntity(i);
            if (isEntityCompatable(entity->componentMask))
            {
                simulatingEntityIds.push_back(i);

                Transformation *trans = entity->getComponent<Transformation>();
                PhysicsData *phys = entity->getComponent<PhysicsData>();

                if (!phys->isStatic)
                {

                    phys->velocity += phys->aceleration * Window::lastFrameTimeDuration / 1000.0f;
                    phys->velocity *= 1.0f - 0.50f * Window::lastFrameTimeDuration / 1000.0f;
                    trans->position += phys->velocity * Window::lastFrameTimeDuration / 1000.0f;

                    phys->angularSpeed += phys->angularAceleration * Window::lastFrameTimeDuration / 1000.0f;
                    phys->angularSpeed *= 1.0f - 0.50f * Window::lastFrameTimeDuration / 1000.0f;
                    trans->rotation += phys->angularSpeed * Window::lastFrameTimeDuration / 1000.0f;
                }
            }
        }

        for (int f = 0; f < simulatingEntityIds.size(); f++)
        {
            Colider *coliderF = ECS::getEntity(simulatingEntityIds[f])->getComponent<Colider>();

            for (int s = f + 1; s < simulatingEntityIds.size(); s++)
            {
                Colider *coliderS = ECS::getEntity(simulatingEntityIds[s])->getComponent<Colider>();

                // Make sure that first object have more simple colider type
                bool fliped = coliderF->type > coliderS->type;

                if (coliderF->type == ColiderType::Sphere && coliderS->type == ColiderType::Sphere)
                {
                    circleToCircleColision(fliped ? simulatingEntityIds[s] : simulatingEntityIds[f], fliped ? simulatingEntityIds[f] : simulatingEntityIds[s]);
                }
                else if (coliderF->type == ColiderType::Sphere && coliderS->type == ColiderType::Box)
                {
                    circleToBoxColision(fliped ? simulatingEntityIds[s] : simulatingEntityIds[f], fliped ? simulatingEntityIds[f] : simulatingEntityIds[s]);
                }
                else if (coliderF->type == ColiderType::Box && coliderS->type == ColiderType::Box)
                {
                    boxToBoxColision(fliped ? simulatingEntityIds[s] : simulatingEntityIds[f], fliped ? simulatingEntityIds[f] : simulatingEntityIds[s]);
                }
            }
        }

        simulatingEntityIds.clear();
    }

}