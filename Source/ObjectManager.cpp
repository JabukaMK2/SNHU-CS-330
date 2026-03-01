#include "SceneManager.h"

// ObjectManager is a helper class that extends SceneManager for organization only
namespace
{
    // Added new color presets
    const glm::vec4 grey(0.3f, 0.3f, 0.3f, 1.0f); // grey
    const glm::vec4 glassColor(0.05f, 0.05f, 0.05f, 0.35f); // dark tinted glass
    const glm::vec4 black(0.1f, 0.1f, 0.1f, 1.0f); // black
	const glm::vec4 noTint(1.0f, 1.0f, 1.0f, 1.0f); // white (does not alter the color of texture)
	const glm::vec4 tanColor(0.9f, 0.8f, 0.7f, 1.0f); // tan
}

/***********************************************************
 *  RenderComputer()
 *
 *  This method is used for rendering the computer frame
 *  and initializes each part then for loops to render each
 *  part instead of having 12 individual functions.
 *  Consists of the base, top, glass, and sides rendering
 *  the scale, position, rotation, and color from this
 *  array.
 ***********************************************************/
void SceneManager::RenderComputer()
{
	const ComputerPart parts[] =
	{
		// BASE ------------------ SCALE ------------------------------- POSITION------------------ ROTATE ----- COLOR ----------
		ComputerPart(glm::vec3(3.0f, 0.4f, 5.0f),  glm::vec3(8.3f, 0.2f, 0.0f),    0.0f,   black), // Back
		ComputerPart(glm::vec3(2.0f, 0.4f, 1.0f),  glm::vec3(8.8f, 0.2f, 3.0f),    0.0f,   black), // Front
		ComputerPart(glm::vec3(1.4f, 0.4f, 1.0f),  glm::vec3(7.65f, 0.2f, 2.65f),  -45.0f, black), // Corner
		
		// TOP ------------------- SCALE ------------------------------- POSITION------------------ ROTATE ----- COLOR ----------
		ComputerPart(glm::vec3(3.0f, 0.4f, 5.0f),  glm::vec3(8.3f, 3.2f, 0.0f),    0.0f,   black), // Back
		ComputerPart(glm::vec3(2.0f, 0.4f, 1.0f),  glm::vec3(8.8f, 3.2f, 3.0f),    0.0f,   black), // Front
		ComputerPart(glm::vec3(1.4f, 0.4f, 1.0f),  glm::vec3(7.65f, 3.2f, 2.65f),  -45.0f, black), // Corner
		
		// SIDE ------------------ SCALE ------------------------------- POSITION------------------ ROTATE ----- COLOR ----------
		ComputerPart(glm::vec3(2.88f, 3.0f, 0.05f), glm::vec3(8.3f, 1.5f, -2.47f), 0.0f, black), // Back
		ComputerPart(glm::vec3(0.05f, 3.0f, 5.9f),  glm::vec3(9.76f, 1.5f, 0.47f), 0.0f, black), // Right
		ComputerPart(glm::vec3(0.8f, 3.0f, 4.3f),   glm::vec3(9.35f, 1.5f, -0.34f),0.0f, black), // Inside
		
		// GLASS ----------------- SCALE ------------------------------- POSITION------------------ ROTATE ----- COLOR ----------
		ComputerPart(glm::vec3(0.05f, 3.0f, 5.0f),  glm::vec3(6.9f, 1.5f, 0.0f),   0.0f,   glassColor), // Left
		ComputerPart(glm::vec3(2.0f, 3.0f, 0.05f),  glm::vec3(8.8f, 1.5f, 3.43f),  0.0f,   glassColor), // Front
		ComputerPart(glm::vec3(1.275f, 3.0f, 0.05f),glm::vec3(7.35f, 1.5f, 2.97f), -45.0f, glassColor) // Corner
	};
	
	// For each item withing ComputerPart (as part)
	for (const ComputerPart& part : parts)
	{
		// Set as item within array that matches the needed data.
		// Made to reduce repeat functionality
		SetTransformations(
			part.scaleXYZ, 
			0.0f,
			part.rotationY, 
			0.0f,
			part.positionXYZ);
		
		// Uses the preconfigured colors that have been constructed for this function
		// Changed to m_pShaderManager to tint the texture
		m_pShaderManager->setVec4Value("objectColor", glm::vec4(part.color.r, part.color.g, part.color.b, part.color.a));
		
		// Added plastic texture
		SetShaderTexture("case");
		SetTextureUVScale(1.0f, 1.0f);
		SetShaderMaterial("matte");
		
		m_basicMeshes->DrawBoxMesh();
	}
}

