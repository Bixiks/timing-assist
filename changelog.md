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
