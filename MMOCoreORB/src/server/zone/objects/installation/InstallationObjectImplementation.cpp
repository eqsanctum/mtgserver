/*
 * InstallationObjectImplementation.cpp
 *
 *  Created on: Jun 4, 2010
 *      Author: crush
 */

#include "InstallationObject.h"

#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/structure/StructureManager.h"

#include "server/zone/packets/installation/InstallationObjectMessage3.h"
#include "server/zone/packets/installation/InstallationObjectDeltaMessage3.h"
#include "server/zone/packets/installation/InstallationObjectDeltaMessage7.h"
#include "server/zone/packets/installation/InstallationObjectMessage6.h"

#include "server/zone/packets/chat/ChatSystemMessage.h"

#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/objects/player/sui/transferbox/SuiTransferBox.h"

#include "server/zone/objects/resource/ResourceSpawn.h"
#include "server/zone/objects/resource/ResourceContainer.h"
#include "server/zone/Zone.h"

#include "server/zone/templates/tangible/SharedInstallationObjectTemplate.h"

#include "SyncrhonizedUiListenInstallationTask.h"

void InstallationObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	StructureObjectImplementation::loadTemplateData(templateData);

	SharedInstallationObjectTemplate* inso = dynamic_cast<SharedInstallationObjectTemplate*>(templateData);

	installationType = inso->getInstallationType();
}

void InstallationObjectImplementation::sendBaselinesTo(SceneObject* player) {
	//send buios here
	info("sending installation baselines");

	BaseMessage* buio3 = new InstallationObjectMessage3(_this);
	player->sendMessage(buio3);

	BaseMessage* buio6 = new InstallationObjectMessage6(_this);
	player->sendMessage(buio6);
}

void InstallationObjectImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	//TangibleObjectImplementation::fillAttributeList(alm, object);

	//Add the owner name to the examine window.
	ManagedReference<SceneObject*> obj = object->getZoneServer()->getObject(ownerObjectID);

	if (obj != NULL && obj->isCreatureObject()) {
		CreatureObject* owner = cast<CreatureObject*>( obj.get());

		String fullName = owner->getCustomObjectName().toString();

		if (fullName.isEmpty())
			owner->getObjectName()->getFullPath(fullName);

		alm->insertAttribute("owner", fullName);
	}

}

void InstallationObjectImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (!isOnAdminList(player->getFirstName()))
		return;

	menuResponse->addRadialMenuItem(118, 3, "@player_structure:management");
	menuResponse->addRadialMenuItemToRadialID(118, 128, 3, "@player_structure:permission_destroy"); //Destroy Structure
	menuResponse->addRadialMenuItemToRadialID(118, 124, 3, "@player_structure:management_status"); //Status
	menuResponse->addRadialMenuItemToRadialID(118, 129, 3, "@player_structure:management_pay"); //Pay Maintenance
	menuResponse->addRadialMenuItemToRadialID(118, 50, 3, "@base_player:set_name"); //Set Name
	if (!isGeneratorObject()) {
		menuResponse->addRadialMenuItemToRadialID(118, 51, 3, "@player_structure:management_power"); //Deposit Power
	}

	menuResponse->addRadialMenuItem(117, 3, "@player_structure:permissions"); //Structure Permissions
	menuResponse->addRadialMenuItemToRadialID(117, 121, 3, "@player_structure:permission_admin"); //Administrator List
	menuResponse->addRadialMenuItemToRadialID(117, 123, 3, "@player_structure:permission_hopper"); //Hopper List
}

int InstallationObjectImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (getZone() == NULL)
		return 1;

	if (!isOnAdminList(player->getFirstName()))
		return 1;

	ManagedReference<StructureManager*> structureManager = getZone()->getStructureManager();

	if (structureManager == NULL)
		return 1;

	switch (selectedID) {
	case 124:
		player->executeObjectControllerAction(0x13F7E585, getObjectID(), ""); //structureStatus
		break;

	case 129:
		structureManager->promptManageMaintenance(player, _this);
		break;

	case 128:
		player->executeObjectControllerAction(0x18FC1726, getObjectID(), ""); //destroyStructure command
		break;

	case 50:
		structureManager->promptNameStructure(player, _this, NULL);
		break;

	case 51:
		//TODO: Move to structure manager.
		if (!isGeneratorObject()) {
			handleStructureAddEnergy(player);
		}
		break;

	case 121:
		sendPermissionListTo(player, "ADMIN");
		break;

	case 123:
		sendPermissionListTo(player, "HOPPER");
		break;

	default:
		break;
	}

	return 0;
}