/***********************************************************
 *  RenderFloor()
 *
 *  This method is used for rendering the floor
 ***********************************************************/
void SceneManager::RenderFloor()
{
	// declare the variables for the transformations
	glm::vec3 scaleXYZ;
	float XrotationDegrees = 0.0f;
	float YrotationDegrees = 0.0f;
	float ZrotationDegrees = 0.0f;
	glm::vec3 positionXYZ;
	
	// set the XYZ scale for the mesh
	scaleXYZ = glm::vec3(50.0f, 0.1f, 50.0f);

	// set the XYZ rotation for the mesh
	XrotationDegrees = 0.0f;
	YrotationDegrees = 0.0f;
	ZrotationDegrees = 0.0f;

	// set the XYZ position for the mesh
	positionXYZ = glm::vec3(0.0f, -7.0f, 0.0f);

	// set the transformations into memory to be used on the drawn meshes
	SetTransformations(
		scaleXYZ,
		XrotationDegrees,
		YrotationDegrees,
		ZrotationDegrees,
		positionXYZ);

	// SetShaderColor(0.7647f, 0.7059f, 0.6275f, 1);
	SetShaderTexture("floor");
	SetShaderMaterial("matte");
	m_pShaderManager->setVec4Value("objectColor", tanColor);
	SetTextureUVScale(5.0f, 10.0f);

	// draw the mesh with transformation values
	m_basicMeshes->DrawPlaneMesh();
	SetTextureUVScale(1.0f, 1.0f);
}
/***********************************************************
 *  RenderDeskTop()
 *
 *  This method is used for rendering the desk top using 
 *  a box with the top rendered separate to use a leather
 *  top surface.
 ***********************************************************/
void SceneManager::RenderDeskTop()
{
	// declare the variables for the transformations
	glm::vec3 scaleXYZ;
	float XrotationDegrees = 0.0f;
	float YrotationDegrees = 0.0f;
	float ZrotationDegrees = 0.0f;
	glm::vec3 positionXYZ;
	
	// set the XYZ scale for the mesh
	scaleXYZ = glm::vec3(20.0f, 0.3f, 8.0f);

	// set the XYZ rotation for the mesh
	XrotationDegrees = 0.0f;
	YrotationDegrees = 0.0f;
	ZrotationDegrees = 0.0f;

	// set the XYZ position for the mesh
	positionXYZ = glm::vec3(0.0f, 0.0f, 0.0f);

	// set the transformations into memory to be used on the drawn meshes
	SetTransformations(
		scaleXYZ,
		XrotationDegrees,
		YrotationDegrees,
		ZrotationDegrees,
		positionXYZ);
	
	// Sets a texture for the top mat
	SetShaderTexture("desk_mat");
	SetShaderMaterial("matte");
	m_pShaderManager->setVec4Value("objectColor", black);
	SetTextureUVScale(5.0f, 5.0f);
	
	// draw top
	m_basicMeshes->DrawBoxMeshSide(ShapeMeshes::top);
	
	// Sets a texture and tints the texture black
	SetShaderTexture("steel");
	SetShaderMaterial("steel");
	m_pShaderManager->setVec4Value("objectColor", grey);
	SetTextureUVScale(5.0f, 5.0f);

	// draw the mesh with transformation values
	m_basicMeshes->DrawBoxMesh();
	
	// Reset UV scale for any other method
	SetTextureUVScale(1.0f, 1.0f);
}

/***********************************************************
 *  RenderMonitor()
 *
 *  This method renders the monitor display as a box to give
 *  it a raised 3D look with the box.  A plane had too much
 *  risk of collision or lack thereof.
 ***********************************************************/
