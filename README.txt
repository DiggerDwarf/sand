

                    Little Sandbox I made

Click to place, you can hold & drag

Hotkey or click to change tile (the X is not a tile dummy)
Click the X button to reset

Press the Escape key (Echap in french) to close the app (or just Alt+F4 works fine really)

List of tiles:
 0) Air         in Black
 1) Sand        in yellow
 2) Rock        in Grey
 3) Water       in blue
 4) Lava        in orange
 5) Obsidian    in dark purple
 6) Vegetation  in green

The game runs at 50 ticks/frames per second, lower if your computer is a potato

List of behaviors (spoilers, better to discover yourself):
  - Sand flows down and when it cannot, diagonally down
  - Sand sinks straight in water, diagonally in Lava
  - Rock gets eroded by water with a 0.1% chance every ticks
  - Water and lava flows in this order of priority : down, diagonally down, straight
  - Water above Lava forms Obsidian
  - Lava above Water forms Rock
  - Obsidian has no interactions, it's what the bounding box is made of
  - Vegetation gets burned by Lava from above
  - Vegetation chooses a random block around itself and does the following:
      - if that block if Rock, it climbs on it with a 3.3% chance
      - if that block is Water, it grows in it with a 50% chance




