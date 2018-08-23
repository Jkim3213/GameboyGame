# GameboyGame
This is ColorBlast.

This game is all about manipulating colors to blast corresponding lasers at oncoming Marios.

The controls:

 Left Trigger: Shoot Laser
Right Trigger: Shoot Laser
     A Button: Prep-Light colors
     B Button: Prep-Dark colors

  Left Button: Red
    Up Button: Green
 Right Button: Blue
  Down Button: Reset Colors to Black

The game gets harder as it goes along. Try to last as long as possible and achieve high scores.
Combine colors to achieve intermediaries i.e. Light-Red + Light-Green = Light-Yellow
					      Light-Red + Dark-Green = Orange

(Hint: The Combination of what you were last hit by is revealed by the color of the score)


This game was heavily inspired from the mobile game Color Sheep.
Art was ripped from Super Mario Bros.


Full List of colors: (some colors are labeled unused because they are too hard to distinguish so are 
			not spawned as enemies, although can still be made by the player)
define MC000 BLACK
define MC111 DRED | DGREEN | DBLUE//grey
define MC222  RED |  GREEN | BLUE //white
define MC100 DRED |      0 |     0//dark red
define MC010    0 | DGREEN |     0//dark green 
define MC001    0 |      0 | DBLUE//dark blue 
define MC200  RED |      0 |     0//red 
define MC020    0 |  GREEN |     0//green 
define MC002    0 |      0 |  BLUE//blue 
define MC110 DRED | DGREEN |     0//dark yellow
define MC101 DRED |      0 | DBLUE//dark magenta
define MC011    0 | DGREEN | DBLUE//dark cyan
define MC220  RED |  GREEN |     0//yellow
define MC202  RED |      0 |  BLUE//magenta
define MC022    0 |  GREEN |  BLUE//cyan
define MC210  RED | DGREEN |     0//orange
define MC201  RED |      0 | DBLUE//unused pink
define MC120 DRED |  GREEN |     0//unused lime
define MC021    0 |  GREEN | DBLUE//unused pastel green
define MC102 DRED |      0 |  BLUE//pastel purple
define MC012    0 | DGREEN |  BLUE//pastel blue
define MC211  RED | DGREEN | DBLUE//unused peach
define MC121 DRED |  GREEN | DBLUE//unused pale green
define MC112 DRED | DGREEN |  BLUE//pastel indigo
define MC221  RED |  GREEN | DBLUE//unused pastel yellow
define MC212  RED | DGREEN |  BLUE//pink
define MC122 DRED |  GREEN |  BLUE//unused pastel cyan