void SceneManager::RenderMonitor()
{
	// declare the variables for the transformations
	glm::vec3 scaleXYZ;
	float XrotationDegrees = 0.0f;
	float YrotationDegrees = 0.0f;
	float ZrotationDegrees = 0.0f;
	glm::vec3 positionXYZ;
	
	// set the XYZ scale for the mesh
	scaleXYZ = glm::vec3(10.0f, 0.1f, 4.0f);

	// set the XYZ rotation for the mesh
	XrotationDegrees = 90.0f;
	YrotationDegrees = 0.0f;
	ZrotationDegrees = 0.0f;

	// set the XYZ position for the mesh
	positionXYZ = glm::vec3(0.0f, 4.0f, -2.0f);

	// set the transformations into memory to be used on the drawn meshes
	SetTransformations(
		scaleXYZ,
		XrotationDegrees,
		YrotationDegrees,
		ZrotationDegrees,
		positionXYZ);

	// Sets a texture for the display
	SetShaderTexture("display");
	SetShaderMaterial("glass");

	SetTextureUVScale(1.0f, 1.0f);
	
	// draw top
	m_basicMeshes->DrawBoxMeshSide(ShapeMeshes::top);
	
	// Sets a texture and tints the texture black
	SetShaderTexture("case");
	SetShaderMaterial("matte");
	m_pShaderManager->setVec4Value("objectColor", grey);
	SetTextureUVScale(5.0f, 5.0f);

	// draw the mesh with transformation values
	m_basicMeshes->DrawBoxMesh();
	
	// Reset UV scale for any other method
	SetTextureUVScale(1.0f, 1.0f);
}

/***********************************************************
 *  RenderMonitorFrame()
 *
 *  Monitors have bezels, at least to some degree.  This
 *  function adds a box behind the display to simulate a 
 *  separate display and frame with bezels.
 ***********************************************************/
void SceneManager::RenderMonitorFrame()
{
	// declare the variables for the transformations
	glm::vec3 scaleXYZ;
	float XrotationDegrees = 0.0f;
	float YrotationDegrees = 0.0f;
	float ZrotationDegrees = 0.0f;
	glm::vec3 positionXYZ;
	
	// set the XYZ scale for the mesh
	scaleXYZ = glm::vec3(10.2f, 0.1f, 4.2f);

	// set the XYZ rotation for the mesh
	XrotationDegrees = 90.0f;
	YrotationDegrees = 0.0f;
	ZrotationDegrees = 0.0f;

	// set the XYZ position for the mesh
	positionXYZ = glm::vec3(0.0f, 4.0f, -2.001f);

	// set the transformations into memory to be used on the drawn meshes
	SetTransformations(
		scaleXYZ,
		XrotationDegrees,
		YrotationDegrees,
		ZrotationDegrees,
		positionXYZ);
	
	// Sets a texture and tints the texture black
	SetShaderTexture("case");
	SetShaderMaterial("matte");
	m_pShaderManager->setVec4Value("objectColor", grey);
	SetTextureUVScale(5.0f, 5.0f);

	// draw the mesh with transformation values
	m_basicMeshes->DrawBoxMesh();
	
	// Reset UV scale for any other method
	SetTextureUVScale(1.0f, 1.0f);
}

/***********************************************************
 *  RenderMonitorStand()
 *
 *  Here we use a box as a bar and another box as the support
 *  platform for it to sit on.
 ***********************************************************/
void SceneManager::RenderMonitorStand()
{
	// declare the variables for the transformations
	glm::vec3 scaleXYZ;
	float XrotationDegrees = 0.0f;
	float YrotationDegrees = 0.0f;
	float ZrotationDegrees = 0.0f;
	glm::vec3 positionXYZ;
	
	// set the XYZ scale for the mesh
	scaleXYZ = glm::vec3(1.0f, 1.0f, 4.0f);

	// set the XYZ rotation for the mesh
	XrotationDegrees = 90.0f;
	YrotationDegrees = 0.0f;
	ZrotationDegrees = 0.0f;

	// set the XYZ position for the mesh
	positionXYZ = glm::vec3(0.0f, 2.0f, -2.5f);

	// set the transformations into memory to be used on the drawn meshes
	SetTransformations(
		scaleXYZ,
		XrotationDegrees,
		YrotationDegrees,
		ZrotationDegrees,
		positionXYZ);
	
	// Sets a texture and tints the texture black
	SetShaderTexture("case");
	SetShaderMaterial("matte");
	m_pShaderManager->setVec4Value("objectColor", grey);
	SetTextureUVScale(5.0f, 5.0f);

	// draw the mesh with transformation values
	m_basicMeshes->DrawBoxMesh();
	
	scaleXYZ = glm::vec3(4.0f, 0.2f, 2.5f);

	// set the XYZ rotation for the mesh
	XrotationDegrees = 0.0f;
	YrotationDegrees = 0.0f;
	ZrotationDegrees = 0.0f;

	// set the XYZ position for the mesh
	positionXYZ = glm::vec3(0.0f, 0.2f, -2.0f);
	
	SetTransformations(
		scaleXYZ,
		XrotationDegrees,
		YrotationDegrees,
		ZrotationDegrees,
		positionXYZ);
	
	m_basicMeshes->DrawBoxMesh();
	
	// Reset UV scale for any other method
	SetTextureUVScale(1.0f, 1.0f);
}