void InstallationObjectImplementation::broadcastMessage(BasePacket* message, bool sendSelf) {
	if (getZone() == NULL)
		return;

	Locker zoneLocker(getZone());

	SortedVector<ManagedReference<QuadTreeEntry*> > closeSceneObjects;
	getZone()->getInRangeObjects(getPositionX(), getPositionY(), 512, &closeSceneObjects, false);

	for (int i = 0; i < closeSceneObjects.size(); ++i) {
		ManagedReference<SceneObject*> scno = cast<SceneObject*>( closeSceneObjects.get(i).get());

		if (!sendSelf && scno == _this)
			continue;

		if(!scno->isPlayerCreature())
			continue;

		CreatureObject* creo = cast<CreatureObject*>( scno.get());

		if(isOnAdminList(creo->getFirstName()))
			scno->sendMessage(message->clone());
	}

	delete message;
}

void InstallationObjectImplementation::setOperating(bool value, bool notifyClient) {
	//updateInstallationWork();

	if (operating == value)
		return;

	if (value) {

		if (basePowerRate != 0 && surplusPower <= 0) {
			StringIdChatParameter stringId("player_structure", "power_deposit_incomplete");
			ChatSystemMessage* msg = new ChatSystemMessage(stringId);

			broadcastToOperators(msg);
			return;
		}

		if (getMaintenanceRate() != 0 && surplusMaintenance <= 0) {
			StringIdChatParameter stringId("shared", "harvester_no_maint_4");
			ChatSystemMessage* msg = new ChatSystemMessage(stringId);

			broadcastToOperators(msg);
			return;
		}
	}

	operating = value;

	if (operating) {
		if (!(optionsBitmask & 1)) {
			optionsBitmask |= 1;
		}
	} else {
		if (optionsBitmask & 1)
			optionsBitmask &= ~1;
	}

	InstallationObjectDeltaMessage3* delta = new InstallationObjectDeltaMessage3(_this);
	delta->updateOperating(value);
	delta->updateOptionsBitmask();
	delta->close();

	InstallationObjectDeltaMessage7* delta7 = new InstallationObjectDeltaMessage7(_this);
	delta7->updateOperating(value);
	delta7->close();

	Vector<BasePacket*> messages;
	messages.add(delta);
	messages.add(delta7);

	broadcastMessages(&messages, true);

	if (value) {
		resourceHopperTimestamp.updateToCurrentTime();
	}

	InstallationObjectDeltaMessage7* inso7 = new InstallationObjectDeltaMessage7( _this);
	inso7->updateExtractionRate(getActualRate());
	inso7->close();

	broadcastToOperators(inso7);
}

void InstallationObjectImplementation::setActiveResource(ResourceContainer* container) {
	if (resourceHopper.size() == 0) {
		addResourceToHopper(container);

		return;
	}

	int i = 0;
	for (; i < resourceHopper.size(); ++i) {
		ResourceContainer* entry = resourceHopper.get(i);

		if (entry == container) {
			if (i == 0)
				return;

			ManagedReference<ResourceContainer*> oldEntry = resourceHopper.get(0);

			InstallationObjectDeltaMessage7* inso7 = new InstallationObjectDeltaMessage7( _this);
			inso7->updateHopper();
			inso7->startUpdate(0x0D);

			resourceHopper.set(0, container, inso7, 2);
			resourceHopper.set(i, oldEntry, inso7, 0);

			inso7->close();

			broadcastToOperators(inso7);
		}
	}
}

