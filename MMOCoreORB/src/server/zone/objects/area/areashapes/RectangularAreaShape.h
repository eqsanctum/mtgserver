/*
 *	server/zone/objects/area/areashapes/RectangularAreaShape.h generated by engine3 IDL compiler 0.60
 */

#ifndef RECTANGULARAREASHAPE_H_
#define RECTANGULARAREASHAPE_H_

#include "engine/core/Core.h"

#include "engine/core/ManagedReference.h"

#include "engine/core/ManagedWeakReference.h"

namespace server {
namespace zone {
namespace objects {
namespace area {
namespace areashapes {

class CircularAreaShape;

} // namespace areashapes
} // namespace area
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::area::areashapes;

#include "server/zone/objects/area/areashapes/AreaShape.h"

namespace server {
namespace zone {
namespace objects {
namespace area {
namespace areashapes {

class RectangularAreaShape : public AreaShape {
public:
	RectangularAreaShape();

	void setDimensions(float h, float w);

	float getHeight();

	float getWidth();

	bool containsPoint(float x, float y);

	bool containsPoint(const Vector3& point);

	Vector3 getRandomPosition();

	Vector3 getRandomPosition(const Vector3& origin, float minDistance, float maxDistance);

	bool isCircularAreaShape();

	bool isRectangularAreaShape();

	bool intersectsWith(AreaShape* areaShape);

	DistributedObjectServant* _getImplementation();

	void _setImplementation(DistributedObjectServant* servant);

protected:
	RectangularAreaShape(DummyConstructorParameter* param);

	virtual ~RectangularAreaShape();

	friend class RectangularAreaShapeHelper;
};

} // namespace areashapes
} // namespace area
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::area::areashapes;

namespace server {
namespace zone {
namespace objects {
namespace area {
namespace areashapes {

class RectangularAreaShapeImplementation : public AreaShapeImplementation {
protected:
	float height;

	float width;

public:
	RectangularAreaShapeImplementation();

	RectangularAreaShapeImplementation(DummyConstructorParameter* param);

	void setDimensions(float h, float w);

	virtual float getHeight();

	virtual float getWidth();

	virtual bool containsPoint(float x, float y);

	virtual bool containsPoint(const Vector3& point);

	virtual Vector3 getRandomPosition();

	virtual Vector3 getRandomPosition(const Vector3& origin, float minDistance, float maxDistance);

	virtual bool isCircularAreaShape();

	virtual bool isRectangularAreaShape();

	virtual bool intersectsWith(AreaShape* areaShape);

private:
	Vector3 getClosestPoint(const Vector3& position);

	Vector3 getClosestPointOnLine(const Vector3& coordinate1, const Vector3& coordinate2, const Vector3& position);

public:
	WeakReference<RectangularAreaShape*> _this;

	operator const RectangularAreaShape*();

	DistributedObjectStub* _getStub();
	virtual void readObject(ObjectInputStream* stream);
	virtual void writeObject(ObjectOutputStream* stream);
protected:
	virtual ~RectangularAreaShapeImplementation();

	void finalize();

	void _initializeImplementation();

	void _setStub(DistributedObjectStub* stub);

	void lock(bool doLock = true);

	void lock(ManagedObject* obj);

	void rlock(bool doLock = true);

	void wlock(bool doLock = true);

	void wlock(ManagedObject* obj);

	void unlock(bool doLock = true);

	void runlock(bool doLock = true);

	void _serializationHelperMethod();
	bool readObjectMember(ObjectInputStream* stream, const String& name);
	int writeObjectMembers(ObjectOutputStream* stream);

	friend class RectangularAreaShape;
};

class RectangularAreaShapeAdapter : public AreaShapeAdapter {
public:
	RectangularAreaShapeAdapter(RectangularAreaShape* impl);

	void invokeMethod(sys::uint32 methid, DistributedMethod* method);

	void setDimensions(float h, float w);

	float getHeight();

	float getWidth();

	bool containsPoint(float x, float y);

	bool isCircularAreaShape();

	bool isRectangularAreaShape();

	bool intersectsWith(AreaShape* areaShape);

};

class RectangularAreaShapeHelper : public DistributedObjectClassHelper, public Singleton<RectangularAreaShapeHelper> {
	static RectangularAreaShapeHelper* staticInitializer;

public:
	RectangularAreaShapeHelper();

	void finalizeHelper();

	DistributedObject* instantiateObject();

	DistributedObjectServant* instantiateServant();

	DistributedObjectAdapter* createAdapter(DistributedObjectStub* obj);

	friend class Singleton<RectangularAreaShapeHelper>;
};

} // namespace areashapes
} // namespace area
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::area::areashapes;

#endif /*RECTANGULARAREASHAPE_H_*/
