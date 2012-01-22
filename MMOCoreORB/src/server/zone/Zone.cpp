/*
 *	server/zone/Zone.cpp generated by engine3 IDL compiler 0.60
 */

#include "Zone.h"

#include "server/zone/ZoneProcessServer.h"

#include "server/zone/managers/structure/StructureManager.h"

#include "server/zone/objects/area/ActiveArea.h"

#include "server/zone/managers/planet/PlanetManager.h"

#include "server/zone/managers/city/CityManager.h"

#include "server/zone/managers/creature/CreatureManager.h"

#include "server/zone/managers/objectcontroller/ObjectController.h"

#include "server/zone/objects/building/cloning/CloningBuildingObject.h"

#include "server/zone/objects/creature/CreatureObject.h"

/*
 *	ZoneStub
 */

enum {RPC_INITIALIZETRANSIENTMEMBERS__ = 6,RPC_FINALIZE__,RPC_GETNEARESTCLONINGBUILDING__CREATUREOBJECT_,RPC_GETNEARESTPLANETARYOBJECT__SCENEOBJECT_STRING_,RPC_INITIALIZEPRIVATEDATA__,RPC_CREATECONTAINERCOMPONENT__,RPC_UPDATEACTIVEAREAS__SCENEOBJECT_,RPC_STARTMANAGERS__,RPC_STOPMANAGERS__,RPC_GETHEIGHT__FLOAT_FLOAT_,RPC_ADDSCENEOBJECT__SCENEOBJECT_,RPC_SENDMAPLOCATIONSTO__SCENEOBJECT_,RPC_DROPSCENEOBJECT__SCENEOBJECT_,RPC_GETPLANETMANAGER__,RPC_GETSTRUCTUREMANAGER__,RPC_GETCITYMANAGER__,RPC_GETZONESERVER__,RPC_GETCREATUREMANAGER__,RPC_GETGALACTICTIME__,RPC_HASMANAGERSSTARTED__,RPC_GETMINX__,RPC_GETMAXX__,RPC_GETMINY__,RPC_GETMAXY__,RPC_GETBOUNDINGRADIUS__,RPC_REGISTEROBJECTWITHPLANETARYMAP__SCENEOBJECT_,RPC_UNREGISTEROBJECTWITHPLANETARYMAP__SCENEOBJECT_,RPC_GETZONENAME__,RPC_GETZONECRC__};

Zone::Zone(ZoneProcessServer* processor, const String& zoneName) : SceneObject(DummyConstructorParameter::instance()) {
	ZoneImplementation* _implementation = new ZoneImplementation(processor, zoneName);
	_impl = _implementation;
	_impl->_setStub(this);
}

Zone::Zone(DummyConstructorParameter* param) : SceneObject(param) {
}

Zone::~Zone() {
}



void Zone::initializeTransientMembers() {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_INITIALIZETRANSIENTMEMBERS__);

		method.executeWithVoidReturn();
	} else
		_implementation->initializeTransientMembers();
}

CloningBuildingObject* Zone::getNearestCloningBuilding(CreatureObject* creature) {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_GETNEARESTCLONINGBUILDING__CREATUREOBJECT_);
		method.addObjectParameter(creature);

		return static_cast<CloningBuildingObject*>(method.executeWithObjectReturn());
	} else
		return _implementation->getNearestCloningBuilding(creature);
}

SceneObject* Zone::getNearestPlanetaryObject(SceneObject* object, const String& mapObjectLocationType) {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_GETNEARESTPLANETARYOBJECT__SCENEOBJECT_STRING_);
		method.addObjectParameter(object);
		method.addAsciiParameter(mapObjectLocationType);

		return static_cast<SceneObject*>(method.executeWithObjectReturn());
	} else
		return _implementation->getNearestPlanetaryObject(object, mapObjectLocationType);
}

void Zone::initializePrivateData() {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_INITIALIZEPRIVATEDATA__);

		method.executeWithVoidReturn();
	} else
		_implementation->initializePrivateData();
}

QuadTree* Zone::getRegionTree() {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		throw ObjectNotLocalException(this);

	} else
		return _implementation->getRegionTree();
}

int Zone::getInRangeObjects(float x, float y, float range, SortedVector<ManagedReference<QuadTreeEntry* > >* objects, bool readLockZone) {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		throw ObjectNotLocalException(this);

	} else
		return _implementation->getInRangeObjects(x, y, range, objects, readLockZone);
}