void InstallationObjectImplementation::handleStructureAddEnergy(CreatureObject* player) {
	try {
		StringBuffer sstext, ssTotalEnergy;

		ManagedReference<SuiTransferBox*> energyBox = new SuiTransferBox(player, SuiWindowType::STRUCTURE_ADD_ENERGY);
		energyBox->setUsingObject(_this);
		energyBox->setPromptTitle("@player_structure:add_power");

		sstext	<< "@player_structure:select_power_amount"
				<<"\n\n@player_structure:current_power_value " << (int) surplusPower;

		energyBox->setPromptText(sstext.toString());

		ResourceManager* resourceManager = getZoneServer()->getResourceManager();

		ssTotalEnergy << resourceManager->getAvailablePowerFromPlayer(player);

		energyBox->addFrom("@player_structure:total_energy", ssTotalEnergy.toString(), ssTotalEnergy.toString(), "1");
		energyBox->addTo("@player_structure:to_deposit", "0", "0", "1");

		player->getPlayerObject()->addSuiBox(energyBox);
		player->sendMessage(energyBox->generateMessage());

	} catch (Exception& e) {
		e.printStackTrace();
		error("unreported exception in InstallationObjectImplementation::handleStructureAddEnergy");
	}
}

float InstallationObjectImplementation::getHopperSize() {
	float hopperSize = 0.0f;

	for (int i = 0; i < resourceHopper.size(); i++) {
		ResourceContainer* entry = resourceHopper.get(i);
		hopperSize += entry->getQuantity();
	}

	return hopperSize;
}

int InstallationObjectImplementation::getHopperItemQuantity(ResourceSpawn* spawn) {
	for (int i = 0; i < resourceHopper.size(); ++i) {
		ResourceContainer* entry = resourceHopper.get(i);

		if (entry->getSpawnObject() == spawn)
			return entry->getQuantity();
	}

	return -1;
}

ResourceContainer* InstallationObjectImplementation::getContainerFromHopper(ResourceSpawn* spawn) {
	for (int i = 0; i < resourceHopper.size(); ++i) {
		ResourceContainer* entry = resourceHopper.get(i);

		if (entry->getSpawnObject() == spawn)
			return entry;
	}

	return NULL;
}

void InstallationObjectImplementation::updateInstallationWork() {
	Time timeToWorkTill;
	bool shutdownAfterWork = updateMaintenance(timeToWorkTill);
	updateHopper(timeToWorkTill, shutdownAfterWork);
}

bool InstallationObjectImplementation::updateMaintenance(Time& workingTime) {
	Time currentTime;

	float elapsedTime = (currentTime.getTime() - lastMaintenanceTime.getTime());
	float workTimePermitted = elapsedTime;

	float payAmount = (elapsedTime / 3600.0) * getMaintenanceRate();

	bool shutdownWork = false;

	if (payAmount > surplusMaintenance) {
		//payAmount = surplusMaintenance;
		//setOperating(false);

		workTimePermitted = surplusMaintenance / getMaintenanceRate() * 3600;

		Time workTill(lastMaintenanceTime.getTime() + (int) workTimePermitted);
		workingTime = workTill;

		shutdownWork = true;
	}

	if (workTimePermitted != 0) {
		elapsedTime = workTimePermitted;
	}

	addMaintenance(-1.0f * payAmount);

	if (isOperating()) {
		float enegeryAmount = (elapsedTime / 3600.0) * basePowerRate;

		if (enegeryAmount > surplusPower) {
			enegeryAmount = surplusPower;

			float workPowerPermitted = surplusPower / basePowerRate * 3600;

			if (workPowerPermitted < elapsedTime) {
				Time workTill(lastMaintenanceTime.getTime() + (int) workPowerPermitted);
				workingTime = workTill;
			}

			shutdownWork = true;

			//setOperating(false);
		}

		addPower((int) (-1.0f * enegeryAmount));
	}

	lastMaintenanceTime.updateToCurrentTime();

	return shutdownWork;
}

