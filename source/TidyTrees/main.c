#include"binaryTree.h"
#include"WetherellShannon.c"

int main(){
	node *root=createTree();
	generateWetherellShannon(root,maxHeight);
	return 0;
}
