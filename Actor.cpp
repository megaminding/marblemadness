//#include "Actor.h"
//#include "StudentWorld.h"  // Include StudentWorld to access its functionality
//using namespace std;
//
//// Actor
//
//Actor::Actor(int imageID, double startX, double startY, int dir, double size)
//    : GraphObject(imageID, startX, startY, dir, size), m_removeOffScreen(false), m_active(true) {}
//
//bool Actor::isObstacle() {
//    return false;
//}
//
//bool Actor::removeOffScreen() {
//    return m_removeOffScreen;
//}
//
//Actor::~Actor() {
//    cout << "DELETED ACTOR";
//}
//
//void Actor::doSomething() {
//    cout << "dosomething called";
//}
//
//bool Actor::isVisible() {
//    if (!m_active) {
//        setVisible(false);
//        return false;
//    }
//    return true;
//}
//
//void Actor::makeVisible() {
//    setVisible(true);
//}
//
//// hasHealth
//
//hasHealth::hasHealth(int imageID, double startX, double startY, int dir, double size)
//    : Actor(imageID, startX, startY, dir, size), hit_points(20) {}
//
//bool hasHealth::canPassThru() {
//    return false;
//}
//
//int hasHealth::health() {
//    return hit_points;
//}
//
//// Avatar
//
//Avatar::Avatar(int imageID, double startX, double startY, int dir, double size, StudentWorld* world)
//    : hasHealth(imageID, startX, startY, dir, size), m_ammo(20), m_world(world) {}
//
//bool Avatar::isObstacle() {
//    return false;
//}
//
//bool Avatar::hasCollectedAllOfTheCrystalsOnTheLevel() {
//    return true;
//}
//
//StudentWorld* Avatar::getWorld() const {
//    return m_world;
//}
//
//void Avatar::setWorld(StudentWorld* world) {
//    cout << "WORLD!" << world;
//    m_world = world;
//}
//
//void Avatar::doSomething() {
//    int ch;
//    if (getWorld()->getKey(ch)) {
//        setWorld(m_world);
//    }
//}
//
//bool Avatar::checkIfCompletedCurrentLevel() {
//    // Implementation for checking completion of the current level
//    return false;
//}
//
//int Avatar::ammo() {
//    return m_ammo;
//}
//
//// ... Implement other class member functions similarly
