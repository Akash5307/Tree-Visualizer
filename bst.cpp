#include<iostream>
#include <climits>
#include<queue>
#include<tuple>
using namespace std;

//BST CODE STARTS----------------------------------------------
struct BST{
    BST* left;
    BST* right;
    int val;
    BST(int val){
        left=nullptr,right=nullptr;
        this->val=val;
    }
    ~BST(){
        delete left;delete right;
    }
};
void insert(BST **root,int val){
    if(*root==nullptr){
        *root=new BST(val);
        return;
    }
    BST* curr=*root;
    while(1){
        if(val<curr->val){
            if(!curr->left){
                curr->left=new BST(val);
                break;
            }
            curr=curr->left;
        }else{
            if(!curr->right){
                curr->right=new BST(val);
                break;
            }
            curr=curr->right;
        }
    }
}
bool deleteNode(BST** root,int val){
    BST* curr=*root,*parent=nullptr;
    // Find node to delete
    while (curr && curr->val != val) {
        parent = curr;
        if(curr->val>val){
            curr=curr->left;
        }else{
            curr=curr->right;
        }
    }
    if(!curr)return 0;
    //case 1: Two children
    if(curr->left and curr->right){
        // Find inorder successor (minimum in right subtree)
        BST* successor=curr->right,*successorParent=curr;
        while(successor->left){
            successorParent=successor;
            successor=successor->left;
        }
        // Copy successor data and delete successor
        curr->val = successor->val;
        if (successorParent->left == successor)
            successorParent->left = successor->right;
        else
            successorParent->right = successor->right;
        
        successor->right = nullptr; // Prevent recursive deletion
        delete successor;
        return 1;
    }    
    // Case 2/3: 0 or 1 child
    BST* child = curr->left ? curr->left : curr->right;
    if (!parent) {
        *root = child; // Update root if deleting root node
    } else {
        if (parent->left == curr)
            parent->left = child;
        else
            parent->right = child;
    }
    
    curr->left = curr->right = nullptr; // Prevent recursive deletion
    delete curr;
    return 1;
}
void preorder(BST* root) {
    if (root) {
        cout << root->val << " ";
        preorder(root->left);
        preorder(root->right);
    }
}
void inorder(BST* root) {
    if (root) {
        inorder(root->left);
        cout << root->val << " ";
        inorder(root->right);
    }
}
void postorder(BST* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        cout << root->val << " ";
    }
}
void levelOrder(BST* root) {
    if (!root) return;
    
    queue<BST*> q;
    q.push(root);
    
    while (!q.empty()) {
        BST* current = q.front();
        q.pop();
        cout << current->val << " ";
        
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
}
int findMin(BST* root) {
    if (!root) throw runtime_error("Tree is empty");
    while (root->left) root = root->left;
    return root->val;
}

int findMax(BST* root) {
    if (!root) throw runtime_error("Tree is empty");
    while (root->right) root = root->right;
    return root->val;
}
int height(BST* root){
    if(!root)return -1;
    return 1+ ( max( height(root->left),height(root->right) ) );
}
int countNodes(BST* root){
    if(!root)return 0;
    return 1+countNodes(root->left)+countNodes(root->right);
}
//BST CODE ENDS
#include<map>
map<int,vector<int>>g;
void print(BST* root){
    if(!root)return;
    queue<BST*>q;
    q.push(root);
    while(!q.empty()){
        int sz=q.size();
        while(sz--){
            auto node=q.front();
            q.pop();
            if(node->left){
                q.push(node->left);
                g[node->val].push_back(node->left->val);
            }
            if(node->right){
                g[node->val].push_back(node->right->val);
                q.push(node->right);
            }
        }
    }
    for(auto [x,vec]:g){
        cout<<x<<" -> ";
        for(auto child:vec){
            cout<<child<<" ";
        }cout<<"\n";
    }
}



//Main Part of the code begins from here::::::::::::::::::::::::::::::::::::
//////////////////////::::::::::::::::::::::::::::::::::::::::::///////////////////////////
#include <fstream>
void generateDotFile(map<int,vector<int>>&g, const string& filename = "graph.dot") {
    ofstream dotFile(filename);
    if (!dotFile.is_open()) {
        cerr << "Failed to create DOT file." << endl;
        return;
    }

    dotFile << "digraph G {\n";
    dotFile << "  node [shape=circle, fontname=\"Arial\"];\n"; // Style nodes

    for (auto [node,vec]:g) {
        for (int child : vec) {
            dotFile << "  " << node << " -> " << child << ";\n"; // Add edges
        }
    }

    dotFile << "}\n";
    dotFile.close();

    cout << "DOT file generated: " << filename << endl;
}
///////////////////////:::::::::::::::::::::::::::::::::::::::////////////////////////////

int main(){
    BST* root = nullptr;
    
    // Insert nodes
    insert(&root, 50);
    insert(&root, 30);
    insert(&root, 70);
    insert(&root, 20);
    insert(&root, 40);
    insert(&root, 60);
    insert(&root, 80);
    insert(&root,10);
    insert(&root,100);
    insert(&root,103);
    insert(&root,75);
    insert(&root,5);

    deleteNode(&root,103);

    print(root);


    generateDotFile(g);
    // system("dot -Tpng graph.dot -o graph.png && open graph.png");
    system("dot -Tpng graph.dot -o graph.png");

    delete root;
    return 0;
}