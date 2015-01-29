CMPS 164: Game Engines, Spring 2011
Author: Alessandra Chen, aachen@ucsc.edu

SETUP INSTRUCTIONS
+ In command console, go to the directory with the MiniGolf
  executable, inside the Binary folder.
+ To run: Minigolf level1.txt level2.txt level3.txt...

DEVELOPMENT LOG
5/16/2011:
+ Game is organized into states (menu, play, results, load), and
  the player is able to transition through them in gameplay.
+ Game rules & play are applied: player can now charge and hit
  ball with certain amount of power, and the ball direction
  cannot be changed while moving. Scores are also tracked
+ Added Overlay, MenuScreen classes and updated Hud class for
  more practical organization in engine terms, and to handle
  level selection states, transition and end result displaying.
+ All levels are pre-loaded into an array rather than being
  instansiated on after-completion basis.
+ InputHandler class added to keep main code less bulky and organized.
+ Math class has a clamping function (to keep numbers within bounds).
+ Once timestep issue of slope direction calculation (changing
  direction too early or too late upon entering slope) and cup radius
  tilting is resolved, it should be a full, playable game.

5/11/2011:
+ Ball direction control.
+ Detached camera components from main to it's own class,
  with default, top, free, and follow modes.
+ Got HUD to display correctly, still need to add status/data
  components and gameplay interface.
+ Added Player class interface to manage player's scores, ball
  striking power, etc.
+ Shaders are working and is used to do basic lighting instead
  of GL's fixed function.
+ Physics can now handle wall-ball collision testing and response,
  ball motion and tracking.
+ Created small Math file to keep codes organized/separate.
+ Added more auxiliary functions in Util.
+ Game is now time based versus CPU's clock rate.

4/22/2011:
+ removed lists in favor for arrays, modified data variables
  to pointers for better compatibility, memory management.
+ changed Point3D to Vector3D
+ added Vector3D auxiliary functions
+ fixed and added lighting based on tile normals
+ drawing of tile/edge normals, to test proper functionality
+ Ball class has position, velocity, direction
+ Physics class added to handle ball movement based on ball's
  vector properties as specified on lab page.
+ fixed tee drawing.
+ re-wrote a lot of functions for cleaner code in general


CONTROLS:
+ Camera:
    - [1], [2], [3], [4]: switch between default/free/top-view/follow modes
    - Free Mode: [a], [s], [d], [w] for camera rotation
+ Gameplay:
    - Hold [p]: charge power
	- Release [p]: hit ball
    - [n], [m]: rotate direction
    - [c]: temporary player charge (to strike ball)
+ Menu:
	- [n], [m]: scroll through level
	- [x]: choose level
+ General:
	- [ESC]: exit window
	
REFERENCES:
+ Circles: http://en.wikibooks.org/wiki/OpenGL_Programming/Basics/2DObjects
+ Normal Calculation: http://nehe.gamedev.net/data/lessons/lesson.asp?lesson=36
+ Timers: http://www.cplusplus.com/reference/clibrary/ctime/clock/
+ HUD: http://www.swiftless.com/tutorials/opengl/orthogonal.html
+ Shaders: http://www.lighthouse3d.com/opengl/glsl/

FUTURE PLANS:
+ fix and keep ball from crossing over edge
+ fix bug of ball sinking into terrain (ball rotation->slope direction)
+ ball-hole collison detection & response
+ HUD rendering & power bar
+ tilt hold drawing to lay flat on plane
+ move debugging code to it's own class (min priority)