void InstallationObjectImplementation::updateHopper(Time& workingTime, bool shutdownAfterUpdate) {
	// Nothing to update if we're not operating
	if (!isOperating())
		return;

	if (resourceHopper.size() == 0) // no active spawn
		return;

	ResourceContainer* container = resourceHopper.get(0);
	ResourceSpawn* spawn = container->getSpawnObject();

	// the spawn expired before we updated hopper last - don't update the hopper
	/*if (spawnExpireTimestamp.compareTo(resourceHopperTimestamp) > 0) { // if (t1 < t2) return 1;
		StringBuffer msg;
		msg << "HarvesterObjectImplementation::updateHopper(" << hex << activeResourceID << dec << ") resource expired!! (why do we have expired resources in the list?) spawnExpireTimestamp: " << dec << spawnExpireTimestamp.getTime() << "  resourceHopperTimestamp: " << resourceHopperTimestamp.getTime() << endl;
		info(msg);
		return;
	}*/

	Time currentTime = workingTime;

	Time spawnExpireTimestamp(spawn->getDespawned());
	// if (t1 < t2) return 1 - if spawnTime is sooner currentTime, use spawnTime, else use spawn time
	Time harvestUntil = (spawnExpireTimestamp.compareTo(currentTime) > 0) ? spawnExpireTimestamp : currentTime;

	float elapsedTime = (harvestUntil.getTime() - resourceHopperTimestamp.getTime());
	float spawnDensity = spawn->getDensityAt(getZone()->getZoneName(), getPositionX(), getPositionY());

	float harvestAmount = (elapsedTime / 60.0) * (spawnDensity * getExtractionRate());

	int availableCapacity = (int)(getHopperSizeMax() - getHopperSize());
	harvestAmount = harvestAmount > availableCapacity ? availableCapacity : harvestAmount;

	float currentQuantity = container->getQuantity();

	if (harvestAmount > 0) {
		spawn->extractResource(getZone()->getZoneName(), (int) harvestAmount);

		updateResourceContainerQuantity(container, (int) (currentQuantity + harvestAmount), true);
		//container->setQuantity(currentQuantity + harvestAmount);
	}
	// Update Timestamp
	resourceHopperTimestamp.updateToCurrentTime();

	if (shutdownAfterUpdate)
		setOperating(false);

	/*InstallationObjectDeltaMessage7* inso7 = new InstallationObjectDeltaMessage7( _this);
	inso7->startUpdate(0x0D);
	resourceHopper.set(0, container, inso7, 1);
	inso7->updateHopperSize(getHopperSize());
	inso7->close();

	broadcastToOperators(inso7);*/

}


void InstallationObjectImplementation::clearResourceHopper() {
	if (resourceHopper.size() == 0)
		return;

	//lets delete the containers from db

	for (int i = 0; i < resourceHopper.size(); ++i) {
		ResourceContainer* container = resourceHopper.get(i);

		container->destroyObjectFromDatabase(true);
	}

	InstallationObjectDeltaMessage7* inso7 = new InstallationObjectDeltaMessage7( _this);
	inso7->updateHopper();
	inso7->startUpdate(0x0D);

	resourceHopper.removeAll(inso7);

	inso7->updateActiveResourceSpawn(getActiveResourceSpawnID());
	inso7->updateHopperSize(getHopperSize());
	inso7->updateExtractionRate(getActualRate());

	inso7->close();

	broadcastToOperators(inso7);

	/*while (resourceHopper.size() > 0) {
		ResourceContainer* container = resourceHopper.get(0);

		removeResourceFromHopper(container);
	}*/

	setOperating(false);
}

void InstallationObjectImplementation::removeResourceFromHopper(ResourceContainer* container) {
	int index = resourceHopper.find(container);

	if (index == -1)
		return;

	container->destroyObjectFromDatabase(true);

	InstallationObjectDeltaMessage7* inso7 = new InstallationObjectDeltaMessage7( _this);
	inso7->updateHopper();
	inso7->startUpdate(0x0D);

	resourceHopper.remove(index, inso7, 1);

	inso7->updateActiveResourceSpawn(getActiveResourceSpawnID());
	inso7->updateHopperSize(getHopperSize());
	inso7->updateExtractionRate(getActualRate());

	inso7->close();

	broadcastToOperators(inso7);

	if (resourceHopper.size() == 0)
		setOperating(false);
}

void InstallationObjectImplementation::addResourceToHopper(ResourceContainer* container) {
	if (resourceHopper.contains(container))
		return;

	InstallationObjectDeltaMessage7* inso7 = new InstallationObjectDeltaMessage7( _this);
	inso7->updateHopper();
	inso7->startUpdate(0x0D);

	resourceHopper.add(container, inso7, 1);
	inso7->close();

	broadcastToOperators(inso7);
}

