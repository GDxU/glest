// ==============================================================
//	This file is part of Glest (www.glest.org)
//
//	Copyright (C) 2001-2008 Marti�o Figueroa
//
//	You can redistribute this code and/or modify it under 
//	the terms of the GNU General Public License as published 
//	by the Free Software Foundation; either version 2 of the 
//	License, or (at your option) any later version
// ==============================================================

#ifndef _GLEST_GAME_PATHFINDER_H_
#define _GLEST_GAME_PATHFINDER_H_

#include "vec.h"

#include <vector>



using Shared::Graphics::Vec2i;

namespace Glest{ namespace Game{

class Map;
class Unit;

// =====================================================
// 	class PathFinder
//
///	Finds paths for units using a modification of the A* algorithm
// =====================================================

class PathFinder{
public:
	enum TravelState{
		tsArrived,
		tsOnTheWay,
		tsBlocked
	};
	struct Node{
		Vec2i pos;
		Node *next;
		Node *prev;
		float heuristic;
		bool exploredCell;
	};
	typedef std::vector<Node*> Nodes;

public:
	static const int maxFreeSearchRadius;
	static const int pathFindNodesMax;
	static const int pathFindRefresh;

private:
	Nodes openNodes;
	Nodes closedNodes;
	Node *nodePool;
	int nodePoolCount;
	const Map *map;

public:
	PathFinder();
	PathFinder(const Map *map);
	~PathFinder();
	void init(const Map *map);
	TravelState findPath(Unit *unit, const Vec2i &finalPos);

private:
	TravelState aStar(Unit *unit, const Vec2i &finalPos);
	Node *newNode();
	Vec2i computeNearestFreePos(const Unit *unit, const Vec2i &targetPos);
	float heuristic(const Vec2i &pos, const Vec2i &finalPos);
	Nodes::iterator minHeuristic();
	bool openPos(const Vec2i &sucPos);
};

}}//end namespace

#endif
