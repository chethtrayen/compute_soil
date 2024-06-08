#include <iostream>
#include <cmath>
using namespace std;

int placeholderIndex[1][3] = {0};

bool isAboveTotalHeight(int initial, int target, int height, bool isCut){
  if(isCut && height > initial){
    return true;
  }

  else if(!isCut && height > target){
    return true;
  }

  return false;
}

bool isBelowTotalHeight(int initial, int target, int height, bool isCut){
  if(isCut && height < target){
    return true;
  }

  else if(!isCut && height < initial){
    return true;
  }

  return false;
}

int getCeilingHeight(int initial, int target, int surface, bool isCut){
  if(isCut && surface > initial){
    return initial;
  }
  else if(!isCut && surface > target){
    return target;
  }

  return surface;
} 

int getBaseHeight(int initial, int target, int surface, bool isCut){
  if(isCut && surface < target){
    return target;
  }
  else if(!isCut && surface < initial){
    return initial;
  }

  return surface;
} 

int computeSoilQualityNode(int initial, int target, int ceilingSurface, int baseSurface){

  const bool isCut = initial > target;
  int ceilingHeight = isCut ? initial : target;
  int baseHeight = isCut ?  target : initial;
  int result = 0;

  if(ceilingSurface > 0 && baseSurface == 0){
    baseHeight = ceilingSurface;
  }else if(ceilingSurface  > 0 && baseSurface > 0){
    ceilingHeight = getCeilingHeight(initial, target, ceilingSurface, isCut);
    baseHeight =  getBaseHeight(initial, target, baseSurface, isCut);
  }else{
    ceilingHeight = baseSurface;
  }

  bool isAbove = isAboveTotalHeight(initial, target, baseHeight, isCut);
  bool isBelow = isBelowTotalHeight(initial, target, ceilingHeight, isCut);

 if(isAbove || isBelow){
    result = 0;
  }else{
    result = ceilingHeight - baseHeight;
  }

  if(isCut){
    result *= -1; 
  }

  cout << result;
  cout << " ";
  return result;
}

void computeSoilQualityJob(int initialData[][3] , int targetData[][3], int ceilingSurfaceData[][3], int baseSurfaceData[][3]){
   int rowSize = 1;
   int columnSize = 3;

  for(int row = 0; row < rowSize; row++){
    for(int column = 0; column < columnSize; column++){
      const int initial = initialData[row][column];
      const int target = targetData[row][column];
      const int ceilingSurface = ceilingSurfaceData[row] != 0 ? ceilingSurfaceData[row][column] : 0;
      const int baseSurface = baseSurfaceData[row] != 0 ? baseSurfaceData[row][column] : 0 ;
      computeSoilQualityNode(initial, target, ceilingSurface, baseSurface);
    }
  }
}

int main(){
  const int arrayLength = 3;
  int initial[1][arrayLength]  = {{30, 100, 50}};
  int target[1][arrayLength]  = {{100, 10, 35}};
  int surfaces1[1][arrayLength]  = {{50, 60, 40}};
  int surfaces2[1][arrayLength]  = {{40, 30, 30}};
  
  //Batch caller
  computeSoilQualityJob(initial, target, surfaces1, placeholderIndex);
  cout << "\n";
  computeSoilQualityJob(initial, target, surfaces1, surfaces2);
  cout << "\n";
  computeSoilQualityJob(initial, target, placeholderIndex, surfaces2);
  cout << endl;
}