void Zone::createContainerComponent() {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_CREATECONTAINERCOMPONENT__);

		method.executeWithVoidReturn();
	} else
		_implementation->createContainerComponent();
}

int Zone::getInRangeActiveAreas(float x, float y, SortedVector<ManagedReference<ActiveArea* > >* objects, bool readLockZone) {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		throw ObjectNotLocalException(this);

	} else
		return _implementation->getInRangeActiveAreas(x, y, objects, readLockZone);
}

SortedVector<ManagedReference<SceneObject* > > Zone::getPlanetaryObjectList(const String& mapObjectLocationType) {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		throw ObjectNotLocalException(this);

	} else
		return _implementation->getPlanetaryObjectList(mapObjectLocationType);
}

void Zone::insert(QuadTreeEntry* entry) {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		throw ObjectNotLocalException(this);

	} else
		_implementation->insert(entry);
}

void Zone::remove(QuadTreeEntry* entry) {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		throw ObjectNotLocalException(this);

	} else
		_implementation->remove(entry);
}

void Zone::update(QuadTreeEntry* entry) {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		throw ObjectNotLocalException(this);

	} else
		_implementation->update(entry);
}

void Zone::inRange(QuadTreeEntry* entry, float range) {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		throw ObjectNotLocalException(this);

	} else
		_implementation->inRange(entry, range);
}

void Zone::updateActiveAreas(SceneObject* object) {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_UPDATEACTIVEAREAS__SCENEOBJECT_);
		method.addObjectParameter(object);

		method.executeWithVoidReturn();
	} else
		_implementation->updateActiveAreas(object);
}

void Zone::startManagers() {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_STARTMANAGERS__);

		method.executeWithVoidReturn();
	} else
		_implementation->startManagers();
}

void Zone::stopManagers() {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_STOPMANAGERS__);

		method.executeWithVoidReturn();
	} else
		_implementation->stopManagers();
}

float Zone::getHeight(float x, float y) {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_GETHEIGHT__FLOAT_FLOAT_);
		method.addFloatParameter(x);
		method.addFloatParameter(y);

		return method.executeWithFloatReturn();
	} else
		return _implementation->getHeight(x, y);
}

void Zone::addSceneObject(SceneObject* object) {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_ADDSCENEOBJECT__SCENEOBJECT_);
		method.addObjectParameter(object);

		method.executeWithVoidReturn();
	} else
		_implementation->addSceneObject(object);
}

void Zone::sendMapLocationsTo(SceneObject* player) {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_SENDMAPLOCATIONSTO__SCENEOBJECT_);
		method.addObjectParameter(player);

		method.executeWithVoidReturn();
	} else
		_implementation->sendMapLocationsTo(player);
}

void Zone::dropSceneObject(SceneObject* object) {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_DROPSCENEOBJECT__SCENEOBJECT_);
		method.addObjectParameter(object);

		method.executeWithVoidReturn();
	} else
		_implementation->dropSceneObject(object);
}

PlanetManager* Zone::getPlanetManager() {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_GETPLANETMANAGER__);

		return static_cast<PlanetManager*>(method.executeWithObjectReturn());
	} else
		return _implementation->getPlanetManager();
}

StructureManager* Zone::getStructureManager() {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_GETSTRUCTUREMANAGER__);

		return static_cast<StructureManager*>(method.executeWithObjectReturn());
	} else
		return _implementation->getStructureManager();
}

CityManager* Zone::getCityManager() {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_GETCITYMANAGER__);

		return static_cast<CityManager*>(method.executeWithObjectReturn());
	} else
		return _implementation->getCityManager();
}

ZoneServer* Zone::getZoneServer() {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_GETZONESERVER__);

		return static_cast<ZoneServer*>(method.executeWithObjectReturn());
	} else
		return _implementation->getZoneServer();
}

CreatureManager* Zone::getCreatureManager() {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_GETCREATUREMANAGER__);

		return static_cast<CreatureManager*>(method.executeWithObjectReturn());
	} else
		return _implementation->getCreatureManager();
}

unsigned long long Zone::getGalacticTime() {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_GETGALACTICTIME__);

		return method.executeWithUnsignedLongReturn();
	} else
		return _implementation->getGalacticTime();
}

