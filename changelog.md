# v1.4.4
- Bigger fix for percent and orbs not saving: after every check the mod now puts back every value in the level and game state it could have touched, not just a few
- Debug Overlay now shows a save check after each attempt, to help track down saving problems

# v1.4.3
- Another fix for percent and orbs not saving with Safe Mode off. The invisible test players were leaving traces in the game's level state and its object counter, which the game checks before saving. All of that is now put back exactly how it was after every check
- The mod now waits a moment at the start of each attempt before it steps in
- With Enabled turned off, the mod no longer does anything in levels

# v1.4.2
- Fixed percent and orbs not saving even with Safe Mode off: the invisible test players could touch the game's anticheat spike, which made the game think you were using noclip. The simulation now skips that spike and never touches the real hit
- Also fixes the start of levels sometimes looking "dangerous" to the mod for the same reason

# v1.4.1
- Fixed orb clicks doing nothing: clicking while you're on an orb now always goes through instantly (no delay, no Input Lead)
- A delayed click that's still waiting fires right away the moment you touch an orb

# v1.4.0
- Plan Ahead setting (1-4 moves): makes sure you can keep surviving that many moves after your click, in every gamemode
- Lookahead can go up to 2 seconds now, and it also lets cube, ball and robot falls be followed longer

# v1.3.3
- Cube, ball and robot: a landing only counts as safe if you can keep going from there (standing still works, or some follow-up jump lands safely too). Fixes it picking a jump that touches down on a ledge and then falls into spikes
- Landing right next to spikes is still fine, as long as the spot is survivable
- Max Think Time default raised to 8ms since landings get checked more carefully now

# v1.3.2
- Fixed robot clicks lagging the game hard enough to cut your hold short
- Every click now has a time limit (Max Think Time, 5ms by default). If the check runs out of time your input just goes through unchanged
- Robot checks try fewer hold lengths

# v1.3.1
- Fixed cube jumps getting pushed later on long drops (overshooting the block you meant to land on)
- Cube, ball and robot checks now follow the jump until you land instead of stopping mid-air
- A jump that already works only gets swapped if the new one lands on the same block and you were basically touching a spike

# v1.3.0
- Orbs & pads are simulated with the game's own physics, so clicks on orbs get lined up too
- Frame perfects: picks safer ticks when your timing only barely survives, searches a bit further as a last resort, and calibrates its own timing
- Smart Predict now slides your icon instead of snapping it, skips fixes that would move you too far, and is on by default
- Wave Adjust (super experimental): holds your wave for you until letting go is safe

# v1.2.0
- Only steps in when no reasonable hold or follow-up click saves your timing (fixes wave presses getting delayed for no reason)
- Picks the safest tick instead of the first one that survives
- Input Lead: lets the mod move clicks earlier too (wave and ship by default)
- Separate, smaller max delay for wave and ship
- Better checks for UFO, swing and spider
- Debug Overlay with live death projection

# v1.1.0
- Added Smart Predict (experimental): fixes clicks and releases that came a few ms too late

# v1.0.0
- First release