void InstallationObjectImplementation::changeActiveResourceID(uint64 spawnID) {

	// Logic:
	// 1) If operating, and already has an active resource ID - make sure the hopper gets updated
	// 2) Get the spawn information & set the active resource id
	// 3) If hopper size is zero for the resource + is operating, send a packet to the operators to add a zero element for delta packets

	info("updating active ");

	if (isOperating()) {
		updateInstallationWork();
	}

	ManagedReference<ResourceSpawn*> newSpawn = dynamic_cast<ResourceSpawn*>(getZoneServer()->getObject(spawnID));
	if (newSpawn == NULL) {
		error("new spawn null");
		return;
	}

	Time currentTime;

	resourceHopperTimestamp.updateToCurrentTime();

	ManagedReference<ResourceContainer*> container = getContainerFromHopper(newSpawn);

	if (container == NULL) {
		container = newSpawn->createResource(0);

		addResourceToHopper(container);
		setActiveResource(container);
	} else {
		setActiveResource(container);
	}

	InstallationObjectDeltaMessage7* inso7 = new InstallationObjectDeltaMessage7( _this);
	inso7->updateExtractionRate(getActualRate());
	inso7->updateActiveResourceSpawn(getActiveResourceSpawnID());
	inso7->close();

	broadcastToOperators(inso7);
}

void InstallationObjectImplementation::broadcastToOperators(BasePacket* packet) {
	for (int i = 0; i < operatorList.size(); ++i) {
		CreatureObject* player = operatorList.get(i);
		player->sendMessage(packet->clone());
	}

	delete packet;
}

void InstallationObjectImplementation::activateUiSync() {
	if (operatorList.size() == 0)
		return;

	try {

		if (syncUiTask == NULL)
			syncUiTask = new SyncrhonizedUiListenInstallationTask(_this);

		if (!syncUiTask->isScheduled())
			syncUiTask->schedule(5000);
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}
}

void InstallationObjectImplementation::verifyOperators() {
	if (operatorList.size() <= 0)
		return;

	// won't fully clean up at once because indexes would change once you remove one - but should clean up
	for (int i = 0; i < operatorList.size(); i++) {
		ManagedReference<CreatureObject*> obj = operatorList.get(i);

		if (!obj->isOnline()) {
			operatorList.remove(i);

			--i;
		}
	}

}

void InstallationObjectImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	StructureObjectImplementation::destroyObjectFromDatabase(destroyContainedObjects);

	if (!destroyContainedObjects)
		return;

	ManagedReference<SceneObject*> deed = getZoneServer()->getObject(deedObjectID);

	if (deed != NULL)
		deed->destroyObjectFromDatabase(true);

	for (int i = 0; i < resourceHopper.size(); ++i) {
		ResourceContainer* container = resourceHopper.get(i);

		container->destroyObjectFromDatabase(true);
	}
}

void InstallationObjectImplementation::updateResourceContainerQuantity(ResourceContainer* container, int newQuantity, bool notifyClient) {
	if (container->getQuantity() == newQuantity)
		return;

	container->setQuantity(newQuantity, false);

	if (!notifyClient)
		return;

	for (int i = 0; i < resourceHopper.size(); ++i) {
		ResourceContainer* cont = resourceHopper.get(i);

		if (cont == container) {
			InstallationObjectDeltaMessage7* inso7 = new InstallationObjectDeltaMessage7( _this);
			inso7->updateHopper();
			inso7->startUpdate(0x0D);
			resourceHopper.set(i, container, inso7, 1);
			inso7->updateHopperSize(getHopperSize());
			inso7->updateExtractionRate(getActualRate());
			inso7->close();

			broadcastToOperators(inso7);
		}
	}

	//broadcastToOperators(new InstallationObjectDeltaMessage7(_this));
}

uint64 InstallationObjectImplementation::getActiveResourceSpawnID() {
	if (resourceHopper.size() == 0) {
		return 0;
	} else {
		ResourceContainer* entry = resourceHopper.get(0);

		return entry->getSpawnObject()->getObjectID();
	}
}

float InstallationObjectImplementation::getActualRate() {
	if (!isOperating())
		return 0.0f;

	if (resourceHopper.size() == 0)
		return 0;

	ResourceContainer* container = resourceHopper.get(0);
	ResourceSpawn* spawn = container->getSpawnObject();

	return extractionRate * (spawn->getDensityAt(getZone()->getZoneName(), getPositionX(), getPositionY()));
}