/***********************************************************
 *  RenderSpeakers()
 *
 *  This method renders the speakers as tapered cylinders
 *  at an angle, giving it the appearance of desktop speakers.
 ***********************************************************/
void SceneManager::RenderSpeakers()
{
	// declare the variables for the transformations
	glm::vec3 scaleXYZ;
	float XrotationDegrees = 0.0f;
	float YrotationDegrees = 0.0f;
	float ZrotationDegrees = 0.0f;
	glm::vec3 positionXYZ;
	
	// set the XYZ scale for the mesh
	scaleXYZ = glm::vec3(0.7f, 0.9f, 0.7f);

	/***               Start of the Right Speaker                   ***/
	/******************************************************************/
	
	// set the XYZ rotation for the mesh
	// tilts up and to the left
	XrotationDegrees = -112.0f;
	YrotationDegrees = -10.0f;
	ZrotationDegrees = 0.0f;

	// set the XYZ position for the mesh
	positionXYZ = glm::vec3(4.5f, 0.8f, -2.0f);

	// set the transformations into memory to be used on the drawn meshes
	SetTransformations(
		scaleXYZ,
		XrotationDegrees,
		YrotationDegrees,
		ZrotationDegrees,
		positionXYZ);
	
	// Sets a texture and tints the texture black
	SetShaderTexture("case");
	SetShaderMaterial("matte");
	m_pShaderManager->setVec4Value("objectColor", black);
	SetTextureUVScale(5.0f, 5.0f);

	// draw the mesh with transformation values
	m_basicMeshes->DrawTaperedCylinderMesh();
	
	// Reset UV scale for any other method
	SetTextureUVScale(1.0f, 1.0f);
	
	/***               Start of the Left Speaker                    ***/
	/******************************************************************/
	
	// set the XYZ rotation for the mesh
	// tilts up and to the right
	XrotationDegrees = -112.0f;
	YrotationDegrees = 10.0f;
	ZrotationDegrees = 0.0f;

	// set the XYZ position for the mesh
	positionXYZ = glm::vec3(-4.5f, 0.8f, -2.0f);

	// set the transformations into memory to be used on the drawn meshes
	SetTransformations(
		scaleXYZ,
		XrotationDegrees,
		YrotationDegrees,
		ZrotationDegrees,
		positionXYZ);
	
	// Sets a texture and tints the texture black
	SetShaderTexture("case");
	SetShaderMaterial("matte");
	m_pShaderManager->setVec4Value("objectColor", black);
	SetTextureUVScale(5.0f, 5.0f);

	// draw the mesh with transformation values
	m_basicMeshes->DrawTaperedCylinderMesh();
	
	// Reset UV scale for any other method
	SetTextureUVScale(1.0f, 1.0f);
}

/***********************************************************
 *  RenderSpeakerGrill()
 *
 *  Here we render a mesh for the speaker by making a
 *  sphere which is smushed on its Z axis, giving it
 *  the desired appearance.
 ***********************************************************/
