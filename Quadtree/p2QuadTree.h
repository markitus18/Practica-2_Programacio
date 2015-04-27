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
	 
	void DivideNode(Collider* col)
	{
		SDL_Rect newChild{ rect.x, rect.y, rect.w / 2, rect.h / 2 };

		childs[0] = new p2QuadTreeNode(newChild);
		childs[0]->parent = this;

		childs[1] = new p2QuadTreeNode(newChild);
		childs[1]->rect.x += rect.w / 2;
		childs[1]->parent = this;

		childs[2] = new p2QuadTreeNode(newChild);
		childs[2]->rect.y += rect.h / 2;
		childs[2]->parent = this;

		childs[3] = new p2QuadTreeNode(newChild);
		childs[3]->rect.x += rect.w / 2;
		childs[3]->rect.y += rect.h / 2;
		childs[3]->parent = this;

		p2DynArray<Collider*> tmp = objects;

		objects.Clear();

		for (int i = 0; i < tmp.Count(); i++)
		{
			Insert(tmp[i]);
		}

		Insert(col);
	}

	bool IntersectsMiddle (Collider* col)
	{
		int collisions = 0;
		for (int i = 0; i < 4; i++)
		{

			if (Intersects(col->rect, childs[i]->rect))
			{
				collisions++;
			}
		}
		if (collisions == 4)
			return true;
		return false;
	}

	void Insert(Collider* col)
	{
		//Check if the collider intersects with all 4 childs

		if (childs[0] != NULL)
		{
			if (IntersectsMiddle(col))
			{
					objects.PushBack(col);
					return;
			}

			//else
			//{
				for (int i = 0; i < 4; i++)
				{
					if (Intersects(col->rect, childs[i]->rect))
					{
						childs[i]->Insert(col);
					}

				}
		//	}

		}

		if (childs[0] == NULL)
		{
			if (objects.Count()  >= QUADTREE_MAX_ITEMS)
			{
				DivideNode(col);				
			}
			else
				objects.PushBack(col);
		}

		// TODO: Insertar un nou Collider al quadtree
		// En principi cada node pot enmagatzemar QUADTREE_MAX_ITEMS nodes (encara que podrien ser més)
		// Si es detecten més, el node s'ha de tallar en quatre
		// Si es talla, a de redistribuir tots els seus colliders pels nous nodes (childs) sempre que pugui
		// Nota: un Collider pot estar a més de un node del quadtree
		// Nota: si un Collider intersecciona als quatre childs, deixar-lo al pare
	}

	int CollectCandidates(p2DynArray<Collider*>& nodes, const SDL_Rect& r) const
	{
		int counter = 0;

		for (int i = 0; i < objects.Count(); i++)
		{
			nodes.PushBack(objects[i]);
			counter++;
		}

		if (childs[0] != NULL)
		{
			for (int i = 0; i < 4; i++)
			{
				if (Intersects(childs[i]->rect, r))
				{
					counter += childs[i]->CollectCandidates(nodes, r);
				}
			}
		}

		return counter;
		/*
		Calcular a quin node es troba el rectangle r i afegirhi tots els colliders d'aquell node
		*/
		// TODO:
		// Omplir el array "nodes" amb tots els colliders candidats
		// de fer intersecció amb el rectangle r
		// retornar el número de intersección calculades en el procés
		// Nota: és una funció recursiva
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