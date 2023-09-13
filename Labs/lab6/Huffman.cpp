
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
//Creating a class of Binary tree node to be able to strore characters c
class BinaryNode {
    public:
        char character;
        int frequency;
       BinaryNode *left, *right;
       //Parameterized Constructor for the binary Node 
        BinaryNode(char ch, int freq){
            character = ch;
            frequency=freq;
            left = NULL;
            right =NULL;

        }
         
        

};

/**
 * Comparison function, compares frequency of two nodes.
 * if the frequence of left node is bigger than the right Node's
 * It return true. This comparison is helpful for us in the 
 * priority queue, it determines the order of nodes, because nodes 
 * with higher frequencies will have lowe priority and vice versa,
 * so we can have the priority queue in the ascending order of frequencies
*/
bool comparison (const BinaryNode* left, const BinaryNode* right){
    if (left->frequency > right->frequency){
        return true;
    }
    else {
        return false;
    }
}
BinaryNode* makeHuffmanTree(const std::string & str){
    
    //Compute the frequence of each character
    std::unordered_map<char, int> freqOfChars;
    char ch;
    for (int i=0; i < str.size(); i++){
        ch = str[i];
        freqOfChars[ch]++;
    }

    //Initialize priority queue with the element type BinaryNode*
   std:: priority_queue<BinaryNode*, std::vector<BinaryNode*>, decltype(&comparison)> priorityQueue(&comparison);
   for(const std::pair<char,int>& pair: freqOfChars){
    char character = pair.first;
    int frequency = pair.second;
    
    // Create a single-node binary tree for each pair of characters and frequencies
    BinaryNode* node = new BinaryNode(character, frequency);
    // Insert the node into the queue with having frequency as key
    priorityQueue.push(node);
   }
    // Now build the Huffman tree
    while(priorityQueue.size()>1){

       BinaryNode * littleTree1 = priorityQueue.top();
       int frequency1 = littleTree1->frequency;
       priorityQueue.pop();
       BinaryNode * littleTree2 = priorityQueue.top();
       int frequency2 = littleTree2->frequency;
       priorityQueue.pop();

       //Create a new binary tree with left subtree and right subtree

       BinaryNode * newTree = new BinaryNode(' ',frequency1+frequency2);
       newTree ->left =littleTree1 ; 
       newTree ->right= littleTree2;

       //Insert the new binary tree into the priority queue with key frequency1+frequency2
       priorityQueue.push(newTree);


   }

   // Rturn Huffman tree
   BinaryNode* huffmanTree = priorityQueue.top();
   return huffmanTree;
   
}
/**
 * printTrie function that given huffman tree prints the huffman encoding trie
 * first we chech if the node is nullptr, if it is we just return, because ther is nothing to print
 * if the current node is leaf (we can understand this by checking the left and right node it's point to is nulllptr, because leaf points to nullptr as its the last level)
 * it means we traverse all the tree so we can print the character and it's encoding
 * until we haven't reached the leaves, we need to keep traversing the tree
 * by recursive call to the left and right side of the tree
*/
void printTrie (const BinaryNode* node, std::string encoding= ""){
    if (node == nullptr){
        return;
    }
    if (node->left== nullptr && node->right==nullptr){
        std::cout<<node->character <<": "<<encoding <<std::endl;
    }
    printTrie(node->left, encoding + "0");
    printTrie(node->right, encoding+ "1");
}
/**
 * Because we used dynamic memory, we need to free the memory after allocation (deallocate)
 * to avaoid memory leak
*/
void deleteNode (BinaryNode * node){
    if (node ==nullptr){
        return ;
    }
    else{
        deleteNode(node->left);
        deleteNode(node->right);
        delete node;
    }
}


int main()
{    
    std::string str = "EYEWITNESSNEWS";
    // calling makeHuffmanTree function
    BinaryNode* huffmanTree = makeHuffmanTree(str);
    // calling printTrie function
    printTrie(huffmanTree);
    // calling the deleteNode function 
   deleteNode(huffmanTree);
    return 0;
}


/***/