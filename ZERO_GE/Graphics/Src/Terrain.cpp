#include "Precompiled.h"

#include "Terrain.h"
#include "GraphicsUtil.h"

using namespace ZERO;
using namespace ZERO::Graphics;

Terrain::Terrain()
{
}

Terrain::~Terrain()
{
}

void Terrain::Initialize(const char* filename, uint32_t columns, uint32_t rows, float maxHeight)
{
	mHeightMap.GenerateFromRAW(filename, columns, rows);
	
	uint32_t numVertices = columns * rows;
	uint32_t numTiles = (columns - 1) * (rows - 1);
	uint32_t numIndices = numTiles * 6;

	mMesh.Allocate(numVertices, numIndices);
	//double for loops, and set vertex x, y, z

	float uStep = 10.0f / (columns - 1);
	float vStep = 10.0f / (rows - 1);
	for (uint32_t z = 0; z < rows; ++z)
	{
		for (uint32_t x = 0; x < columns; ++x)
		{
			uint32_t index = x + (z*columns);
			float height = mHeightMap.GetHeight(x, z) * maxHeight;
			auto& vertex = mMesh.GetVertex(index);
			vertex.position = { (float)x, height, (float)z };
			vertex.normal = ZERO::Math::Vector3::YAxis();
			vertex.uv = { x * uStep, z*vStep };

		}
	}
	
	//Fill Indices
	uint32_t index = 0;
	for (uint32_t z = 0; z < rows - 1; ++z)
	{
		for (uint32_t x = 0; x < columns - 1; ++x)
		{
			//1 --- 3
			//|  \  |
			//0 --- 2

			mMesh.GetIndex(index++)	 = (x    ) + ((z    )*columns);
			mMesh.GetIndex(index++)	 = (x    ) + ((z + 1)*columns);
			mMesh.GetIndex(index++)	 = (x + 1) + ((z    )*columns);

			mMesh.GetIndex(index++)	 = (x    ) + ((z + 1)*columns);
			mMesh.GetIndex(index++)	 = (x + 1) + ((z + 1)*columns);
			mMesh.GetIndex(index++)	 = (x + 1) + ((z    )*columns);
		}
	}

	GraphicsUtil::ComputeNormals(mMesh);
	mMeshBuffer.Initialize(mMesh);
}

void Terrain::Terminate()
{
	mMeshBuffer.Terminate();
	mMesh.Destroy();
	mHeightMap.Clear();
}

void Terrain::Render()
{
	mMeshBuffer.Render();
}



