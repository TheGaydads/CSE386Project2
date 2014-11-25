#ifndef ___TREE_H___
#define ___TREE_H___


#include "visualobject.h"
 
class Tree : public VisualObject
{
	public:
		Tree( float height = 7.0f, float width = 14.0f, 
			  int rows = 1, int columns = 1 );

		virtual ~Tree(void);
			
		virtual void initialize();

		virtual void draw();

	protected:
	
		void setShaderValues();

		int rows, columns;
		float height, width;

		int indiceCount;
};

#endif // ___TREE_H___

