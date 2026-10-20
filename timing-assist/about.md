# Timing Assist

Made for low fps and laggy or blurry monitors.

When you click, the mod quickly runs the game's own physics a little into the future. If clicking right now would kill you but clicking a few ms later wouldn't, it holds your click until that tick and then lets it through. If now is already fine, nothing changes.

It never makes a click earlier, only later, so the trick is to click a hair early and let it line you up.

## Works in every gamemode
Cube, ship, ball, UFO, wave, robot, spider and swing, plus mini, dual and platformer.

## Release compensation
- **Keep Hold Length:** if your press was delayed, your release gets the same delay, so a ship or wave hold stays the length you meant.
- **Release Assist:** in ship, wave and robot your release also gets checked and moved to the nearest safe tick.

## Smart Predict (experimental, off by default)
Fixes clicks that came slightly too late. The mod remembers your player's last few ticks. If a click comes in late and pressing now would kill you, it checks whether pressing a few ticks earlier would have worked. If so, it rewinds your player to that tick, applies the click there, and catches back up in the same frame. Ship, wave and robot releases get the same treatment.

It only rewinds if nothing else happened in between (no other inputs, orbs, pads, portals, gamemode or gravity changes). Your icon can snap a tiny bit when it kicks in.

## Good to know
- It won't touch a click while you're on an orb or dashing.
- It stops looking ahead at pads, portals and orbs it can't predict, so it plays it safe around them.
- Moving objects are treated as if they stand still during the check.
- Safe Mode (on by default) blocks progress for any attempt where it actually moved an input.
- Turn Click Between Frames off while using this, they fight over input timing.
