// ----------------------------------------------------
// Quadtree implementation --
// ----------------------------------------------------

#ifndef __P2QUADTREE_H__
#define __P2QUADTREE_H__

#include "Collider.h"
#include "p2DynArray.h"

#define QUADTREE_MAX_ITEMS 2

// Helper function to check if one rectangle complately contains another
bool Contains(const SDL_Rect& a, const SDL_Rect& b);
bool Intersects(const SDL_Rect& a, const SDL_Rect& b);

// Tree node -------------------------------------------------------
class p2QuadTreeNode
{

public:

	SDL_Rect				rect;
	p2DynArray<Collider*>	objects;
	p2QuadTreeNode*			parent;
	p2QuadTreeNode*			childs[4];

public:

	p2QuadTreeNode(SDL_Rect r) : 
		rect(r),
		objects(QUADTREE_MAX_ITEMS)
	{
		parent = childs[0] = childs[1] = childs[2] = childs[3] = NULL;
	}

	~p2QuadTreeNode()
	{
		for(int i = 0; i < 4; ++i)
			if(childs[i] != NULL) delete childs[i];
	}
	 
	void Insert(Collider* col)
	{
		//Check if the collider intersects with all 4 childs
		for (int i = 0; i < 4; i++)
		{
			int collisions = 0;
			if (col->CheckCollision(childs[i]->rect))
			{
				collisions++;
			}

			if (collisions == 4)
			{
				objects.PushBack(col);
				return;
			}

		}
		bool inserted = false;
		for (int i = 0; i < 4; i++)
		{
			if (col->CheckCollision(childs[i]->rect))
			{
				childs[i]->Insert(col);
				bool inserted = true;
			}
				
		} 
		if (!inserted)
		{
			objects.PushBack(col);

		}
		// TODO: Insertar un nou Collider al quadtree
		// En principi cada node pot enmagatzemar QUADTREE_MAX_ITEMS nodes (encara que podrien ser m�s)
		// Si es detecten m�s, el node s'ha de tallar en quatre
		// Si es talla, a de redistribuir tots els seus colliders pels nous nodes (childs) sempre que pugui
		// Nota: un Collider pot estar a m�s de un node del quadtree
		// Nota: si un Collider intersecciona als quatre childs, deixar-lo al pare
	}

	int CollectCandidates(p2DynArray<Collider*>& nodes, const SDL_Rect& r) const
	{
		/*
		Calcular a quin node es troba el rectangle r i afegirhi tots els colliders d'aquell node
		*/
		// TODO:
		// Omplir el array "nodes" amb tots els colliders candidats
		// de fer intersecci� amb el rectangle r
		// retornar el n�mero de intersecci�n calculades en el proc�s
		// Nota: �s una funci� recursiva
		return 0;
	}

	void CollectRects(p2DynArray<p2QuadTreeNode*>& nodes) 
	{
		nodes.PushBack(this);

		for(int i = 0; i < 4; ++i)
			if(childs[i] != NULL) childs[i]->CollectRects(nodes);
	}

};

// Tree class -------------------------------------------------------
class p2QuadTree
{
public:

	// Constructor
	p2QuadTree() : root(NULL)
	{}

	// Destructor
	virtual ~p2QuadTree()
	{
		Clear();
	}

	void SetBoundaries(const SDL_Rect& r)
	{
		if(root != NULL)
			delete root;

		root = new p2QuadTreeNode(r);
	}

	void Insert(Collider* col)
	{
		if(root != NULL)
		{
			if(Intersects(root->rect, col->rect))
				root->Insert(col);
		}
	}

	void Clear()
	{
		if(root != NULL)
		{
			delete root;
			root = NULL;
		}
	}

	int CollectCandidates(p2DynArray<Collider*>& nodes, const SDL_Rect& r) const
	{
		int tests = 1;
		if(root != NULL && Intersects(root->rect, r))
			tests = root->CollectCandidates(nodes, r);
		return tests;
	}

	void CollectRects(p2DynArray<p2QuadTreeNode*>& nodes) const
	{
		if(root != NULL)
			root->CollectRects(nodes);
	}

public:

	p2QuadTreeNode*	root;

};

#endif // __p2QuadTree_H__