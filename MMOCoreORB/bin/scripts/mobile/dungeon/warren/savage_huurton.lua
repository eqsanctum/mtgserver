savage_huurton = Creature:new {
	objectName = "@mob/creature_names:warren_huurton_savage",
	socialGroup = "warren_huurton",
	pvpFaction = "",
	faction = "",
	level = 26,
	chanceHit = 0.35,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2637,
	baseHAM = 6800,
	baseHAMmax = 8300,
	armor = 0,
	resists = {135,135,0,-1,0,0,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "hide_wooly",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 35,
	milkType = "milk_wild",
	milk = 35,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/huurton_hue.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(savage_huurton, "savage_huurton")