bool Zone::hasManagersStarted() {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_HASMANAGERSSTARTED__);

		return method.executeWithBooleanReturn();
	} else
		return _implementation->hasManagersStarted();
}

float Zone::getMinX() {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_GETMINX__);

		return method.executeWithFloatReturn();
	} else
		return _implementation->getMinX();
}

float Zone::getMaxX() {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_GETMAXX__);

		return method.executeWithFloatReturn();
	} else
		return _implementation->getMaxX();
}

float Zone::getMinY() {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_GETMINY__);

		return method.executeWithFloatReturn();
	} else
		return _implementation->getMinY();
}

float Zone::getMaxY() {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_GETMAXY__);

		return method.executeWithFloatReturn();
	} else
		return _implementation->getMaxY();
}

float Zone::getBoundingRadius() {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_GETBOUNDINGRADIUS__);

		return method.executeWithFloatReturn();
	} else
		return _implementation->getBoundingRadius();
}

void Zone::registerObjectWithPlanetaryMap(SceneObject* object) {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_REGISTEROBJECTWITHPLANETARYMAP__SCENEOBJECT_);
		method.addObjectParameter(object);

		method.executeWithVoidReturn();
	} else
		_implementation->registerObjectWithPlanetaryMap(object);
}

void Zone::unregisterObjectWithPlanetaryMap(SceneObject* object) {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_UNREGISTEROBJECTWITHPLANETARYMAP__SCENEOBJECT_);
		method.addObjectParameter(object);

		method.executeWithVoidReturn();
	} else
		_implementation->unregisterObjectWithPlanetaryMap(object);
}

String Zone::getZoneName() {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_GETZONENAME__);

		method.executeWithAsciiReturn(_return_getZoneName);
		return _return_getZoneName;
	} else
		return _implementation->getZoneName();
}

unsigned int Zone::getZoneCRC() {
	ZoneImplementation* _implementation = static_cast<ZoneImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_GETZONECRC__);

		return method.executeWithUnsignedIntReturn();
	} else
		return _implementation->getZoneCRC();
}

DistributedObjectServant* Zone::_getImplementation() {

	_updated = true;
	return _impl;
}

void Zone::_setImplementation(DistributedObjectServant* servant) {
	_impl = servant;
}

/*
 *	ZoneImplementation
 */

ZoneImplementation::ZoneImplementation(DummyConstructorParameter* param) : SceneObjectImplementation(param) {
	_initializeImplementation();
}


ZoneImplementation::~ZoneImplementation() {
	ZoneImplementation::finalize();
}


void ZoneImplementation::_initializeImplementation() {
	_setClassHelper(ZoneHelper::instance());

	_this = NULL;

	_serializationHelperMethod();
}

void ZoneImplementation::_setStub(DistributedObjectStub* stub) {
	_this = static_cast<Zone*>(stub);
	SceneObjectImplementation::_setStub(stub);
}

DistributedObjectStub* ZoneImplementation::_getStub() {
	return _this;
}

ZoneImplementation::operator const Zone*() {
	return _this;
}

void ZoneImplementation::lock(bool doLock) {
	_this->lock(doLock);
}

void ZoneImplementation::lock(ManagedObject* obj) {
	_this->lock(obj);
}

void ZoneImplementation::rlock(bool doLock) {
	_this->rlock(doLock);
}

void ZoneImplementation::wlock(bool doLock) {
	_this->wlock(doLock);
}

void ZoneImplementation::wlock(ManagedObject* obj) {
	_this->wlock(obj);
}

void ZoneImplementation::unlock(bool doLock) {
	_this->unlock(doLock);
}

void ZoneImplementation::runlock(bool doLock) {
	_this->runlock(doLock);
}

void ZoneImplementation::_serializationHelperMethod() {
	SceneObjectImplementation::_serializationHelperMethod();

	_setClassName("Zone");

}

void ZoneImplementation::readObject(ObjectInputStream* stream) {
	uint16 _varCount = stream->readShort();
	for (int i = 0; i < _varCount; ++i) {
		String _name;
		_name.parseFromBinaryStream(stream);

		uint16 _varSize = stream->readShort();

		int _currentOffset = stream->getOffset();

		if(ZoneImplementation::readObjectMember(stream, _name)) {
		}

		stream->setOffset(_currentOffset + _varSize);
	}

	initializeTransientMembers();
}

