# Timing Assist

Made for low fps and laggy or blurry monitors.

When you click, the mod quickly runs the game's own physics a little into the future. If clicking right now would kill you but clicking a few ms later wouldn't, it holds your click until that tick and then lets it through. If now is already fine, nothing changes.

It only steps in when your timing really doesn't work. It tests a range of hold lengths and follow-up clicks, and leaves your input alone if any reasonable one works. When it does move an input, it picks the tick that keeps you furthest from hazards, not just the first one that survives.

Without Input Lead it can only move clicks later, so click a hair early and let it line you up.

## Input Lead
Wave and ship get a tiny fixed delay on every click (8ms by default). That gives the mod room to move a click earlier as well as later, which matters most in wave, where most mistakes are late clicks. You can change the amount, pick which gamemodes use it, or set it to 0.

## Works in every gamemode
Cube, ship, ball, UFO, wave, robot, spider and swing, plus mini, dual and platformer.

## Release compensation
- **Keep Hold Length:** if your press was delayed, your release gets the same delay, so a ship or wave hold stays the length you meant.
- **Release Assist:** in ship, wave and robot your release also gets checked and moved to the nearest safe tick.

## Orbs & Pads
The check runs through orbs and pads using the game's own orb code, so every gamemode reacts to them exactly like the real game. Clicks you make while touching an orb always go through instantly, so orbs always trigger. Custom orbs, teleport orbs and portals still stop the check.

## Frame perfects
- It checks that you'd survive with a margin, not just barely. If your timing only scrapes by and another tick is clearly safer, it moves to that one.
- For cube, ball and robot, a landing only counts as safe if you can keep going from there: standing still works, or some follow-up jump lands safely. So it aims for spots you can actually continue from. Landing right next to spikes is still fine.
- **Plan Ahead** (1-4) sets how many moves ahead it checks. At 2 or more, the move after your next one has to work too. This works in every gamemode. Give it more Max Think Time when you raise it.
- If nothing safe is found in the normal window, it looks a few ticks further as a last resort.
- It calibrates its own timing. It compares its predictions with what really happens, and if it's consistently one tick off it corrects itself and remembers that.

## Smart Predict (experimental, on by default)
Fixes clicks that came slightly too late. The mod remembers your player's last few ticks. If a click comes in late and pressing now would kill you, it checks whether pressing a few ticks earlier would have worked, and if so replays those ticks with the click in the right spot. Your icon slides over to the fixed path over a few frames instead of snapping, and fixes that would move you too far are skipped. Ship, wave and robot releases get the same treatment.

It only does this if nothing else happened in between (no other inputs, orbs, pads, portals, gamemode or gravity changes).

## Wave Adjust (super experimental, off by default)
If you let go in wave at a bad time, it keeps holding for you until letting go is safe, then lets go (up to 120ms by default). Clicking again while it's holding just keeps you holding.

## Debug Overlay
Draws a live projection like Show Trajectory: green is where you go if you click or keep holding, blue is where you go if you don't click or let go, and red and blue boxes mark where you'd die. When the mod moves an input it briefly shows your timing in orange and its pick in yellow, and the corner label names every decision.

## Good to know
- It won't touch a click while you're on an orb or dashing.
- Moving objects are treated as if they stand still during the check.
- Safe Mode (on by default) blocks progress for any attempt where it actually moved an input.
- Turn Click Between Frames off while using this, they fight over input timing.
