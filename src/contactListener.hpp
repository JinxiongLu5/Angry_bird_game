#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include <box2d/box2d.h>
#include <set>

/**
 * \class ContactListener
 * \brief Class for listening to physics collisions in the game.
 *
 * ContactListener is a subclass of b2ContactListener and is used to detect collisions
 * between physics bodies in the game world. It overrides the PostSolve method to determine 
 * the outcome of collisions, such as marking bodies for destruction based on the collision intensity.
 */
class ContactListener : public b2ContactListener {
public:
    std::set<b2Body*> bodiesToDestroy; /*!< Set of bodies that are marked for destruction after a collision. */
    
    /**
     * \brief Called after the collision solver.
     * \param contact Pointer to the contact information.
     * \param impulse Pointer to the contact impulse, which gives an indication of the collision intensity.
     * 
     * This method overrides the PostSolve method in b2ContactListener to check the intensity of collisions.
     * Bodies involved in collisions with an impulse above a certain threshold are marked for destruction.
     */
    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override {
        float threshold = 2.0f; 

        // Check the impulse on contact
        if (impulse->normalImpulses[0] > threshold) {
            // If the impulse exceeds the threshold, mark the bodies for destruction
            bodiesToDestroy.insert(contact->GetFixtureA()->GetBody());
            bodiesToDestroy.insert(contact->GetFixtureB()->GetBody());
        }
    }
};

#endif // CONTACTLISTENER_H