bool ZoneImplementation::readObjectMember(ObjectInputStream* stream, const String& _name) {
	if (SceneObjectImplementation::readObjectMember(stream, _name))
		return true;

	if (_name == "zoneName") {
		TypeInfo<String >::parseFromBinaryStream(&zoneName, stream);
		return true;
	}

	if (_name == "zoneCRC") {
		TypeInfo<unsigned int >::parseFromBinaryStream(&zoneCRC, stream);
		return true;
	}

	if (_name == "regionTree") {
		TypeInfo<QuadTreeReference >::parseFromBinaryStream(&regionTree, stream);
		return true;
	}

	if (_name == "quadTree") {
		TypeInfo<QuadTreeReference >::parseFromBinaryStream(&quadTree, stream);
		return true;
	}


	return false;
}

void ZoneImplementation::writeObject(ObjectOutputStream* stream) {
	int _currentOffset = stream->getOffset();
	stream->writeShort(0);
	int _varCount = ZoneImplementation::writeObjectMembers(stream);
	stream->writeShort(_currentOffset, _varCount);
}

int ZoneImplementation::writeObjectMembers(ObjectOutputStream* stream) {
	String _name;
	int _offset;
	uint16 _totalSize;
	_name = "zoneName";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeShort(0);
	TypeInfo<String >::toBinaryStream(&zoneName, stream);
	_totalSize = (uint16) (stream->getOffset() - (_offset + 2));
	stream->writeShort(_offset, _totalSize);

	_name = "zoneCRC";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeShort(0);
	TypeInfo<unsigned int >::toBinaryStream(&zoneCRC, stream);
	_totalSize = (uint16) (stream->getOffset() - (_offset + 2));
	stream->writeShort(_offset, _totalSize);

	_name = "regionTree";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeShort(0);
	TypeInfo<QuadTreeReference >::toBinaryStream(&regionTree, stream);
	_totalSize = (uint16) (stream->getOffset() - (_offset + 2));
	stream->writeShort(_offset, _totalSize);

	_name = "quadTree";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeShort(0);
	TypeInfo<QuadTreeReference >::toBinaryStream(&quadTree, stream);
	_totalSize = (uint16) (stream->getOffset() - (_offset + 2));
	stream->writeShort(_offset, _totalSize);


	return 4 + SceneObjectImplementation::writeObjectMembers(stream);
}

QuadTree* ZoneImplementation::getRegionTree() {
	// server/zone/Zone.idl():  		return regionTree.get();
	return (&regionTree)->get();
}

PlanetManager* ZoneImplementation::getPlanetManager() {
	// server/zone/Zone.idl():  		return planetManager;
	return planetManager;
}

StructureManager* ZoneImplementation::getStructureManager() {
	// server/zone/Zone.idl():  		return structureManager;
	return structureManager;
}

CityManager* ZoneImplementation::getCityManager() {
	// server/zone/Zone.idl():  		return cityManager;
	return cityManager;
}

ZoneServer* ZoneImplementation::getZoneServer() {
	// server/zone/Zone.idl():  		return server;
	return server;
}

CreatureManager* ZoneImplementation::getCreatureManager() {
	// server/zone/Zone.idl():  		return creatureManager;
	return creatureManager;
}

unsigned long long ZoneImplementation::getGalacticTime() {
	// server/zone/Zone.idl():  		return galacticTime.miliDifference() / 1000;
	return (&galacticTime)->miliDifference() / 1000;
}

bool ZoneImplementation::hasManagersStarted() {
	// server/zone/Zone.idl():  		return managersStarted;
	return managersStarted;
}

String ZoneImplementation::getZoneName() {
	// server/zone/Zone.idl():  		return zoneName;
	return zoneName;
}

unsigned int ZoneImplementation::getZoneCRC() {
	// server/zone/Zone.idl():  		return zoneCRC;
	return zoneCRC;
}

/*
 *	ZoneAdapter
 */

ZoneAdapter::ZoneAdapter(Zone* obj) : SceneObjectAdapter(obj) {
}

