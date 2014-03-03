#include "includes.h"
#include "GameEntity.h"

class Quadtree
{
	Quadtree *parent;
	e::unique_ptr<Quadtree> nodes[4];
	e::vector<e::shared_ptr<GameEntity>> entities;
	e::XMFLOAT2 pos;
	float width, height;
	bool split;
public:
	Quadtree(e::XMVECTOR pos, float width, float height, Quadtree *parent);
	void Insert(e::shared_ptr<GameEntity> entity);
	void Update();
private:
	int GetNode(e::shared_ptr<GameEntity> entity);
	void Split();
	static const int MAX_ENTITIES;

	enum NODE
	{
		NODE_OUT_OF_BOUNDS = -1,
		NODE_THIS = -2
	};
};