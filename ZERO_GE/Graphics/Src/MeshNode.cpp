
//====================================================================================================
// Includes
//====================================================================================================
#include "Precompiled.h"
#include "MeshNode.h"


//====================================================================================================
// Class Definitions
//====================================================================================================
using namespace ZERO;
using namespace ZERO::Graphics;

MeshNode::MeshNode()
	: SceneNode()
	, mpMesh(nullptr)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

MeshNode::~MeshNode()
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

void MeshNode::OnRender()
{
	if (mpMesh != nullptr)
	{
		mpMesh->Render();
	}
}