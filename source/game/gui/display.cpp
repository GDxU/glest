

#include "display.h"

#include "metrics.h"
#include "command_type.h"



namespace Glest {

// =====================================================
// 	class Display
// =====================================================

Display::Display(){
	clear();
}

//misc
void Display::clear(){
	for(int i=0; i<upCellCount; ++i){
		upImages[i]= NULL;
	}

	for(int i=0; i<downCellCount; ++i){
		downImages[i]= NULL;
		downLighted[i]= true;
		commandTypes[i]= NULL;
		commandClasses[i]= ccNull;
	}

	downSelectedPos= invalidPos;
	title.clear();
	text.clear();
	progressBar= -1;
}

int Display::computeDownIndex(int x, int y){
	y= y-(downY-cellSideCount*imageSize);
	
	if(y>imageSize*cellSideCount){
		return invalidPos;
	}

	int cellX= x/imageSize;
	int cellY= (y/imageSize) % cellSideCount;
	int index= (cellSideCount-cellY-1)*cellSideCount+cellX;;

	if(index<0 || index>=downCellCount || downImages[index]==NULL){
		index= invalidPos;
	}

	return index;
}

int Display::computeDownX(int index) const{
	return (index % cellSideCount) * imageSize;
}

int Display::computeDownY(int index) const{
	return Display::downY - (index/cellSideCount)*imageSize - imageSize;
}

int Display::computeUpX(int index) const{
	return (index % cellSideCount) * imageSize;
}

int Display::computeUpY(int index) const{
	return Metrics::getInstance().getDisplayH() - (index/cellSideCount)*imageSize - imageSize;
}

}//end namespace
