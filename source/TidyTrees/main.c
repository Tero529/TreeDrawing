#include"binaryTree.h"
#include"WetherellShannon.c"

int main(){
	node *root=createTree();
	enum AlgorithmType secondPass=NORMAL;
	generateWetherellShannon(root,maxHeight,secondPass);
	inorderPrint(root);
	return 0;
}
