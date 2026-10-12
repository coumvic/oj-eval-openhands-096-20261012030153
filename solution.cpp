#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

struct NodeInfo {
    int depth;
    int parent;
    NodeInfo(int d, int p) : depth(d), parent(p) {}
};

class Solution {
private:
    unordered_map<int, NodeInfo*> nodeMap;
    int index;
    
    TreeNode* buildTree(const vector<int>& preorder) {
        if (index >= preorder.size() || preorder[index] == -1) {
            index++;
            return nullptr;
        }
        
        TreeNode* root = new TreeNode(preorder[index]);
        index++;
        root->left = buildTree(preorder);
        root->right = buildTree(preorder);
        return root;
    }
    
    void buildNodeMap(TreeNode* node, int depth, int parent) {
        if (!node) return;
        
        nodeMap[node->val] = new NodeInfo(depth, parent);
        buildNodeMap(node->left, depth + 1, node->val);
        buildNodeMap(node->right, depth + 1, node->val);
    }
    
public:
    void solve() {
        int q;
        cin >> q;
        
        vector<pair<int, int>> queries;
        for (int i = 0; i < q; i++) {
            int x, y;
            cin >> x >> y;
            queries.push_back({x, y});
        }
        
        // Read the entire remaining line for preorder traversal
        vector<int> preorder;
        string line;
        cin.ignore();
        getline(cin, line);
        
        istringstream iss(line);
        int num;
        while (iss >> num) {
            preorder.push_back(num);
        }
        
        // Build the tree
        index = 0;
        TreeNode* root = buildTree(preorder);
        
        // Build node information map
        buildNodeMap(root, 0, -1);
        
        // Process queries
        for (const auto& query : queries) {
            int x = query.first;
            int y = query.second;
            
            if (nodeMap.find(x) == nodeMap.end() || nodeMap.find(y) == nodeMap.end()) {
                cout << 0 << endl;
                continue;
            }
            
            NodeInfo* infoX = nodeMap[x];
            NodeInfo* infoY = nodeMap[y];
            
            if (infoX->depth == infoY->depth && infoX->parent != infoY->parent) {
                cout << 1 << endl;
            } else {
                cout << 0 << endl;
            }
        }
        
        // Clean up memory
        cleanup(root);
        for (auto& pair : nodeMap) {
            delete pair.second;
        }
    }
    
    void cleanup(TreeNode* node) {
        if (!node) return;
        cleanup(node->left);
        cleanup(node->right);
        delete node;
    }
};

int main() {
    Solution sol;
    sol.solve();
    return 0;
}