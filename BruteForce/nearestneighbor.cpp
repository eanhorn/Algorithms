/*
 * nearestneighbor.cpp
 *
 *  Created on: Sep 24, 2021
 *      Author: erikjanhorn
 */
#include <cmath>
#include <iostream>
#include <limits>
#include <string>
#include<utility>
using namespace std;

struct Neighbor{
	float x, y;
	string name;
	Neighbor(float x_, float y_, string name_) :
		x{x_},  y{y_}; name{name_}
	{}
	Neighbor() : x{0}, y{0}, name{"unknown"}{}
};

float distance(float x1, float y1, float x2, float y2){
	float dx = x2-x1, dy=y2-y1;
	return dx*dx+dy*dy;
}

pair <Neighbor, Neighbor> nearest(Neighbor nbs[], int length){
	float min_dist = numeric_limits<float>::max();
	int min_i, min_j;
	for(int i=0;i<length-1;i++){
		for(int j=i+1;j<length;j++){
			float cur_dist = distance(nbs[i].x, nbs[i].y, nbs[j].x, nbs[j].y);
			if(cur_dist<min_dist){
				min_dist = cur_dist;
				min_i=i;
				min_j=j;
			}
		}
	}
	return make_pair(nbs[min_i], nbs[min_j]);
}
int main(){
	Neighbor nbs[4] = {Neighbor(12.5, 34.5, "A"),
										Neighbor(13.5, 44.5, "B"),
										Neighbor(14.5, 54.5, "C"),
										Neighbor(15.5, 64.5, "D")};

	pair<Neighbor, Neighbor> result = nearest(nbs, 4);
	cout << result.first.name << " " << result.second.name << endl;
	return 0;
}



