#include <iostream>
using namespace std;

const int rowSize = 1;
const int columnSize = 3;

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

void computeSoilQualityJob(int initialData[][columnSize] , int targetData[][columnSize], int ceilingSurfaceData[][columnSize], int baseSurfaceData[][columnSize]){
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
  int placeholderIndex[rowSize][columnSize] = {0}; 
  /*
  Notes:
    - Index 0: Is a fill with surfaces in the initial and target bounds
    - Index 1: Is a cut with both surfaces outside the initial and target bounds
    - Index 2: Is a cut with the last surfaces outside the target bounds
  */
  int initial[rowSize][columnSize]  = {{30, 100, 50}};
  int target[rowSize][columnSize]  = {{100, 10, 35}};
  int surfaces1[rowSize][columnSize]  = {{50, 110, 40}};
  int surfaces2[rowSize][columnSize]  = {{40, 5, 30}};
  
  
  //Batch caller
  computeSoilQualityJob(initial, target, surfaces1, placeholderIndex);
  cout << "\n";
  computeSoilQualityJob(initial, target, surfaces1, surfaces2);
  cout << "\n";
  computeSoilQualityJob(initial, target, placeholderIndex, surfaces2);
  cout << endl;
}