void SceneManager::RenderSpeakerGrill()
{
	// declare the variables for the transformations
	glm::vec3 scaleXYZ;
	float XrotationDegrees = 0.0f;
	float YrotationDegrees = 0.0f;
	float ZrotationDegrees = 0.0f;
	glm::vec3 positionXYZ;
	
	// set the XYZ scale for the mesh
	scaleXYZ = glm::vec3(0.63f, 0.63f, 0.1f);

	// set the XYZ rotation for the mesh
	XrotationDegrees = -22.0f;
	YrotationDegrees = -10.0f;
	ZrotationDegrees = 0.0f;

	// set the XYZ position for the mesh
	positionXYZ = glm::vec3(4.5f, 0.8f, -2.0f);

	// set the transformations into memory to be used on the drawn meshes
	SetTransformations(
		scaleXYZ,
		XrotationDegrees,
		YrotationDegrees,
		ZrotationDegrees,
		positionXYZ);
	
	// Sets a texture and tints the texture black
	SetShaderTexture("mesh");
	SetShaderMaterial("matte");
	m_pShaderManager->setVec4Value("objectColor", grey);
	SetTextureUVScale(1.0f, 1.0f);

	// draw the mesh with transformation values
	m_basicMeshes->DrawSphereMesh();
	
	
	// LEFT GRILL
	// set the XYZ scale for the mesh
	scaleXYZ = glm::vec3(0.63f, 0.63f, 0.1f);

	// set the XYZ rotation for the mesh
	XrotationDegrees = -22.0f;
	YrotationDegrees = 10.0f;
	ZrotationDegrees = 0.0f;

	// set the XYZ position for the mesh
	positionXYZ = glm::vec3(-4.5f, 0.8f, -2.0f);

	// set the transformations into memory to be used on the drawn meshes
	SetTransformations(
		scaleXYZ,
		XrotationDegrees,
		YrotationDegrees,
		ZrotationDegrees,
		positionXYZ);
	
	// Sets a texture and tints the texture black
	SetShaderTexture("mesh");
	SetShaderMaterial("matte");
	m_pShaderManager->setVec4Value("objectColor", grey);
	SetTextureUVScale(1.0f, 1.0f);

	// draw the mesh with transformation values
	m_basicMeshes->DrawSphereMesh();
}

/***********************************************************
 *  RenderKeyboardSimple()
 *
 *  This method is used for rendering a simple box keyboard
 *  which uses an RGB keyboard skin on top, then rendering
 *  the other sides as our plastic texture.
 ***********************************************************/
void SceneManager::RenderKeyboardSimple()
{
	// declare the variables for the transformations
	glm::vec3 scaleXYZ;
	float XrotationDegrees = 0.0f;
	float YrotationDegrees = 0.0f;
	float ZrotationDegrees = 0.0f;
	glm::vec3 positionXYZ;
	
	// set the XYZ scale for the mesh
	scaleXYZ = glm::vec3(5.0f, 0.2f, 2.0f);

	// set the XYZ rotation for the mesh
	XrotationDegrees = 3.0f;
	YrotationDegrees = 0.0f;
	ZrotationDegrees = 0.0f;

	// set the XYZ position for the mesh
	positionXYZ = glm::vec3(0.0f, 0.16f, 2.5f);

	// set the transformations into memory to be used on the drawn meshes
	SetTransformations(
		scaleXYZ,
		XrotationDegrees,
		YrotationDegrees,
		ZrotationDegrees,
		positionXYZ);
	
	// Adds a top down keyboard RGB texture to give the scene more color
	SetShaderTexture("keys");
	SetShaderMaterial("matte");
	m_pShaderManager->setVec4Value("objectColor", noTint);
	SetTextureUVScale(1.0f, 1.0f);
	
	m_basicMeshes->DrawBoxMeshSide(ShapeMeshes::top);
	
	// Sets a texture and tints the texture black
	SetShaderTexture("case");
	SetShaderMaterial("matte");
	m_pShaderManager->setVec4Value("objectColor", grey);
	SetTextureUVScale(5.0f, 5.0f);

	// draw the mesh with transformation values
	m_basicMeshes->DrawBoxMesh();
	
	// Reset UV scale for any other method
	SetTextureUVScale(1.0f, 1.0f);
}

/***********************************************************
 *  RenderLegs()
 *
 *  This method is used for rendering all 4 legs
 ***********************************************************/
void SceneManager::RenderLegs()
{
	// Declare scale as all legs are identical in shape and size
	glm::vec3 scaleXYZ = glm::vec3(0.8f, 7.0f, 0.2f);
	
	// Store all leg positions
	constexpr glm::vec3 leg_position[] = {
		{-9.5f, -3.5f, 3.8f},
		{9.5f, -3.5f, 3.8f},
		{-9.5f, -3.5, -3.8f},
		{9.5f, -3.5, -3.8f}
	};
	
	// Iterate through all leg positions
	for (auto& leg : leg_position)
	{
		// set the transformations into memory to be used on the drawn meshes
		SetTransformations(
			scaleXYZ,
			0.0f,
			0.0f,
			0.0f,
			leg);
		
		// set the color into the shader
		m_pShaderManager->setVec4Value("objectColor", black);
		SetShaderTexture("steel");
		SetShaderMaterial("steel");
		SetTextureUVScale(1.0f, 20.0f);
		
		// draw the mesh with transformation values
		m_basicMeshes->DrawBoxMesh();
	}
	
	// Resets UV scale
	SetTextureUVScale(1.0f, 1.0f);
}