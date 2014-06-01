#include "Mesh.h"


Mesh::Mesh() : stride(sizeof(Vertex_PTT)), iCount(0), vBufferSize(0), vertBuff(0), m_localMinimumExtent(vec3(0)), m_localMaximumExtent(vec3(0))
{
#ifdef GL
#else
	iBuffer = 0;
	vBuffer = 0;
#endif
}


Mesh::~Mesh(void)
{
#ifdef GL

#else 
	// DX 10
   if (vBuffer) {
      this->vBuffer->Release();
   }
   if (iBuffer) {
      this->iBuffer->Release();
   }
#endif
   delete [] vertBuff;
}

ErrorCode Mesh::LoadObj(WCHAR *fileName) {   
   UINT vertexCount = 0, texCount = 0, faceCount = 0; 
   
   // Temporary Buffers
   Vec3 *vbuff; // Stores Coordinate Data from file
   Vec2 *tbuff; // Stores Tex Coord Data From File
   __int32 *ibuff; // Stores Index Data from File
   __int32 *texMap; // Maps indices
    

   FILE *fp;
   _wfopen_s(&fp, fileName, L"r");

   if (!fp) {      
      return Error_FileOpenFail;
   }

   // buffer to read one line
   const __int16 buffSize = 512;
   char buff[buffSize];
   
   // PASS 1: First, count number of each element so we can acquire the proper buffers
   while (!feof(fp)) {
      // clear the buffer
      for (int k = 0; k < buffSize; k++) {
         buff[k] = 0;
      }

      fgets(buff, buffSize, fp);

      if (buff[0] == 'v') {
         if (buff[1] == ' ') {
            vertexCount++;
         }
         if (buff[1] == 't') {
            texCount++;
         }         
      }
      if (buff[0] == 'f') {
         faceCount++;
      }   
   }

   // Allocate Buffers   
   vbuff = new Vec3[vertexCount];
   ibuff = new __int32[faceCount * 3];
   tbuff = new Vec2[texCount];  
   if (vertBuff != 0)
   {
	   delete[] vertBuff;
   }
   vertBuff = new Vertex_PTT[texCount]; // Since individual vertices can have multiple tex coords, we split based on those.
   texMap = new __int32[texCount]; // This maps from tBuffer index to vertBuffer index. -1 means not yet mapped.

   if (vbuff == NULL || ibuff == NULL || tbuff == NULL || vertBuff == NULL || texMap == NULL) {
      return Error_MemoryAllocation;
   }

   for (int i = 0; i < texCount; i++) {
      texMap[i] = -1; // Not yet mapped
   }

   // Now, re-read and fill the buffers
   char workingBuff[buffSize] = {0};
      
   int iValue;
   
   // Track how many we have put into each buffer
   UINT vIndex = 0, tIndex = 0, iIndex = 0, vertIndex = 0;
   float value; // the value we read from file.
   int cursor = 0; // Where do we begin reading data on the line
   int marker = 0; // Mark our spot between reads


   fseek(fp, 0, SEEK_SET); // rewind   
   
   // PASS 2:
   // In this loop, we read a line from the file into our buffer "buff"
   // We use "workingBuff" to store the parsed data that we need
   // Once we pull that data, we store it in an appropriate buffer
   while (!feof(fp)) {
      // Clear buffer
      for (int k = 0; k < buffSize; k++) {
         buff[k] = 0;
      }

      fgets(buff, buffSize, fp);          

      if (buff[0] == 'v') {
         if (buff[1] == ' ') { // Vertex Coordinate Data                                    
            cursor = 2; // Begin reading at the third character

            while (buff[cursor] != ' ') { // Read until a blank space
               workingBuff[cursor - 2] = buff[cursor];
               cursor++;
            }

            // Now we have the data for x coordinate in our working buffer.

            // Add Terminator
            workingBuff[cursor] = 0;

            // Mark where we begin next read.
            marker = ++cursor;

            value = atof(workingBuff);

            vbuff[vIndex].x = value;
			            
            while (buff[cursor] != ' ') {
               workingBuff[cursor - marker] = buff[cursor];
               cursor++;
            }

            // Now we have data for y coordinate

            workingBuff[cursor] = 0;
            marker = ++cursor;
            value = atof(workingBuff);
            vbuff[vIndex].y = value;
            
            // Now read until the end of the line
            while (buff[cursor] != ' ' && buff[cursor] != '\n' && buff[cursor] != '\r' && buff[cursor] != 0) {
               workingBuff[cursor - marker] = buff[cursor];
               cursor++;
            }
            workingBuff[cursor] = 0;
            value = atof(workingBuff);
            vbuff[vIndex].z = value;

			// Calculate initial bounding volume extents X
			if (vbuff[vIndex].x < this->m_localMinimumExtent.x)
			{
				this->m_localMinimumExtent.x = vbuff[vIndex].x;
			}
			else if (vbuff[vIndex].x > this->m_localMaximumExtent.x)
			{
				this->m_localMaximumExtent.x = vbuff[vIndex].x;
			}

			// Calculate initial bounding volume extents Y
			if (vbuff[vIndex].y < this->m_localMinimumExtent.y)
			{
				this->m_localMinimumExtent.y = vbuff[vIndex].y;
			}
			else if (vbuff[vIndex].y > this->m_localMaximumExtent.y)
			{
				this->m_localMaximumExtent.y = vbuff[vIndex].y;
			}

			// Calculate initial bounding volume extents Z
			if (vbuff[vIndex].z < this->m_localMinimumExtent.z)
			{
				this->m_localMinimumExtent.z = vbuff[vIndex].z;
			}
			else if (vbuff[vIndex].z > this->m_localMaximumExtent.z)
			{
				this->m_localMaximumExtent.z = vbuff[vIndex].z;
			}
			
            vIndex++;
         } // Finished writing data for a vertex position to vbuff

         if (buff[1] == 't') { // Texure Coord
            cursor = 3;

            while (buff[cursor] != ' ') {
               workingBuff[cursor - 3] = buff[cursor];
               cursor++;
            }

            buff[cursor] = 0;
            marker = ++cursor;
            value = atof(workingBuff);
            tbuff[tIndex].x = value;
                        
            while (buff[cursor] != ' ' && buff[cursor] != '\n' && buff[cursor] != '\r' && buff[cursor] != 0) {
               workingBuff[cursor-marker] = buff[cursor];
               cursor++;
            }
            workingBuff[cursor] = 0;
            marker = ++cursor;
            value = atof(workingBuff);
            tbuff[tIndex].y = value;
            tIndex++;            
         } // Finished writing data for a Texture Coordinate to tbuff         
      }

      if (buff[0] == 'f') {  // Now we assemble our buffers for GPU
         cursor = 2;
         marker = cursor;
         int workingVertex, workingTex; // working index for Vertex and Tangent data

         for (int j = 0; j < 3; j++) { // 3 vertices per face            
            
            // Clear Buffer
            for (int k = 0; k < buffSize; k++) {
               workingBuff[k] = 0;
            }

            // Read first index (Vertex Coordinate)
            while (buff[cursor] != '/') {               
               workingBuff[cursor-marker] = buff[cursor];
               cursor++;
            }

            workingBuff[cursor] = 0;
            marker = ++cursor;
            workingVertex = atoi(workingBuff) - 1; // 1 based indices in obj

            // Clear Buffer
            for (int k = 0; k < buffSize; k++) {
               workingBuff[k] = 0;
            }

            // Read second index (Tex Coord)
            while (buff[cursor] != '/' && buff[cursor] != ' ' && buff[cursor] != '\n' 
               && buff[cursor] != '\r' && buff[cursor] != 0) {
               workingBuff[cursor - marker] = buff[cursor];
               cursor++;
            }
            workingBuff[cursor] = 0;
            marker = ++cursor;
            workingTex = atoi(workingBuff) - 1; // 1 based indices in obj
            
            // Now we have the first set of indices for our face.
            if (texMap[workingTex] != -1) 
			{ 
				// we have already seen this vertex before                              
				ibuff[iIndex] = texMap[workingTex];
            } 
			else 
			{ 
				// we need a new entry in vertexBuffer
               vertBuff[vertIndex].pos.x = vbuff[workingVertex].x;
               vertBuff[vertIndex].pos.y = vbuff[workingVertex].y;
               vertBuff[vertIndex].pos.z = vbuff[workingVertex].z;

               vertBuff[vertIndex].tc[0] = tbuff[workingTex].x;
               vertBuff[vertIndex].tc[1] = tbuff[workingTex].y;

               vertBuff[vertIndex].tangent = Vec3(0, 0, 0);
               vertBuff[vertIndex].normal = Vec3(0, 0, 0);

               texMap[workingTex] = vertIndex;
               ibuff[iIndex] = vertIndex;
               vertIndex++;
            }
            iIndex++;
         }         
      }   
   }
   
   fclose(fp);

   this->iCount = faceCount * 3; // 3 vertices per face
   
   struct triangle {
      Vec3 v0, v1, v2; // Position Values
      Vec2 u0, u1, u2; // Tex Coord Values
   };

   // Now we need to assemble the tangent and normal information

   triangle tri;
   Vec3 workingTangent;
   Vec3 workingFaceNormal;

   for (int i = 0; i < this->iCount; i+=3) {
      workingTangent = Vec3(0, 0, 0);
      workingFaceNormal = Vec3(0, 0, 0);
      
      // Which other indices do we use to define this triangle?
      // ie. If its the middle vertex, i % 3 = 1, so we want i-1, i, i+1
      int whichVert = i % 3; 

      // Grab the 3 vertices that make up this triangle face
      tri.v0 = vertBuff[ibuff[i - whichVert]].pos;
      tri.u0 = vertBuff[ibuff[i - whichVert]].tc;
            
      tri.v1 = vertBuff[ibuff[i - whichVert + 1]].pos;
      tri.u1 = vertBuff[ibuff[i - whichVert + 1]].tc;
            
      tri.v2 = vertBuff[ibuff[i - whichVert + 2]].pos;
      tri.u2 = vertBuff[ibuff[i - whichVert + 2]].tc;

      // Calculate Edge Vectors
      Vec3 e0, e1;
      e0 = tri.v1 - tri.v0;
      e1 = tri.v2 - tri.v0;

      // Calculate Texture "edges"
      Vec2 d0, d1;
      d0 = tri.u1 - tri.u0;
      d1 = tri.u2 - tri.u0;
	  
      //Vec3 norm;
      //Cross(&norm, &e0, &e1);
      Vec3 norm = Cross(e0, e1);

      float detInv = 1 / ((d0.x * d1.y) - (d1.x * d0.y));

      workingTangent.x += detInv * ((d1.y * e0.x) - (d1.x * e1.x));
      workingTangent.y += detInv * ((d1.y * e0.y) - (d1.x * e1.y));
      workingTangent.z += detInv * ((d1.y * e0.z) - (d1.x * e1.z));                                    

      workingFaceNormal += norm;

      vertBuff[ibuff[i - whichVert]].tangent += workingTangent;
      vertBuff[ibuff[i - whichVert + 1]].tangent += workingTangent;
      vertBuff[ibuff[i - whichVert + 2]].tangent += workingTangent;

      vertBuff[ibuff[i - whichVert]].normal += workingFaceNormal;
      vertBuff[ibuff[i - whichVert + 1]].normal += workingFaceNormal;
      vertBuff[ibuff[i - whichVert + 2]].normal += workingFaceNormal;
   }

   // normalize all of the tangents and normals
   for (int i = 0; i < texCount; i++) {
	   //vertBuff[i].tangent = Vec3(0.0f, 1.0f, 0.0f);
	   Normalize(vertBuff[i].tangent);
	   Normalize(vertBuff[i].normal);
      //Normalize(&(vertBuff[i].tangent), &(vertBuff[i].tangent));
      //Normalize(&(vertBuff[i].normal), &(vertBuff[i].normal));
   }
   
   UINT vertSize = sizeof(Vertex_PTT);
   UINT byteWidthV = vertSize * texCount;  
   this->vBufferSize = texCount;

   //UINT byteWidthV = sizeof(Vertex_P) * texCount;  
   UINT byteWidthI = sizeof(DWORD) * (faceCount * 3);
   /*
   Vertex_P *vp = new Vertex_P[texCount];
   for (int i = 0; i < texCount; i++)
   {
	   vp[i].pos = vertBuff[i].pos;
   }*/

   //--------------------
#ifdef GL
    glGenVertexArrays(1, &vaoId[0]);
	glBindVertexArray(vaoId[0]);

	glGenBuffers(1, vboId);

	glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
	glBufferData(GL_ARRAY_BUFFER, byteWidthV, vertBuff, GL_STATIC_DRAW );


	// Vertex attribute 0, is 3 floats wide
	// Vertex_PTT is pos, tan, normal, tc
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, vertSize, reinterpret_cast<void*>(offsetof(Vertex_PTT, pos)));
	glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, vertSize, reinterpret_cast<void*>(offsetof(Vertex_PTT, tangent)));
	glVertexAttribPointer((GLuint)3, 3, GL_FLOAT, GL_FALSE, vertSize, reinterpret_cast<void*>(offsetof(Vertex_PTT, normal)));
	glVertexAttribPointer((GLuint)1, 2, GL_FLOAT, GL_FALSE, vertSize, reinterpret_cast<void*>(offsetof(Vertex_PTT, tc)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glGenBuffers(1, iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, byteWidthI, ibuff, GL_STATIC_DRAW);

	//glBindVertexArray(0);

	/*
	glBindBuffer(GL_ARRAY_BUFFER, vboId[1]);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), colors, GL_STATIC_DRAW );
	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	*/

	glBindVertexArray(0);
#else
          
   //DX

   r->CreateVBuffer((const void *)vertBuff, byteWidthV, &(this->vBuffer));

   r->CreateIBuffer((const void *)ibuff, byteWidthI, &(this->iBuffer));
      
#endif
	//-------------

   // Free Buffers
   delete vbuff;
   delete ibuff;
   delete tbuff;
      
   delete texMap;

   return OK;
}

/*
ErrorCode Mesh::Init(Renderer *r) {
   this->r = r;   
   return OK;   
}*/


ErrorCode Mesh::Draw() {
#ifdef GL
	
	glBindVertexArray(vaoId[0]);
	glDrawElements(GL_TRIANGLES, this->iCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	return OK;
#else
   return r->DrawIndexed(this->iBuffer, this->iCount, this->vBuffer, stride);
#endif

}

void Mesh::ComputeLocalExtents()
{
	for (int i = 0; i < this->vBufferSize; i++)
	{
		vec3 vert = vertBuff[i].pos;

		// Calculate initial bounding volume extents X
		if (vert.x < this->m_localMinimumExtent.x)
		{
			this->m_localMinimumExtent.x = vert.x;
		}
		else if (vert.x > this->m_localMaximumExtent.x)
		{
			this->m_localMaximumExtent.x = vert.x;
		}

		// Calculate initial bounding volume extents Y
		if (vert.y < this->m_localMinimumExtent.y)
		{
			this->m_localMinimumExtent.y = vert.y;
		}
		else if (vert.y > this->m_localMaximumExtent.y)
		{
			this->m_localMaximumExtent.y = vert.y;
		}

		// Calculate initial bounding volume extents Z
		if (vert.z < this->m_localMinimumExtent.z)
		{
			this->m_localMinimumExtent.z = vert.z;
		}
		else if (vert.z > this->m_localMaximumExtent.z)
		{
			this->m_localMaximumExtent.z = vert.z;
		}
	}
}

 void Mesh::GetLocalExtents(vec3 &outMin, vec3&outMax)
 {
	 outMin = this->m_localMinimumExtent;
	 outMax = this->m_localMaximumExtent;
 }