Packet* ZoneAdapter::invokeMethod(uint32 methid, DistributedMethod* inv) {
	Packet* resp = new MethodReturnMessage(0);

	switch (methid) {
	case RPC_INITIALIZETRANSIENTMEMBERS__:
		initializeTransientMembers();
		break;
	case RPC_FINALIZE__:
		finalize();
		break;
	case RPC_GETNEARESTCLONINGBUILDING__CREATUREOBJECT_:
		resp->insertLong(getNearestCloningBuilding(static_cast<CreatureObject*>(inv->getObjectParameter()))->_getObjectID());
		break;
	case RPC_GETNEARESTPLANETARYOBJECT__SCENEOBJECT_STRING_:
		resp->insertLong(getNearestPlanetaryObject(static_cast<SceneObject*>(inv->getObjectParameter()), inv->getAsciiParameter(_param1_getNearestPlanetaryObject__SceneObject_String_))->_getObjectID());
		break;
	case RPC_INITIALIZEPRIVATEDATA__:
		initializePrivateData();
		break;
	case RPC_CREATECONTAINERCOMPONENT__:
		createContainerComponent();
		break;
	case RPC_UPDATEACTIVEAREAS__SCENEOBJECT_:
		updateActiveAreas(static_cast<SceneObject*>(inv->getObjectParameter()));
		break;
	case RPC_STARTMANAGERS__:
		startManagers();
		break;
	case RPC_STOPMANAGERS__:
		stopManagers();
		break;
	case RPC_GETHEIGHT__FLOAT_FLOAT_:
		resp->insertFloat(getHeight(inv->getFloatParameter(), inv->getFloatParameter()));
		break;
	case RPC_ADDSCENEOBJECT__SCENEOBJECT_:
		addSceneObject(static_cast<SceneObject*>(inv->getObjectParameter()));
		break;
	case RPC_SENDMAPLOCATIONSTO__SCENEOBJECT_:
		sendMapLocationsTo(static_cast<SceneObject*>(inv->getObjectParameter()));
		break;
	case RPC_DROPSCENEOBJECT__SCENEOBJECT_:
		dropSceneObject(static_cast<SceneObject*>(inv->getObjectParameter()));
		break;
	case RPC_GETPLANETMANAGER__:
		resp->insertLong(getPlanetManager()->_getObjectID());
		break;
	case RPC_GETSTRUCTUREMANAGER__:
		resp->insertLong(getStructureManager()->_getObjectID());
		break;
	case RPC_GETCITYMANAGER__:
		resp->insertLong(getCityManager()->_getObjectID());
		break;
	case RPC_GETZONESERVER__:
		resp->insertLong(getZoneServer()->_getObjectID());
		break;
	case RPC_GETCREATUREMANAGER__:
		resp->insertLong(getCreatureManager()->_getObjectID());
		break;
	case RPC_GETGALACTICTIME__:
		resp->insertLong(getGalacticTime());
		break;
	case RPC_HASMANAGERSSTARTED__:
		resp->insertBoolean(hasManagersStarted());
		break;
	case RPC_GETMINX__:
		resp->insertFloat(getMinX());
		break;
	case RPC_GETMAXX__:
		resp->insertFloat(getMaxX());
		break;
	case RPC_GETMINY__:
		resp->insertFloat(getMinY());
		break;
	case RPC_GETMAXY__:
		resp->insertFloat(getMaxY());
		break;
	case RPC_GETBOUNDINGRADIUS__:
		resp->insertFloat(getBoundingRadius());
		break;
	case RPC_REGISTEROBJECTWITHPLANETARYMAP__SCENEOBJECT_:
		registerObjectWithPlanetaryMap(static_cast<SceneObject*>(inv->getObjectParameter()));
		break;
	case RPC_UNREGISTEROBJECTWITHPLANETARYMAP__SCENEOBJECT_:
		unregisterObjectWithPlanetaryMap(static_cast<SceneObject*>(inv->getObjectParameter()));
		break;
	case RPC_GETZONENAME__:
		resp->insertAscii(getZoneName());
		break;
	case RPC_GETZONECRC__:
		resp->insertInt(getZoneCRC());
		break;
	default:
		return NULL;
	}

	return resp;
}

void ZoneAdapter::initializeTransientMembers() {
	(static_cast<Zone*>(stub))->initializeTransientMembers();
}

void ZoneAdapter::finalize() {
	(static_cast<Zone*>(stub))->finalize();
}

CloningBuildingObject* ZoneAdapter::getNearestCloningBuilding(CreatureObject* creature) {
	return (static_cast<Zone*>(stub))->getNearestCloningBuilding(creature);
}

SceneObject* ZoneAdapter::getNearestPlanetaryObject(SceneObject* object, const String& mapObjectLocationType) {
	return (static_cast<Zone*>(stub))->getNearestPlanetaryObject(object, mapObjectLocationType);
}

