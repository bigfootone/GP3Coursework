GP2BaseCode
===========

Alexander MacDiarmid - S1307325
	Engine architect
	View Fustrum Culling
	world editor
	
David Stuart - S1313657
	input controls
	enviroment mapping 
	toon shading
	
Ricardo Barros - S13140840
	lights 
	backed shadows 
	shadow mapping 
	
controls:
	w, a, s, d - move 
	mouse - look 
	1 - empty room
	2 - universe room 
	3 - apollo 11 room 
	4 - memorial room
	p - debug mode/fly camera
	l - (while in debug mode) access the editor 
	m - enable wireframe modles (with post processing this will not have the desired effect)
	n - disable wireframe models
	space - Toggle Sepia filter
	Q - Decrease Sepia factor
	E - Increase sepia factor
	
editor commands (some may have broken)
	assignObjectName - give new object a name
	assignGameObject - get the perent for a new object or get an obejct to move 
	assignMesh - give a new object a mesh
	assignTexture - give a new object a texture
	assignShader - give a new object a shader
	spawnObject - create a new game object with the currently assigned name, mesh, texture, parent and shader
	spawnLight - create a new light (currently doesnt do anything)
	spawnNode - create a new scene node 
	transform - access the transform commands for the currently selected game object 
	setPos - change the current game objects position 
	movePos - move the current game object by an ammount 
	setRotation - change the rotation od the current game object 
	setScale - change the scale of the current game object
	doneTransform - exit the transformation commande 
	save - save the current scene graph to a file 
	load - load a scene file 
	done - to exit the editor mode