OldaleTown_House2_MapScripts:: @ 81FBF5A
	.byte 0

OldaleTown_House2_EventScript_Woman:: @ 81FBF5B
	msgbox OldaleTown_House2_Text_PokemonLevelUp, MSGBOX_NPC
	end

OldaleTown_House2_EventScript_Man:: @ 81FBF64
	msgbox OldaleTown_House2_Text_YoullGoFurtherWithStrongPokemon, MSGBOX_NPC
	end

@ ORIGINAL TEXT
OldaleTown_House2_Text_PokemonLevelUp_ORIGINAL: @ 81FBF6D
	.string "When POKéMON battle, they eventually\n"
	.string "level up and become stronger.$"

@ MODIFIED TEXT
OldaleTown_House2_Text_PokemonLevelUp: @ 81FBF6D
	.string "When POKéMON battle, they eventually\n"
	.string "level up and become stronger.\p"
	.string "They will also have a less likely\n"
	.string "chance of dying in battle.$"

@ ORIGINAL TEXT
OldaleTown_House2_Text_YoullGoFurtherWithStrongPokemon_ORIGINAL: @ 81FBFB0
	.string "If the POKéMON with you become\n"
	.string "stronger, you'll be able to go farther\l"
	.string "away from here.$"

@ MODIFIED TEXT
OldaleTown_House2_Text_YoullGoFurtherWithStrongPokemon: @ 81FBFB0
	.string "If the POKéMON with you become\n"
	.string "stronger, you'll be able demolish\l"
	.string "anyone in your way!$"