void ZoneAdapter::initializePrivateData() {
	(static_cast<Zone*>(stub))->initializePrivateData();
}

void ZoneAdapter::createContainerComponent() {
	(static_cast<Zone*>(stub))->createContainerComponent();
}

void ZoneAdapter::updateActiveAreas(SceneObject* object) {
	(static_cast<Zone*>(stub))->updateActiveAreas(object);
}

void ZoneAdapter::startManagers() {
	(static_cast<Zone*>(stub))->startManagers();
}

void ZoneAdapter::stopManagers() {
	(static_cast<Zone*>(stub))->stopManagers();
}

float ZoneAdapter::getHeight(float x, float y) {
	return (static_cast<Zone*>(stub))->getHeight(x, y);
}

void ZoneAdapter::addSceneObject(SceneObject* object) {
	(static_cast<Zone*>(stub))->addSceneObject(object);
}

void ZoneAdapter::sendMapLocationsTo(SceneObject* player) {
	(static_cast<Zone*>(stub))->sendMapLocationsTo(player);
}

void ZoneAdapter::dropSceneObject(SceneObject* object) {
	(static_cast<Zone*>(stub))->dropSceneObject(object);
}

PlanetManager* ZoneAdapter::getPlanetManager() {
	return (static_cast<Zone*>(stub))->getPlanetManager();
}

StructureManager* ZoneAdapter::getStructureManager() {
	return (static_cast<Zone*>(stub))->getStructureManager();
}

CityManager* ZoneAdapter::getCityManager() {
	return (static_cast<Zone*>(stub))->getCityManager();
}

ZoneServer* ZoneAdapter::getZoneServer() {
	return (static_cast<Zone*>(stub))->getZoneServer();
}

CreatureManager* ZoneAdapter::getCreatureManager() {
	return (static_cast<Zone*>(stub))->getCreatureManager();
}

unsigned long long ZoneAdapter::getGalacticTime() {
	return (static_cast<Zone*>(stub))->getGalacticTime();
}

bool ZoneAdapter::hasManagersStarted() {
	return (static_cast<Zone*>(stub))->hasManagersStarted();
}

float ZoneAdapter::getMinX() {
	return (static_cast<Zone*>(stub))->getMinX();
}

float ZoneAdapter::getMaxX() {
	return (static_cast<Zone*>(stub))->getMaxX();
}

float ZoneAdapter::getMinY() {
	return (static_cast<Zone*>(stub))->getMinY();
}

float ZoneAdapter::getMaxY() {
	return (static_cast<Zone*>(stub))->getMaxY();
}

float ZoneAdapter::getBoundingRadius() {
	return (static_cast<Zone*>(stub))->getBoundingRadius();
}

void ZoneAdapter::registerObjectWithPlanetaryMap(SceneObject* object) {
	(static_cast<Zone*>(stub))->registerObjectWithPlanetaryMap(object);
}

void ZoneAdapter::unregisterObjectWithPlanetaryMap(SceneObject* object) {
	(static_cast<Zone*>(stub))->unregisterObjectWithPlanetaryMap(object);
}

String ZoneAdapter::getZoneName() {
	return (static_cast<Zone*>(stub))->getZoneName();
}

unsigned int ZoneAdapter::getZoneCRC() {
	return (static_cast<Zone*>(stub))->getZoneCRC();
}

/*
 *	ZoneHelper
 */

ZoneHelper* ZoneHelper::staticInitializer = ZoneHelper::instance();

ZoneHelper::ZoneHelper() {
	className = "Zone";

	Core::getObjectBroker()->registerClass(className, this);
}

void ZoneHelper::finalizeHelper() {
	ZoneHelper::finalize();
}

DistributedObject* ZoneHelper::instantiateObject() {
	return new Zone(DummyConstructorParameter::instance());
}

DistributedObjectServant* ZoneHelper::instantiateServant() {
	return new ZoneImplementation(DummyConstructorParameter::instance());
}

DistributedObjectAdapter* ZoneHelper::createAdapter(DistributedObjectStub* obj) {
	DistributedObjectAdapter* adapter = new ZoneAdapter(static_cast<Zone*>(obj));

	obj->_setClassName(className);
	obj->_setClassHelper(this);

	adapter->setStub(obj);

	return adapter;
}

